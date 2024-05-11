#include "pid_freq.h"

//=========================================================
// ПИД регулятор для удержания температуры лазера
//=========================================================
// Коэффициенты регулятора
float FREQ_factorKp = 0.8f;//0.5f; //17.5f; // Kurchanov
float FREQ_factorKi = 0.2f;//0.4f; //27.0f; // Kurchanov
float FREQ_factorKd = 0.0f;

float FREQ_rangeMax = 65535.0f;
float FREQ_rangeMin = -65535.0f;
//=========================================================

float FREQ_valueP = 0.0;
float FREQ_valueI = 0.0;
float FREQ_valueD = 0.0;
float FREQ_valueS = 0.0;
float FREQ_nowValue = 0.0;
float FREQ_backValue = 0.0;
bool FREQ_flagRun = false;

void Reset_FREQ_PID(void){
	FREQ_valueP = 0.0f;
	FREQ_valueI = 0.0f;
	FREQ_valueD = 0.0f;
	FREQ_valueS = 0.0f;
	FREQ_nowValue = 0.0;
	FREQ_backValue = 0.0;
	FREQ_flagRun = false;
}
// Расчет воздействия
float Compute_FREQ_PID(float value){
	// Предыдущие значение
	FREQ_backValue = FREQ_nowValue;
	// Текущие значение
	FREQ_nowValue = value;
	//===================================================
	// Пропорциональная составляющая
	//===================================================
	FREQ_valueP = FREQ_nowValue;
	//===================================================
	// Интегральная составляющая
	//===================================================
	if (FREQ_factorKi != 0){
		FREQ_valueI += FREQ_factorKi * FREQ_valueP;
		if (FREQ_valueI > FREQ_rangeMax){
			FREQ_valueI = FREQ_rangeMax;
		}
		if(FREQ_valueI < FREQ_rangeMin){
			FREQ_valueI = FREQ_rangeMin;
		}
	}
	//===================================================
	// Дифференциальная составляющая
	//===================================================
	FREQ_valueD = FREQ_nowValue - FREQ_backValue;
	//===================================================
	// Суммарное воздействие
	//===================================================	
	// Первый проход (нет дифференциальной части)
	if (FREQ_flagRun == false){
		FREQ_flagRun = true;
		FREQ_valueS = FREQ_factorKp * FREQ_valueP + 
										FREQ_valueI;
	} else {
		FREQ_valueS = FREQ_factorKp * FREQ_valueP + 
										FREQ_valueI +
										FREQ_factorKd * FREQ_valueD;
	}
	return FREQ_valueS;
}
