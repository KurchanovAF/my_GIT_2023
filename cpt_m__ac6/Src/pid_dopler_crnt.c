#include "pid_dopler_crnt.h"

//=========================================================
// ПИД регулятор для удержания температуры лазера
//=========================================================
// Коэффициенты регулятора
float DOPLER_CRNT_factorKp = 0.1f; //1.5f; // Kurchanov
float DOPLER_CRNT_factorKi = 0.01f; //0.1f; // Kurchanov
float DOPLER_CRNT_factorKd = 0.0f;

float DOPLER_CRNT_rangeMax = 65535.0f;
float DOPLER_CRNT_rangeMin = -65535.0f;
//=========================================================

float DOPLER_CRNT_valueP = 0.0;
float DOPLER_CRNT_valueI = 0.0;
float DOPLER_CRNT_valueD = 0.0;
float DOPLER_CRNT_valueS = 0.0;
float DOPLER_CRNT_nowValue = 0.0;
float DOPLER_CRNT_backValue = 0.0;
bool DOPLER_CRNT_flagRun = false;

void Reset_DOPLER_CRNT_PID(void){
	DOPLER_CRNT_valueP = 0.0f;
	DOPLER_CRNT_valueI = 0.0f;
	DOPLER_CRNT_valueD = 0.0f;
	DOPLER_CRNT_valueS = 0.0f;
	DOPLER_CRNT_nowValue = 0.0;
	DOPLER_CRNT_backValue = 0.0;
	DOPLER_CRNT_flagRun = false;
}
// Расчет воздействия
float Compute_DOPLER_CRNT_PID(float value){
	// Предыдущие значение
	DOPLER_CRNT_backValue = DOPLER_CRNT_nowValue;
	// Текущие значение
	DOPLER_CRNT_nowValue = value;
	//===================================================
	// Пропорциональная составляющая
	//===================================================
	DOPLER_CRNT_valueP = DOPLER_CRNT_nowValue;
	//===================================================
	// Интегральная составляющая
	//===================================================
	if (DOPLER_CRNT_factorKi != 0){
		DOPLER_CRNT_valueI += DOPLER_CRNT_factorKi * DOPLER_CRNT_valueP;
		if (DOPLER_CRNT_valueI > DOPLER_CRNT_rangeMax){
			DOPLER_CRNT_valueI = DOPLER_CRNT_rangeMax;
		}
		if(DOPLER_CRNT_valueI < DOPLER_CRNT_rangeMin){
			DOPLER_CRNT_valueI = DOPLER_CRNT_rangeMin;
		}
	}
	//===================================================
	// Дифференциальная составляющая
	//===================================================
	DOPLER_CRNT_valueD = DOPLER_CRNT_nowValue - DOPLER_CRNT_backValue;
	//===================================================
	// Суммарное воздействие
	//===================================================	
	// Первый проход (нет дифференциальной части)
	if (DOPLER_CRNT_flagRun == false){
		DOPLER_CRNT_flagRun = true;
		DOPLER_CRNT_valueS = DOPLER_CRNT_factorKp * DOPLER_CRNT_valueP + 
										DOPLER_CRNT_valueI;
	} else {
		DOPLER_CRNT_valueS = DOPLER_CRNT_factorKp * DOPLER_CRNT_valueP + 
										DOPLER_CRNT_valueI +
										DOPLER_CRNT_factorKd * DOPLER_CRNT_valueD;
	}
	return DOPLER_CRNT_valueS;
}
