#include <pid_freq.h>

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

//=========================================================
// ПИ регулятор для удержания частоты
//=========================================================

struct {
	float FREQ_valueS;
	float FREQ_valueI;
	float FREQ_valueP;

	float FREQ_factorKp;
	float FREQ_factorKi;
} pi_freq;

float FREQ_valueP_ = 0.0f;
float FREQ_valueI_ = 0.0f;
float FREQ_valueS_ = 0.0f;

void reset_freq_pi(void){
	pi_freq.FREQ_valueS = 0.0f;
	pi_freq.FREQ_valueI = 0.0f;
	pi_freq.FREQ_valueP = 0.0f;

	pi_freq.FREQ_factorKp = FREQ_factorKp;
	pi_freq.FREQ_factorKi = FREQ_factorKi;

	FREQ_valueS_ = 0.0f;
	FREQ_valueI_ = 0.0f;
	FREQ_valueP_ = 0.0f;
}

void set_freq_pi(void){
	pi_freq.FREQ_factorKp = FREQ_factorKp;
	pi_freq.FREQ_factorKi = FREQ_factorKi;
}

void freq_pi_(void){
	FREQ_valueI_ += FREQ_valueP_*FREQ_factorKi;
	FREQ_valueS_ = FREQ_valueP_*FREQ_factorKp + FREQ_valueI_;
}

