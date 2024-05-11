#include "pid_dopler_tec.h"

//=========================================================
// ПИД регулятор для удержания температуры лазера
//=========================================================
// Коэффициенты регулятора
float DOPLER_TEC_factorKp = 0.08f;//1.5f;
float DOPLER_TEC_factorKi = 0.002f;//0.1f;
float DOPLER_TEC_factorKd = 0.0f;

float DOPLER_TEC_rangeMax = 65535.0f;
float DOPLER_TEC_rangeMin = -65535.0f;
//=========================================================

float DOPLER_TEC_valueP = 0.0;
float DOPLER_TEC_valueI = 0.0;
float DOPLER_TEC_valueD = 0.0;
float DOPLER_TEC_valueS = 0.0;
float DOPLER_TEC_nowValue = 0.0;
float DOPLER_TEC_backValue = 0.0;
bool DOPLER_TEC_flagRun = false;

void Reset_DOPLER_TEC_PID(void){
	DOPLER_TEC_valueP = 0.0f;
	DOPLER_TEC_valueI = 0.0f;
	DOPLER_TEC_valueD = 0.0f;
	DOPLER_TEC_valueS = 0.0f;
	DOPLER_TEC_nowValue = 0.0;
	DOPLER_TEC_backValue = 0.0;
	DOPLER_TEC_flagRun = false;
}
// Расчет воздействия
float Compute_DOPLER_TEC_PID(float value){
	// Предыдущие значение
	DOPLER_TEC_backValue = DOPLER_TEC_nowValue;
	// Текущие значение
	DOPLER_TEC_nowValue = value;
	//===================================================
	// Пропорциональная составляющая
	//===================================================
	DOPLER_TEC_valueP = DOPLER_TEC_nowValue;
	//===================================================
	// Интегральная составляющая
	//===================================================
	if (DOPLER_TEC_factorKi != 0){
		DOPLER_TEC_valueI += DOPLER_TEC_factorKi * DOPLER_TEC_valueP;
		if (DOPLER_TEC_valueI > DOPLER_TEC_rangeMax){
			DOPLER_TEC_valueI = DOPLER_TEC_rangeMax;
		}
		if(DOPLER_TEC_valueI < DOPLER_TEC_rangeMin){
			DOPLER_TEC_valueI = DOPLER_TEC_rangeMin;
		}
	}
	//===================================================
	// Дифференциальная составляющая
	//===================================================
	DOPLER_TEC_valueD = DOPLER_TEC_nowValue - DOPLER_TEC_backValue;
	//===================================================
	// Суммарное воздействие
	//===================================================	
	// Первый проход (нет дифференциальной части)
	if (DOPLER_TEC_flagRun == false){
		DOPLER_TEC_flagRun = true;
		DOPLER_TEC_valueS = DOPLER_TEC_factorKp * DOPLER_TEC_valueP + 
										DOPLER_TEC_valueI;
	} else {
		DOPLER_TEC_valueS = DOPLER_TEC_factorKp * DOPLER_TEC_valueP + 
										DOPLER_TEC_valueI +
										DOPLER_TEC_factorKd * DOPLER_TEC_valueD;
	}
	return DOPLER_TEC_valueS;
}
