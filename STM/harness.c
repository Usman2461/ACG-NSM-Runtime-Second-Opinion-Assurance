#include "zipc_stub.h"
#include "Main_m0.h"
#include "ComSys_Paramram.h"
#include <string.h>

/* event buffer the generated code reads */
char ZMainEvent[256] = "";

/* expose current state: Main_m0.c keeps it in a static array, so we
   track it via a shadow updated by reading after each call.
   Simplest: re-declare access through a helper the generated file lacks,
   so instead we mirror state by parsing. We add an accessor by making
   the generated state visible: we re-implement a tiny tracker. */

/* Since ZMain_m0State is static in Main_m0.c, we expose state by adding
   a global the actions update is not enough. Instead we read state via
   a function we add to Main_m0.c through a small patch (see build). */
extern int zipc_get_state_internal(void);

/* ---- public API for ctypes ---- */
void stm_init(void) {
    strcpy(ZMainEvent, "");
    strcpy(g_last_action, "none");
    ZMain_m0Init();
}

/* inject an event by name, then run one evaluation cycle */
const char* stm_step(const char* event_name) {
    strncpy(ZMainEvent, event_name, 255);
    ZMainEvent[255] = '\0';
    strcpy(g_last_action, "none");
    ZMain_m0Call();
    return g_last_action;
}

int stm_state(void) { return zipc_get_state_internal(); }
const char* stm_action(void) { return g_last_action; }

/* RAM accessors */
void stm_set_ram(unsigned char passedline, unsigned char oncoming,
                 unsigned char pedestrian, unsigned int remain) {
    PassedLine = passedline;
    Oncoming = oncoming;
    Pedestrian = pedestrian;
    Remain = remain;
}
unsigned char stm_get_passedline(void) { return PassedLine; }
