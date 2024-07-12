//=============================================================================
//       Greg Friedholm Copyright (c) 2017
//-----------------------------------------------------------------------------
//       Tamper.h
//-----------------------------------------------------------------------------
//  This file contains definitions for functions defined in Tamper.c
//=============================================================================

#ifndef TAMPER_H_
#define TAMPER_H_

#define TAMPER_ACTIVE     true
#define TAMPER_INACTIVE   false

#define DEF_TAMPER_INACTIVE_COUNTER   5
#define DEF_TAMPER_ACTIVE_COUNTER     1

#define DEF_TAMPER_COUNTDOWN TWO_HUNDRED_MILLISECONDS;


//
// Global functions
//

void SigmaDeltaInit(void);
void CheckForTamper(void);
void SetTamper(bool tamperState);
bool GetTamperState(void);

#endif  // TAMPER_H_