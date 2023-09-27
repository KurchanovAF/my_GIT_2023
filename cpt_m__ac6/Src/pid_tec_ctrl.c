#include "pid_tec_ctrl.h"

//=========================================================
// ��� ��������� ��� ��������� ����������� ������
//=========================================================
// ������������ ����������
float TECCTRL_factorKp =  1.00f;//4.00f;//10.0f; // �������� 1.00f -> 10.0f
float TECCTRL_factorKi =  0.01f;// 0.2f; // �������� 0.02f ->  0.2f
float TECCTRL_factorKd =  0.00f; // �������� 0.50f ->  0.0f

float TECCTRL_rangeMax = 65535.0f;
float TECCTRL_rangeMin = -65535.0f;
//=========================================================

float TECCTRL_valueP = 0.0;
float TECCTRL_valueI = 0.0;
float TECCTRL_valueD = 0.0;
float TECCTRL_valueS = 0.0;
float TECCTRL_nowValue = 0.0;
float TECCTRL_backValue = 0.0;
bool TECCTRL_flagRun = false;

void Reset_TECCTRL_PID(void){
	TECCTRL_valueP = 0.0f;
	TECCTRL_valueI = 0.0f;
	TECCTRL_valueD = 0.0f;
	TECCTRL_valueS = 0.0f;
	TECCTRL_nowValue = 0.0;
	TECCTRL_backValue = 0.0;
	TECCTRL_flagRun = false;
}
// ������ �����������
float Compute_TECCTRL_PID(float value){
	// ���������� ��������
	TECCTRL_backValue = TECCTRL_nowValue;
	// ������� ��������
	TECCTRL_nowValue = value;
	//===================================================
	// ���������������� ������������
	//===================================================
	TECCTRL_valueP = TECCTRL_nowValue;
	//===================================================
	// ������������ ������������
	//===================================================
	if (TECCTRL_factorKi != 0){
		TECCTRL_valueI += TECCTRL_factorKi * TECCTRL_valueP;
		if (TECCTRL_valueI > TECCTRL_rangeMax){
			TECCTRL_valueI = TECCTRL_rangeMax;
		}
		if(TECCTRL_valueI < TECCTRL_rangeMin){
			TECCTRL_valueI = TECCTRL_rangeMin;
		}
	}
	//===================================================
	// ���������������� ������������
	//===================================================
	TECCTRL_valueD = TECCTRL_nowValue - TECCTRL_backValue;
	//===================================================
	// ��������� �����������
	//===================================================	
	// ������ ������ (��� ���������������� �����)
	if (TECCTRL_flagRun == false){
		TECCTRL_flagRun = true;
		TECCTRL_valueS = TECCTRL_factorKp * TECCTRL_valueP + 
										TECCTRL_valueI;
	} else {
		TECCTRL_valueS = TECCTRL_factorKp * TECCTRL_valueP + 
										TECCTRL_valueI +
										TECCTRL_factorKd * TECCTRL_valueD;
	}
	return TECCTRL_valueS;
}
