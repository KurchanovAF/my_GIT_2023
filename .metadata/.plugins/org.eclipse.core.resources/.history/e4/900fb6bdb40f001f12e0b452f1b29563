/*
 * pid_DOPLER_FREQ.c
 *
 *  Created on: 03 июля 2021 г.
 *      Author: Анатолий
 */
#include "pid_DOPLER_FREQ.h"
#include "var.h"

//=========================================================
// ПИД регулятор для удержания длины волны экстремумом частоты
//=========================================================
// Коэффициенты регулятора
float DOPLER_FREQ_factorKp =  1.00f;
float DOPLER_FREQ_factorKi =  10.0f;
float DOPLER_FREQ_factorKd =  0.00f;

float DOPLER_FREQ_rangeMax = 65535.0f;
float DOPLER_FREQ_rangeMin = -65535.0f;
//=========================================================

float DOPLER_FREQ_valueP = 0.0;
float DOPLER_FREQ_valueI = 0.0;
float DOPLER_FREQ_valueD = 0.0;
float DOPLER_FREQ_valueS = 0.0;
float DOPLER_FREQ_nowValue = 0.0;
float DOPLER_FREQ_backValue = 0.0;
bool DOPLER_FREQ_flagRun = false;

void Reset_DOPLER_FREQ_PID(void){
	DOPLER_FREQ_valueP = 0.0f;
	DOPLER_FREQ_valueI = 0.0f;
	DOPLER_FREQ_valueD = 0.0f;
	DOPLER_FREQ_valueS = 0.0f;
	DOPLER_FREQ_nowValue = 0.0;
	DOPLER_FREQ_backValue = 0.0;
	DOPLER_FREQ_flagRun = false;
}
// Расчет воздействия
float Compute_DOPLER_FREQ_PID(float value){
	//my_INT++;
	//value = my_FLT_;
	// Предыдущие значение
	DOPLER_FREQ_backValue = DOPLER_FREQ_nowValue;
	// Текущие значение
	DOPLER_FREQ_nowValue = value;
	//===================================================
	// Пропорциональная составляющая
	//===================================================
	DOPLER_FREQ_valueP = DOPLER_FREQ_nowValue;
	//===================================================
	// ИнтDOPLER_FREQегральная составляющая
	//===================================================
	if (DOPLER_FREQ_factorKi != 0){
		DOPLER_FREQ_valueI += DOPLER_FREQ_factorKi * DOPLER_FREQ_valueP;
		if (DOPLER_FREQ_valueI > DOPLER_FREQ_rangeMax){
			DOPLER_FREQ_valueI = DOPLER_FREQ_rangeMax;
		}
		if(DOPLER_FREQ_valueI < DOPLER_FREQ_rangeMin){
			DOPLER_FREQ_valueI = DOPLER_FREQ_rangeMin;
		}
	}
	//===================================================
	// Дифференциальная составляющая
	//===================================================
	DOPLER_FREQ_valueD = DOPLER_FREQ_nowValue - DOPLER_FREQ_backValue;
	//===================================================
	// Суммарное воздействие
	//===================================================
	// Первый проход (нет дифференциальной части)
	if (DOPLER_FREQ_flagRun == false){
		DOPLER_FREQ_flagRun = true;
		DOPLER_FREQ_valueS = DOPLER_FREQ_factorKp * DOPLER_FREQ_valueP +
										DOPLER_FREQ_valueI;
	} else {
		DOPLER_FREQ_valueS = DOPLER_FREQ_factorKp * DOPLER_FREQ_valueP +
										DOPLER_FREQ_valueI +
										DOPLER_FREQ_factorKd * DOPLER_FREQ_valueD;
	}
	//my_FLT = DOPLER_FREQ_valueS;
	return DOPLER_FREQ_valueS;
}


