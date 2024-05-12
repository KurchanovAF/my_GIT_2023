#ifndef __DOPLER_CRNT_PID_H__
#define __DOPLER_CRNT_PID_H__
#include <stdbool.h>
float Compute_DOPLER_CRNT_PID(float value);
void Reset_DOPLER_CRNT_PID(void);

void reset_DOP_pi(void);
void DOP_pi_(void);

#endif
