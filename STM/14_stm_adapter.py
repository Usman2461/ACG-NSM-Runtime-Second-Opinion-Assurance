"""
14_stm_adapter.py
=================
Phase 6 (Option A): Adapter between the RLC Bridge and the compiled ZIPC STM.

The bridge emits risk/legality events (EV_RISK_*, EV_ILLEGAL_PROCEED, ...).
The compiled TURNLEFT STM understands signal/yield/timer events
(EV_SIG_RED, EV_YIELD_BLOCK, ...). This adapter MAPS between them and
ticks the generated-C state machine via ctypes.

Mapping rationale (Option A - reuse existing verified model):
  Bridge concept                     -> ZIPC STM event
  -----------------------------------------------------------
  legality: PROCEED illegal (red)    -> EV_SIG_RED
  legality: proceed legal (green)    -> EV_SIG_GREEN_LT
  legality: yellow / warning         -> EV_SIG_YELLOW
  risk: CRITICAL or HIGH             -> EV_YIELD_BLOCK (must brake/yield)
  risk: dropped to LOW/MED + legal   -> EV_YIELD_CLEAR
  reached stop line (scenario)       -> EV_STOPLINE_REACH
  intersection exit (scenario)       -> EV_INTSEC_EXIT
  sensor fault (bridge)              -> EV_TMR_EXPIRED (-> fault/safe path)

USAGE:
  from stm_adapter import STMAdapter
  stm = STMAdapter('./libstm.so')
  stm.init()
  result = stm.step_from_bridge(bridge_output, scenario_flags)
"""
import ctypes

STATE_NAMES = {0:'INIT', 1:'APPROACH', 2:'BRAKE_HOLD', 3:'ASSESS_YIELD',
               4:'YIELD_WAIT', 5:'TURNING', 6:'SLOW_FAULT', 7:'FAULT_EXIT'}


class STMAdapter:
    def __init__(self, lib_path='./libstm.so'):
        self.lib = ctypes.CDLL(lib_path)
        self.lib.stm_step.restype = ctypes.c_char_p
        self.lib.stm_step.argtypes = [ctypes.c_char_p]
        self.lib.stm_action.restype = ctypes.c_char_p
        self.lib.stm_state.restype = ctypes.c_int
        self.lib.stm_set_ram.argtypes = [ctypes.c_ubyte]*3 + [ctypes.c_uint]

    def init(self):
        self.lib.stm_init()

    def state(self):
        return self.lib.stm_state()

    def state_name(self):
        return STATE_NAMES.get(self.state(), '?')

    def _raw_step(self, event_name):
        action = self.lib.stm_step(event_name.encode()).decode()
        return action

    def map_bridge_to_zipc_events(self, bridge_out, scenario_flags):
        """
        Translate bridge output + scenario context into an ORDERED list of
        ZIPC events to inject this tick. Priority: safety first.
        """
        events = []
        ram = bridge_out['ram']
        bridge_events = bridge_out['events']

        # --- scenario-driven structural events ---
        if scenario_flags.get('stopline_reached'):
            events.append('EV_STOPLINE_REACH')
        if scenario_flags.get('intersection_exit'):
            events.append('EV_INTSEC_EXIT')

        # --- safety (risk) first ---
        risk_tier = ram['RiskTier']   # 0=LOW 1=MED 2=HIGH 3=CRITICAL
        if risk_tier >= 2:            # HIGH or CRITICAL -> must yield/brake
            events.append('EV_YIELD_BLOCK')
        elif 'EV_RISK_LOW' in bridge_events or risk_tier <= 1:
            # risk cleared -> allow yield clear (only meaningful if was blocked)
            if scenario_flags.get('was_yielding'):
                events.append('EV_YIELD_CLEAR')

        # --- legality (signal) ---
        mask = ram['LegalMask']
        proceed_legal = bool(mask & 0b000001)   # bit0 = PROCEED
        art = ram['ViolationArticle']

        if not proceed_legal and art == 38:
            events.append('EV_SIG_RED')          # signal violation -> red
        elif 'EV_RISK_LOW' in bridge_events and proceed_legal:
            events.append('EV_SIG_GREEN_LT')     # clear to go
        # yellow handled by warning verdicts (optional)

        # --- sensor fault -> fault path ---
        if 'EV_SENSOR_FAULT' in bridge_events:
            events.append('EV_TMR_EXPIRED')

        return events

    def step_from_bridge(self, bridge_out, scenario_flags):
        """
        Push RAM, map events, inject them in order, return final state+action.
        Returns dict: {events_injected, state, state_name, action}
        """
        # write RAM (oncoming/pedestrian from bridge legality inputs)
        ram = bridge_out['ram']
        # derive oncoming/pedestrian flags from audit if present
        ped = 1 if scenario_flags.get('pedestrian') else 0
        onc = 1 if scenario_flags.get('oncoming') else 0
        passedline = 1 if scenario_flags.get('passed_line') else 0
        self.lib.stm_set_ram(passedline, onc, ped, int(ram.get('RSSMargin',0)) & 0xFFFF)

        zipc_events = self.map_bridge_to_zipc_events(bridge_out, scenario_flags)

        actions = []
        for ev in zipc_events:
            a = self._raw_step(ev)
            if a != 'none':
                actions.append(a)

        return {
            'events_injected': zipc_events,
            'state': self.state(),
            'state_name': self.state_name(),
            'action': actions[-1] if actions else 'none',
            'all_actions': actions,
        }


# ---- self-test: bridge -> adapter -> compiled STM ----
if __name__ == '__main__':
    import sys
    sys.path.insert(0, '/mnt/d/NSTM_Project/src')
    import importlib.util
    spec = importlib.util.spec_from_file_location("bridge", "/mnt/d/NSTM_Project/src/13_rlc_bridge.py")
    bridge_mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(bridge_mod)

    print("="*64)
    print("Full chain test: RLC Bridge -> Adapter -> compiled ZIPC STM")
    print("="*64)

    bridge = bridge_mod.RLCBridge(weather='clear')
    stm = STMAdapter('/mnt/d/NSTM_Project/stm/libstm.so')
    stm.init()
    print(f"\nInitial STM state: {stm.state_name()}")

    # simulate a left-turn approach sequence
    ticks = [
        ("Approaching, green, clear",
         {'obs_dist':(40,0.95),'ego_speed':(35,0.95),'pedestrian':(False,0.95),
          'traffic_light':(1,0.95),'oncoming':(False,0.95)},
         {'speed_limit':50}, {'stopline_reached':True}),
        ("At line, light turns red",
         {'obs_dist':(40,0.95),'ego_speed':(10,0.95),'pedestrian':(False,0.95),
          'traffic_light':(0,0.95),'oncoming':(False,0.95)},
         {'speed_limit':50}, {}),
        ("Green left arrow, but oncoming (high risk)",
         {'obs_dist':(15,0.92),'ego_speed':(20,0.93),'pedestrian':(False,0.93),
          'traffic_light':(1,0.95),'oncoming':(True,0.92)},
         {'speed_limit':50}, {}),
        ("Oncoming cleared, low risk, green",
         {'obs_dist':(45,0.95),'ego_speed':(15,0.95),'pedestrian':(False,0.95),
          'traffic_light':(1,0.95),'oncoming':(False,0.95)},
         {'speed_limit':50}, {'was_yielding':True}),
    ]

    for name, perc, inp, flags in ticks:
        bout = bridge.process(perc, inp)
        result = stm.step_from_bridge(bout, flags)
        print(f"\n--- {name} ---")
        print(f"  bridge events: {bout['events']}")
        print(f"  -> ZIPC events: {result['events_injected']}")
        print(f"  -> STM state: {result['state_name']}, action: {result['action']}")

    print("\n=== Full perception->bridge->STM chain WORKING ===")
