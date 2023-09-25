#include "pid_cell.h"

//=========================================================
// ПИД регулятор для удержания температуры лазера
//=========================================================
// Коэффициенты регулятора
float CELL_factorKp = 50.0f;//50.f;//30.0f;
float CELL_factorKi = 0.03f;//0.001f;//0.001f;// 0.02f; // Курчанов
float CELL_factorKd = 0.00f;

float CELL_rangeMax = 65535.0f;
float CELL_rangeMin = 0.0f;
//=========================================================

float CELL_valueP = 0.0;
float CELL_valueI = 0.0;
float CELL_valueD = 0.0;
float CELL_valueS = 0.0;
float CELL_nowValue = 0.0;
float CELL_backValue = 0.0;
bool CELL_flagRun = false;

void Reset_CELL_PID(void){
	CELL_valueP = 0.0f;
	CELL_valueI = 0.0f;
	CELL_valueD = 0.0f;
	CELL_valueS = 0.0f;
	CELL_nowValue = 0.0;
	CELL_backValue = 0.0;
	CELL_flagRun = false;
}
// Расчет воздействия
float Compute_CELL_PID(float value){
	// Предыдущие значение
	CELL_backValue = CELL_nowValue;
	// Текущие значение
	CELL_nowValue = value;
	//===================================================
	// Пропорциональная составляющая
	//===================================================
	CELL_valueP = CELL_nowValue;
	//===================================================
	// Интегральная составляющая
	//===================================================
	if (CELL_factorKi != 0){
		CELL_valueI += CELL_factorKi * CELL_valueP;
		if (CELL_valueI > CELL_rangeMax){
			CELL_valueI = CELL_rangeMax;
		}
		if(CELL_valueI < CELL_rangeMin){
			CELL_valueI = CELL_rangeMin;
		}
	}
	//===================================================
	// Дифференциальная составляющая
	//===================================================
	CELL_valueD = CELL_nowValue - CELL_backValue;
	//===================================================
	// Суммарное воздействие
	//===================================================	
	// Первый проход (нет дифференциальной части)
	if (CELL_flagRun == false){
		CELL_flagRun = true;
		CELL_valueS = CELL_factorKp * CELL_valueP + 
										CELL_valueI;
	} else {
		CELL_valueS = CELL_factorKp * CELL_valueP + 
										CELL_valueI +
										CELL_factorKd * CELL_valueD;
	}
	return CELL_valueS;
}
