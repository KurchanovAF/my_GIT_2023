/*
 * pid_MICROWAVE.c
 *
 *  Created on: 11 ����. 2021 �.
 *      Author: ��������
 */
#include "pid_MICROWAVE.h"
#include "var.h"

//=========================================================
// ��� ��������� ��� ��������� �������� ��� ������
//=========================================================
// ������������ ����������
float MICROWAVE_factorKp =  1.00f;
float MICROWAVE_factorKi =  10.0f;
float MICROWAVE_factorKd =  0.00f;

float MICROWAVE_rangeMax = 65535.0f;
float MICROWAVE_rangeMin = -65535.0f;
//=========================================================

float MICROWAVE_valueP = 0.0;
float MICROWAVE_valueI = 0.0;
float MICROWAVE_valueD = 0.0;
float MICROWAVE_valueS = 0.0;
float MICROWAVE_nowValue = 0.0;
float MICROWAVE_backValue = 0.0;
bool MICROWAVE_flagRun = false;

void Reset_MICROWAVE_PID(void){
	MICROWAVE_valueP = 0.0f;
	MICROWAVE_valueI = 0.0f;
	MICROWAVE_valueD = 0.0f;
	MICROWAVE_valueS = 0.0f;
	MICROWAVE_nowValue = 0.0;
	MICROWAVE_backValue = 0.0;
	MICROWAVE_flagRun = false;
}
// ������ �����������
float Compute_MICROWAVE_PID(float value){
	//my_INT++;
	//value = my_FLT_;
	// ���������� ��������
	MICROWAVE_backValue = MICROWAVE_nowValue;
	// ������� ��������
	MICROWAVE_nowValue = value;
	//===================================================
	// ���������������� ������������
	//===================================================
	MICROWAVE_valueP = MICROWAVE_nowValue;
	//===================================================
	// ������������ ������������
	//===================================================
	if (MICROWAVE_factorKi != 0){
		MICROWAVE_valueI += MICROWAVE_factorKi * MICROWAVE_valueP;
		if (MICROWAVE_valueI > MICROWAVE_rangeMax){
			MICROWAVE_valueI = MICROWAVE_rangeMax;
		}
		if(MICROWAVE_valueI < MICROWAVE_rangeMin){
			MICROWAVE_valueI = MICROWAVE_rangeMin;
		}
	}
	//===================================================
	// ���������������� ������������
	//===================================================
	MICROWAVE_valueD = MICROWAVE_nowValue - MICROWAVE_backValue;
	//===================================================
	// ��������� �����������
	//===================================================
	// ������ ������ (��� ���������������� �����)
	if (MICROWAVE_flagRun == false){
		MICROWAVE_flagRun = true;
		MICROWAVE_valueS = MICROWAVE_factorKp * MICROWAVE_valueP +
										MICROWAVE_valueI;
	} else {
		MICROWAVE_valueS = MICROWAVE_factorKp * MICROWAVE_valueP +
										MICROWAVE_valueI +
										MICROWAVE_factorKd * MICROWAVE_valueD;
	}
	//my_FLT = MICROWAVE_valueS;
	return MICROWAVE_valueS;
}


