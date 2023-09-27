#include "pid_optics_pwr.h"
#include "var.h"

//=========================================================
// ��� ��������� ��� ��������� ���������� �������� ������
//=========================================================
// ������������ ����������
float OPTICS_PWR_factorKp = 0.1f;
float OPTICS_PWR_factorKi = 0.001f;
float OPTICS_PWR_factorKd = 0.00f;

float OPTICS_PWR_rangeMax = 65535.0f;
float OPTICS_PWR_rangeMin = -65535.0f;//0.0f;
//=========================================================

float OPTICS_PWR_valueP = 0.0;
float OPTICS_PWR_valueI = 0.0;
float OPTICS_PWR_valueD = 0.0;
float OPTICS_PWR_valueS = 0.0;
float OPTICS_PWR_nowValue = 0.0;
float OPTICS_PWR_backValue = 0.0;
bool OPTICS_PWR_flagRun = false;

void Reset_OPTICS_PWR_PID(void){
	OPTICS_PWR_valueP = 0.0f;
	OPTICS_PWR_valueI = 0.0f;
	OPTICS_PWR_valueD = 0.0f;
	OPTICS_PWR_valueS = 0.0f;
	OPTICS_PWR_nowValue = 0.0;
	OPTICS_PWR_backValue = 0.0;
	OPTICS_PWR_flagRun = false;
	fix_avrResult_OUT_DC = avrResult_OUT_DC;
}
// ������ �����������
float Compute_OPTICS_PWR_PID(float value){
	// ���������� ��������
	OPTICS_PWR_backValue = OPTICS_PWR_nowValue;
	// ������� ��������
	OPTICS_PWR_nowValue = value;
	//===================================================
	// ���������������� ������������
	//===================================================
	OPTICS_PWR_valueP = OPTICS_PWR_nowValue;
	//===================================================
	// ������������ ������������
	//===================================================
	if (OPTICS_PWR_factorKi != 0){
		OPTICS_PWR_valueI += OPTICS_PWR_factorKi * OPTICS_PWR_valueP;
		/**/
		if (OPTICS_PWR_valueI > OPTICS_PWR_rangeMax){
			OPTICS_PWR_valueI = OPTICS_PWR_rangeMax;
		}
		if(OPTICS_PWR_valueI < OPTICS_PWR_rangeMin){	// ���� OPTICS_PWR_factorKi < 0, �� ��������� �������� !!
			OPTICS_PWR_valueI = OPTICS_PWR_rangeMin;
		}
		//*/
	}
	//===================================================
	// ���������������� ������������
	//===================================================
	OPTICS_PWR_valueD = OPTICS_PWR_nowValue - OPTICS_PWR_backValue;
	//===================================================
	// ��������� �����������
	//===================================================	
	// ������ ������ (��� ���������������� �����)
	if (OPTICS_PWR_flagRun == false){
		OPTICS_PWR_flagRun = true;
		OPTICS_PWR_valueS = OPTICS_PWR_factorKp * OPTICS_PWR_valueP + 
										OPTICS_PWR_valueI;
	} else {
		OPTICS_PWR_valueS = OPTICS_PWR_factorKp * OPTICS_PWR_valueP + 
										OPTICS_PWR_valueI +
										OPTICS_PWR_factorKd * OPTICS_PWR_valueD;
	}
	return OPTICS_PWR_valueS;
}
