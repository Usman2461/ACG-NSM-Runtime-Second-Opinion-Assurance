#ifndef __ACTION_DECLS_H__
#define __ACTION_DECLS_H__
void InitAll(void); void Brake(void); void SlowDown(void); void Hold(void);
void EmergBrake(void); void Resume(void); void WarnFault(void);
void RecheckYld(void); void RecheckSig(void); void RecheckAll(void);
void SetPassedLine(void); void StartSigTmr(void); void StartSafetyTmr(void);
void StartTurnTmr(void); void StartYldChk(void);
#endif
