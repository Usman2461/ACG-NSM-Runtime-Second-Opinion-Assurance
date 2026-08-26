#include "zipc_stub.h"
#include "ComSys_Paramram.h"
#include <string.h>

char g_last_action[64] = "none";

/* Each action records itself so Python can read what the STM decided.
   In the real vehicle these would actuate; here we capture the decision. */
void InitAll(void)        { CAPTURE_ACTION("InitAll"); PassedLine=0; }
void Brake(void)          { CAPTURE_ACTION("Brake"); }
void SlowDown(void)       { CAPTURE_ACTION("SlowDown"); }
void Hold(void)           { CAPTURE_ACTION("Hold"); }
void EmergBrake(void)     { CAPTURE_ACTION("EmergBrake"); }
void Resume(void)         { CAPTURE_ACTION("Resume"); }
void WarnFault(void)      { CAPTURE_ACTION("WarnFault"); }
void RecheckYld(void)     { CAPTURE_ACTION("RecheckYld"); }
void RecheckSig(void)     { CAPTURE_ACTION("RecheckSig"); }
void RecheckAll(void)     { CAPTURE_ACTION("RecheckAll"); }
void SetPassedLine(void)  { CAPTURE_ACTION("SetPassedLine"); PassedLine=1; }
void StartSigTmr(void)    { /* timer stubs: no action capture */ }
void StartSafetyTmr(void) { }
void StartTurnTmr(void)   { }
void StartYldChk(void)    { }
