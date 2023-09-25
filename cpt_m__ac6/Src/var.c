#include "var.h"

int ID_keyTest = 1;
int itemWork = WORK_SCAN_CRNT;

int my_TST = 0;
//=========================================================

uint32_t  my_TST_U32;

bool bCompFreqTK = false;		// Компенсация частоты по температуре контроллера
bool bCompFreqTK_1 = false;		// Старт процесса компенсации произошел, начальный код мы запомнили
float avrResult_SD1_start = 0;	// Начальное значение кода датчика температуры микроконтроллера
float SD1_d;

int var_my_ADC2 = 1;
// Вариант 2 - функции цифровой фильтрации на С		- 33384 такта,  период = 60022
// Вариант 1 - функции цифровой фильтрации на ASM	-  8315 тактов, период = 60022 (60021 - 60025)
// Вариант 0 - нет цифровой фильтрации на С			-  8325 тактов, период = 60022 (60022 - 60027)

// 06 апреля 2021
// точное управление частотой и тонкой настройкой тока лазера проводить каждую нечетную миллисекунду
// остальные 9 параметров собрать в 4 группы по 2 параметра, а 5-я группа будет из 1-го параметра
// итого минимальная длина цикла 10 миллисекунд, но можно и оставить длину 16 миллисекунд
// пока только планы...
//
// при скорости 115200 бод 1 бит передается 8,7 мкс; 1 байт (всего 10 бит) передается 87 мкс (11,5 кБайт в секунду)
// 9 групп по 4 байта (36 байт) при скорости 115200 бод передаются 3,123 мс
// 1 байт на скорости 4800 бод передается 2,088 мс
// 1 байт на скорости 19200 бод передается 0,522 мс ==> можно передавать до 1000 байт в секунду,
// а нужно реально 9*4*10 = 360 байт в секунду (100/36 36/100 < 6/16 = 0,375)
// а нужно реально 9*4*10 = 360 байт в секунду (100/36 36/100 < 8/22 = 0,364):
// 22 = 11 + 8 + 3, 3 группы это ??? ...
// 8/24 = 0,3333
// 24 = 12 + 8 + 4
//
bool b_my_ms_num = false;	// признак прохождения первого цикла из 16 мс
int my_ms_num = 0;	// Номер активной миллисекунды для установки параметров
			//  0 - миллисекунда не активная
			//  1 - точное управление частотой (UT1A - перепутаны)
			//  2 - мощность нагрева лазера
			//  3 - грубая настройка тока лазера
			//  4 - заказанный уровень температуры лазера
			//  5 - настройка тока катушек
			//  6 - мощность нагрева ячейки
			//  7 - тонкая настройка тока лазера
			//  8 - грубая настройка частоты (UT2A)
			//  9 - уровень СВЧ
			// 10 - параметры делителя ФАПЧ
			// 11 - усиление фотоприемника
int my_alarm = 1;	// Признак недопустимого поведения программы
int my_Tick = 0;

uint32_t num_TIM4 = 0;
bool     b_TIM4 = false;

// Kurchanov 24.02.2021
uint8_t LSM303_BufferTx[16];
uint8_t LSM303_BufferRx[16];
// Kurchanov 24.02.2021
uint8_t I2C3_RxBuffer[16];
uint8_t I2C3_TxBuffer[16];
// Kurchanov 24.02.2021
uint16_t my_LSM303D_Temperature = 0;

// Kurchanov 05.03.2021
float F2F1_rezult_X      = 0;
float F2F1_rezult_A      = 0;
float F2F1_rezult_A_30   = 0;		//   3 секунды
float F2F1_rezult_A_900  = 0;		//  90 секунд
int   F2F1_rezult_N_30   = 0;
int   F2F1_rezult_N_900  = 0;

// Kurchanov 09.03.2021
float F1F2_rezult_X      = 0;
float F1F2_rezult_A      = 0;
float F1F2_rezult_A_30   = 0;		//   3 секунды
float F1F2_rezult_A_900  = 0;		//  90 секунд
int   F1F2_rezult_N_30   = 0;
int   F1F2_rezult_N_900  = 0;

//=========================================================

//* DEFINE CS133
int value_UT1A = 32768;
int value_UT1A_aver = 0;
float value_UT1A_rez = 0;
int value_UT2A = 32768;
int value_VY = 35187;// 41400; // !!!
int value_VY_aver = 0;
float value_VY_rez = 0;
int value_U2R = 32768;
int value_U2R_D = 920;//230;//920;//1845;//7380;//1845;//3690;	// Смещение длины волны от пика частоты
int value_VT1 =  41800;//38930; //40500;//36500;//47500 Р Т‘Р В»РЎРЏ РЎвЂ Р ВµР В·Р С‘РЎРЏ//46930;
int value_L1 = 65000;//1500; //0; // Kurchanov
int value_T5 = 0;
int value__T5 = 0;
int value_DTX = 30000;
int value_DTX_aver = 0;
float value_DTX_rez = 0;
int value_RFI = 4000;//2800;//1390; //1950;//1900;
int value_OutFactor = 128;
//*/

/* DEFINE Rb97
int value_UT1A = 32768;
int value_UT1A_aver = 0;
float value_UT1A_rez = 0;
int value_UT2A = 39226;
int value_VY = 49700;
int value_VY_aver = 0;
float value_VY_rez = 0;
int value_U2R = 32768;
int value_VT1 = 42500;//38000;//38000 Р Т‘Р В»РЎРЏ РЎР‚РЎС“Р В±Р С‘Р Т‘Р С‘РЎРЏ; 47500 Р Т‘Р В»РЎРЏ РЎвЂ Р ВµР В·Р С‘РЎРЏ// 46930; Р С™РЎС“РЎР‚РЎвЂЎР В°Р Р…Р С•Р Р†
int value_L1 = 65000;
int value_T5 = 0;
int value_DTX = 30000;
int value_DTX_aver = 0;
float value_DTX_rez = 0;
int value_RFI = 3400;
int value_OutFactor = 128;
//*/

bool flagUpdate_UT1A = false;
bool flagUpdate_UT2A = false;
bool flagUpdate_VY = false;
bool flagUpdate_U2R = false;
bool flagUpdate_VT1 = false;
bool flagUpdate_L1 = false;
bool flagUpdate_T5 = false;
bool flagUpdate_DTX = false;
bool flagUpdate_RFI = false;
bool flagUpdate_OutFactor = false;
bool flagUpdate_LMX2486 = false;

// Р В¤Р В»Р В°Р С– Р С—Р С•Р Т‘Р С”Р В»РЎР‹РЎвЂЎР ВµР Р…Р С‘РЎРЏ РЎвЂ Р С‘РЎвЂћРЎР‚Р С•Р Р†Р С•Р С–Р С• Р Т‘Р В°РЎвЂљРЎвЂЎР С‘Р С”Р В° РЎвЂљР ВµР С�Р С—Р ВµРЎР‚Р В°РЎвЂљРЎС“РЎР‚РЎвЂ№
bool flagConnectedTempSensor = false;
//bool flagConnectedTempSensor = true;
uint32_t ticsDelayUpdateTempCell = 0;

uint8_t I2C3_RxBuffer[16];
uint8_t I2C3_TxBuffer[16];


int fixValue_TEC_CTRL = 0;
int fixValue_MICROWAVE = 0;
int fixValue_DOPLER_FREQ = 0;
int fixValue_VY = 41800;		// Kurchanov Р вЂ™Р вЂўР вЂєР пїЅР В§Р пїЅР СњР С’ Р СњР пїЅР вЂњР вЂќР вЂў Р СњР вЂў Р пїЅР РЋР СџР С›Р вЂєР В¬Р вЂ”Р Р€Р вЂўР СћР РЋР Р‡ !!
int fixValue_T5 = 0;
int fixValue_U2R = 32768;
int fixValue_UT1A = 32768;

//float my_delta = 0;
//float my_deltaPID = 0;
//int my_INT = 0;
//float my_FLT = 0;
//float my_FLT_ = 0;

int scanStep_VY = 25; // Р С™РЎС“РЎР‚РЎвЂЎР В°Р Р…Р С•Р Р†
int scanMin_VY = 20000;	// 45000 Р С™РЎС“РЎР‚РЎвЂЎР В°Р Р…Р С•Р Р†
int scanMax_VY = 55000;

int scanStep_UT2A = 50;//5;//50;
int scanMin_UT2A = 0;
int scanMax_UT2A = 65535;

bool b_PID_FLAG_LOOP_CELL = false;	// false - первый вызов, true - уже работает
bool b_PID_FLAG_LOOP_SENSOR_TEMP_CELL = false;	// false - первый вызов, true - уже работает

/* 3Р’В 417Р’В xxx xxx
int LMX_ValueN = 341;
int LMX_ValueFN = 851920;
int LMX_ValueFD = 1158497;//*/
// 4 596Р’В xxx xxx
//*//4Р’В 596Р’В 312Р’В 735
//* Cs 4 596 315 885 Гц
int LMX_ValueN = 459;
int LMX_ValueFN = 2242603;// 4Р’В 596Р’В 331Р’В 869
int LMX_ValueFD = 3541771;//*/
// 4Р’В 596Р’В 333Р’В 285,000 ==> 32768, 38196
// 4Р’В 596Р’В 332Р’В 785,000 ==> 32768, 38575
// 4Р’В 596Р’В 332Р’В 285,000 ==> 32768, 38962
// 4Р’В 596Р’В 331Р’В 985,000 ==> 32768, 39191
// 4Р’В 596Р’В 331Р’В 869,000 ==> 32762, 39226


int LMX_ValueINT = 0;
float LMX_ShiftFreq = 8051.0f;
int LMX_DataValueFN[256];
int LMX_DataValueFD[256];
int itemOptionLMX = 128;

int statusLoopPID = PID_FLAG_LOOP_TEC_CTRL;

bool flagUpdateCompute_TEC_CTRL = false;
bool flagUpdateCompute_MICROWAVE = false;
bool flagProcess_MICROWAVE = false;		// Выявление начала процесса регулирования для запоминания начального значения
bool flagUpdateCompute_DOPLER_FREQ = false;
bool flagProcess_DOPLER_FREQ = false;	// Выявление начала процесса регулирования для запоминания начального значения
bool flagUpdateCompute_OUT2_DOPLER_CRNT = false;
bool flag_SCAN_CRNT = false;						// Kurchanov 10.03.2021
bool flagUpdateCompute_OUT2_DOPLER_TEC = false;
bool flagUpdateCompute_OUT1_OPTICS_PWR = false;
bool flagProcess_OUT1_OPTICS_PWR = false;
bool flagUpdateCompute_CELL = false;
bool flagUpdateTempCell = false;


float result_OUT2_DOPLER_CRNT = 0.0f;
float result_OUT2_DOPLER_TEC = 0.0f;
float result_OUT1_OPTICS_PWR = 0.0f;

int fixValue_OUT2_DOPLER_CRNT = 0;
int fixValue_OUT2_DOPLER_TEC = 0;


float level_CONTR = 2048.0f;
// Р вЂќР ВµРЎвЂљР ВµР С”РЎвЂљР С•РЎР‚ Р В·Р В°РЎвЂ¦Р Р†Р В°РЎвЂљР В°
float sigmaPID_CTRL = 10.0f;
int countLoopPID_TEC_CTRL = 0;
int timeLoopPID_TEC_CTRL = 100;
bool isLoopPID_TEC_CTRL = false;

int timeLoopPID_MICROWAVE = 2;
bool isLoopPID_MICROWAVE = false;

float resultTec = 0.0f;							// Р С™РЎС“РЎР‚РЎвЂЎР В°Р Р…Р С•Р Р†
float resultMICROWAVE = 0.0f;
float resultDOPLER_FREQ = 0.0f;
float resultTemp_CELL = 0.0f;
float resultTemp_D_CELL = 0.0f;
float levelTemp_CELL = 2048.0f;
float levelTemp_D_CELL = 62.0f;
// Р СњР ВµР С•Р В±РЎвЂ¦Р С•Р Т‘Р С‘Р С�Р В°РЎРЏ РЎвЂљР ВµР С�Р С—Р ВµРЎР‚Р В°РЎвЂљРЎС“РЎР‚Р В° РЎРЏРЎвЂЎР ВµР в„–Р С”Р С‘
float levelValueSensor_TempCell = 62.00f;

int value_TC;
float value_D_TC;
float value_FAZA_L;
float value_FAZA_F;
int value_STEP_L;
int value_N_STEP_L = 1;
float value_mult_To_FREQ = 0.0f;
int i_MESSAGE_1 = 0;
int i_MESSAGE_2 = 0;
int i_MESSAGE_3 = 0;
float f_MESSAGE_2 = 0;
float f_MESSAGE_3 = 0;
bool b_MESSAGE = false;
bool b_eq = false;

int iF0 = 0;
int iT1__ = 0;
int iT2__ = 0;
int iT3__ = 0;
int iT4__ = 0;
int iT__n = 0;
uint32_t my_dat_1 = 0x0000f00f;
uint32_t my_dat_2 = 0x00001111;

uint16_t DMA1_Data[2*ADC_ARRAY_DMA1_HALF_SIZE];
uint16_t DMA2_Data[2*ADC_ARRAY_DMA2_HALF_SIZE];

uint16_t* pDataDMA1;
//uint16_t* pDataDMA2;
volatile uint16_t* volatile pDataDMA2;

// Kurchanov 23.11.2020
//=========================================================
// Р вЂќР В°РЎвЂљРЎвЂЎР С‘Р С” РЎвЂљР ВµР С�Р С—Р ВµРЎР‚Р В°РЎвЂљРЎС“РЎР‚РЎвЂ№
//=========================================================
float value_TempCell = 0.0f;
float value_Temp_D_Cell = 0.0f;
bool TempCellIsCorrect = false;
int tickDelayUpdateTempCell = 0;
float resultAverage_SENSOR_TempCell = 0.0f;

// Kurchanov 03.08.2020
// __attribute__((aligned(8))); 8 - Р В±Р В°Р в„–РЎвЂљ Р Р†РЎвЂ№РЎР‚Р В°Р Р†Р Р…Р С‘Р Р†Р В°Р Р…Р С‘Р Вµ
// Р С—Р С• РЎС“Р С�Р С•Р В»РЎвЂЎР В°Р Р…Р С‘РЎР‹ Р ВµРЎРѓР В»Р С‘ Р Р…Р В°Р С—Р С‘РЎРѓР В°РЎвЂљРЎРЉ __attribute__((aligned));

// Kurchanov 2021.01.21
// Меняем полностью подход
// Буфер увеличенной длины теперь не для исходной порции DMA
// а для выхода OUT2 и режектированного по F1 сигнала перед
// его окончательной режекцией и по F2 также

// Kurchanov 16.04.2021
//*
uint16_t  my_DMA2_tst_Data[ADC_ARRAY_DMA2_HALF_SIZE]   __attribute__((aligned))	= {
		// Сюда помещаем модельный тестовый буфер длиной 360 полуслов
};
//*/

#ifdef my_ASM_fun
uint16_t  my_DMA2_Data[ADC_ARRAY_DMA2_HALF_SIZE]   __attribute__((aligned));
uint16_t  my_DMA2_Data_F0[ADC_ARRAY_DMA12_HALF_SIZE + 56] __attribute__((aligned));		// Буфер увеличенной длины сигнала OUT2 для последующей режекции частот модуляции
uint16_t  my_DMA2_Data_F1[ADC_ARRAY_DMA12_HALF_SIZE] __attribute__((aligned));			// Буфер нормальной длины сигнала OUT2 после режекции частоты F1 для детектирования частоты F2
uint16_t  my_DMA2_Data_F2[ADC_ARRAY_DMA12_HALF_SIZE + 30] __attribute__((aligned));		// Буфер увеличенной длины сигнала OUT2 после режекции частоты F2 для детектирования частоты F1
uint16_t  my_DMA2_Data_F1_F2[ADC_ARRAY_DMA12_HALF_SIZE] __attribute__((aligned));		// Буфер нормальной длины сигнала OUT2 после режекции частот F1 и F2 для анализа шумов лазера
int32_t  my_F2F1_rez[6];
int32_t  my_F2F1_P_rez[6];
int32_t  my_F1F2_rez[5];
int32_t  my_F1F2_P_rez[5];
float F1F2_rezult[5];
float F1F2_OUT1_rezult[5];
float F1F2_P_rezult[5];
float F1F2_P_S;
float F2F1_rezult[6];
bool b_F2F1_rezult = false;
float F2F1_rezult_1[6];
float F2F1_rezult_2[6];
float F2F1_rezult_D[6];
float F2F1_P_rezult[6];
int32_t  my_F2F1_sum[6];
int32_t  my_F2F1_P_sum[6];
int32_t  my_F1F2_sum[5];
int32_t  my_F1F2_OUT1_sum[5];
int32_t  my_F1F2_P_sum[5];
int32_t  my_F0_sum;
#endif

uint16_t buf_TEST_ADC_3[2400] __attribute__((aligned));
bool b_buf_TEST_ADC_3 = false;
bool b_buf_TEST_ADC_2 = false;
float corr_1_TEST_ADC_2 = 0;
float corr_2_TEST_ADC_2 = 0;
float corr_12_TEST_ADC_2 = 0;
float corr_TEST_ADC_2 = 0;
int num_corr_TEST_ADC_2 = 0;
int pkgPos = 0;		// Номер посылки из 16 значений
int numPos = 0;		// Номер позиции в длинном буфере
float result_OUT2_CPT_FREQ_CPT_tmp;
float result_OUT2_CPT_CRNT_DOPLER_tmp;

// Kurchanov (19.10.2020) 12.01.2021
#ifdef my_C_fun
uint16_t  my_DMA2_Data_[ADC_ARRAY_DMA2_HALF_SIZE]   __attribute__((aligned));
uint16_t  my_DMA2_Data_F0_[ADC_ARRAY_DMA12_HALF_SIZE + 56] __attribute__((aligned));	// Буфер увеличенной длины сигнала OUT2 для последующей режекции частот модуляции
uint16_t  my_DMA2_Data_F1_[ADC_ARRAY_DMA12_HALF_SIZE] __attribute__((aligned));			// Буфер нормальной длины сигнала OUT2 после режекции частоты F1 для детектирования частоты F2
uint16_t  my_DMA2_Data_F2_[ADC_ARRAY_DMA12_HALF_SIZE + 30] __attribute__((aligned));	// Буфер увеличенной длины сигнала OUT2 после режекции частоты F2 для детектирования частоты F1
uint16_t  my_DMA2_Data_F1_F2_[ADC_ARRAY_DMA12_HALF_SIZE] __attribute__((aligned));		// Буфер нормальной длины сигнала OUT2 после режекции частот F1 и F2 для анализа шумов лазера



int32_t  my_F2F1_rez_[6];
int32_t  my_F1F2_rez_[5];
// Kurchanov 13.01.2021
uint16_t max_Data_F0_;
uint16_t min_Data_F0_;
uint16_t max_Data_F1_;
uint16_t min_Data_F1_;
uint16_t max_Data_F2_;
uint16_t min_Data_F2_;
uint16_t max_Data_F1_F2_;
uint16_t min_Data_F1_F2_;
int32_t  sum_ampl_Data_F0_ = 0;
int32_t  sum_ampl_Data_F1_ = 0;
int32_t  sum_ampl_Data_F2_ = 0;
int32_t  sum_ampl_Data_F1_F2_ = 0;
float  rez_ampl_Data_F0_;
float  rez_ampl_Data_F1_;
float  rez_ampl_Data_F2_;
float  rez_ampl_Data_F1_F2_;

float F1F2_rezult_[5];
float F2F1_rezult_[6];
int32_t  my_F2F1_sum_[6];
int32_t  my_F1F2_sum_[5];
int32_t  my_F0_sum_;
#endif

// Р Т‘Р В»РЎРЏ РЎвЂћРЎС“Р Р…Р С”РЎвЂ Р С‘Р в„– Р Р…Р В° Р В°РЎРѓРЎРѓР ВµР С�Р В±Р В»Р ВµРЎР‚Р Вµ
//uint16_t* p_my_DMA2_Data;
//uint16_t* p_my_DMA2_Data_F0;
//uint16_t* p_my_DMA2_Data_F1;
//uint16_t* p_my_DMA2_Data_F2;
//uint16_t* p_my_DMA2_Data_F1_F2;
//int32_t* p_my_F2F1_rez;
//int32_t* p_my_F1F2_rez;
int32_t* p_my_F2F1_sum;
int32_t* p_my_F1F2_sum;
int32_t* p_my_F1F2_OUT1_sum;

// Р Т‘Р В»РЎРЏ РЎвЂћРЎС“Р Р…Р С”РЎвЂ Р С‘Р в„– Р Р…Р В° C
uint16_t* p_my_DMA2_Data_;
uint16_t* p_my_DMA2_Data_F0_;
uint16_t* p_my_DMA2_Data_F1_;
uint16_t* p_my_DMA2_Data_F2_;
uint16_t* p_my_DMA2_Data_F1_F2_;
int32_t* p_my_F2F1_rez_;
int32_t* p_my_F1F2_rez_;
int32_t* p_my_F2F1_sum_;
int32_t* p_my_F1F2_sum_;

uint8_t itemPartResultDMA1_ADC1 = 0;
uint8_t itemPartResultDMA2_ADC2 = 0;

int resultData_OUT_1R[2*COUNT_DATA_HALF_SIZE_OUT_1R];
int resultData_CONTR[2*COUNT_DATA_HALF_SIZE_CONTR];
int resultData_SD1[2*COUNT_DATA_HALF_SIZE_SD1];
int resultData_OUT_3R[2*COUNT_DATA_HALF_SIZE_OUT_3R];

int resultData_OUT_2R[2*COUNT_DATA_HALF_SIZE_OUT_2R];
int resultData_OUT_0R[2*COUNT_DATA_HALF_SIZE_OUT_0R];
int resultData_SD2[2*COUNT_DATA_HALF_SIZE_SD2];

int itemMOD_CRNT = 0;
int itemMOD_FREQ = 0;
int MOD_CRNT_width = 200;

int sum_OUT_DC = 0;
int sum_CONTR = 0;
int sum_SD1 = 0;
int sum_OUT_3R = 0;

#ifdef my_ASM_fun
int sum_OUT_2R = 0;
int sum_OUT_0R = 0;
int sum_SD2 = 0;
#endif

#ifdef my_C_fun
int sum_OUT_2R_ = 0;
int sum_OUT_0R_ = 0;
int sum_SD2_ = 0;
#endif

int sum_OUT_2RN = 0;
int sum_OUT_0RN = 0;

int rez_OUT_2R = 0;

int * p_sum_OUT_DC = 0;
int * p_sum_OUT_1R = 0;
int * p_sum_CONTR = 0;
int * p_sum_SD1 = 0;
int * p_sum_OUT_3R = 0;

float fix_avrResult_OUT_DC = 0.0f;
float avrResult_OUT_DC = 0.0f;
float avrResult_OUT_1R = 0.0f;
float avrResult_CONTR = 0.0f;
float avrResult_SD1 = 0.0f;
float avrResult_SD1_ = 0.0f;
float avrResult_OUT_3R = 0.0f;
float startResult_OUT_3R = 0.0f;
float avrResult_OUT_2R = 0.0f;
float avrResult_OUT_0R  = 0.0f;
float avrResult_OUT_0R_ = 0.0f;
float avrResult_SD2 = 0.0f;

float avrResult_OUT2_DC = 0.0f;
float avrResult_OUT_0RN = 0.0f;

// Задаем минимальный период усреднения 16 миллисекунд
// для того, чтобы правильно работала очередь из 11 позиций
// 16*120 = 1920, 15 мс ==> 62,5 Гц
int count_OUT_DC = 1920;		// ??
int count_OUT_1R = 1920;		// Р Р†РЎвЂ№РЎвЂ¦Р С•Р Т‘ DC Р Т‘Р В»РЎРЏ OUT1
int count_CONTR  = 1920;		// Р Р†РЎвЂ№РЎвЂ¦Р С•Р Т‘ РЎвЂљР ВµР С�Р С—Р ВµРЎР‚Р В°РЎвЂљРЎС“РЎР‚РЎвЂ№ Р В»Р В°Р В·Р ВµРЎР‚Р В° Р С—Р С• Р ВµР С–Р С• РЎвЂљР ВµРЎР‚Р С�Р С•РЎР‚Р ВµР В·Р С‘РЎРѓРЎвЂљР С•РЎР‚РЎС“
int count_SD1 	 = 1920;			// Р Р…Р Вµ Р С‘РЎРѓР С—Р С•Р В»РЎРЉР В·РЎС“Р ВµРЎвЂљРЎРѓРЎРЏ
int count_OUT_3R = 1920;	// Р вЂќР ВµРЎвЂљР ВµР С”РЎвЂљР С•РЎР‚ Р РЋР вЂ™Р В§
int count_OUT_2R = 1920;		// OUT2
int count_OUT_0R = 1920;		// Р СћР ВµР С�Р С—Р ВµРЎР‚Р В°РЎвЂљРЎС“РЎР‚Р В° РЎРЏРЎвЂЎР ВµР в„–Р С”Р С‘
int count_SD2 	 = 1920;			// Р Р…Р Вµ Р С‘РЎРѓР С—Р С•Р В»РЎРЉР В·РЎС“Р ВµРЎвЂљРЎРѓРЎРЏ

int index_OUT_DC = 0;
//bool b_OUT_DC = false;
//int index_OUT_1R = 0;
int index_CONTR = 0;
int index_SD1 = 0;
int index_OUT_3R = 0;
int index_OUT_2R = 0;
//int index_OUT_2RN = 0;
int index_OUT_0R = 0;
int index_SD2 = 0;

//float result_OUT2_CPT[2] = {0.0, 0.0f};


//int sum_OUT2_CPT[2] = {0, 0};
//int index_OUT2_CPT = 0;
//int count_OUT2_CPT = 4*10;
bool flagUpdateCompute_OUT2_CPT = false;
int fixValue_OUT2_CPT = 0;

float shift_OUT2_DOPLER_CRNT = 0.0f;//36.3f;

int sum_OUT1_DOPLER_CRNT[2] = {0, 0};
int count_OUT1_DOPLER_CRNT = 1;
bool flagUpdateCompute_OUT1_DOPLER_CRNT = false;
float result_OUT1_DOPLER_CRNT = 0.0f;
int fixValue_OUT1_DOPLER_CRNT = 0;

//int sum_CPT_FREQ = 0;
//int index_CPT_FREQ = 0;
//int count_CPT_FREQ = 240;
//bool flagUpdateCompute_CPT_FREQ = false;
//float result_CPT_FREQ = 0.0f;

int sum_OUT1_CPT_CRNT[5] = {0, 0 , 0, 0, 0};
int sum_OUT2_CPT_CRNT[5] = {0, 0 , 0, 0, 0};
int sum_OUT1_CRNT_2[5] = {0, 0 , 0, 0, 0};
int sum_OUT2_CRNT_2[5] = {0, 0 , 0, 0, 0};
int index_OUT1_CPT_CRNT = 0;
int index_OUT2_CPT_CRNT = 0;
int count_OUT1_CPT_CRNT = 192;	// не используется
int count_OUT2_CPT_CRNT = 192;	// 16*12=192, 16 - миллисекунд (период усреднения)
// 62,5 Гц при выводе усреднять 6 раз ==>  вывод 10,417 Гц
bool flagUpdateCompute_OUT2_CPT_CRNT = false;
float result_OUT1_CPT_CRNT[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float result_OUT1_CRNT_2[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float result_OUT1_CPT_CRNT_DOPLER = 0.0f;
float result_OUT2_CPT_CRNT[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float result_OUT2_CRNT_2[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float result_OUT2_CPT_CRNT_DOPLER = 0.0f;
float delta_DOPLER_DC = 0.0f; // Kurchanov 08.05.2020

int sum_OUT2_CPT_FREQ[6] = {0, 0 , 0};
int index_OUT2_CPT_FREQ = 0;
int count_OUT2_CPT_FREQ = 160;	// 16*10=80, 16 - миллисекунд (период усреднения)
bool flagUpdateCompute_OUT2_CPT_FREQ = false;
bool flagUpdateCompute_FREQ_GNSS = true;
bool flagStartCompute_FREQ_GNSS = false;
float result_OUT2_CPT_FREQ[6] = {0.0f, 0.0f, 0.0f};
float result_OUT2_CPT_FREQ_CPT = 0.0f;


float shift_OUT2_FREQ = 0.0f;
// Kurchanov 29.05.2020
bool b_Start_Shift_Freq = false;
float shift_Lin_Freq = 0.0f;
float shift_Freq_GNSS = 0.0f;
float shift_Freq_GNSS_I = 0.0f;
// Р В Р В°Р В·Р С�Р В°РЎвЂ¦ = (426.600 + 694.300) = 1121, 39487 - 39067 = 420 Р вЂњРЎвЂ 
// Р С™РЎР‚РЎС“РЎвЂљР С‘Р В·Р Р…Р В° = (420 Р вЂњРЎвЂ /2)/1121 = 0.19 Р вЂњРЎвЂ /Р С”Р С•Р Т‘
// 10^-11 ==> 0,046 Р вЂњРЎвЂ  ==> 0,24 Р С”Р С•Р Т‘Р В°
float step_Freq_GNSS = 0.24f;//0.24f;//0.24f;	// Tolik 06_11_2020
// РЎРѓР С�Р ВµРЎвЂ°Р ВµР Р…Р С‘Р Вµ -23 Р Т‘Р В°Р ВµРЎвЂљ РЎС“Р С�Р ВµР Р…РЎРЉРЎв‚¬Р ВµР Р…Р С‘Р Вµ РЎвЂЎР В°РЎРѓРЎвЂљР С•РЎвЂљРЎвЂ№ Р Р…Р В° 10РЎвЂ¦10^-10
// Р С—Р В»Р В°Р Р†Р Р…Р С• Р Р† 0, РЎвЂЎР В°РЎРѓРЎвЂљР С•РЎвЂљР В° Р Р† Р С�Р С‘Р Р…РЎС“РЎРѓ Р Р…Р В° 2.7x10^-7, РЎРѓРЎвЂЎР ВµРЎвЂљРЎвЂЎР С‘Р С” Р Р† Р С�Р С‘Р Р…РЎС“РЎРѓ Р В·Р В° 1 РЎРѓР ВµР С”РЎС“Р Р…Р Т‘РЎС“ = 36
// 

int sum_OUT1_CPT_FREQ[6] = {0, 0 , 0, 0, 0 , 0};
int index_OUT1_CPT_FREQ = 0;
int count_OUT1_CPT_FREQ = 30;
bool flagUpdateCompute_OUT1_CPT_FREQ = false;
float result_OUT1_CPT_FREQ[6] = {0.0f, 0.0f, 0.0f};


int fixValue_CPT_FREQ = 0;


int DEBUG_maxDWT1 = 0;
int DEBUG_maxDWT2 = 0;
int DEBUG_maxDWT3 = 0;

int DEBUG_item_VY = 0;
int DEBUG_item_DTX = 0;
int DEBUG_item_RFI = 0;
int DEBUG_item_VT1 = 0;
//=========================================================
// Р вЂ�РЎС“РЎвЂћР ВµРЎР‚РЎвЂ№ Р Т‘Р В»РЎРЏ РЎР‚Р В°Р В±Р С•РЎвЂљРЎвЂ№ РЎРѓ UART
//=========================================================
// Р РЋРЎвЂљРЎР‚Р С•Р С”Р В° Р Т‘Р В»РЎРЏ Р С•РЎвЂљР С—РЎР‚Р В°Р С”Р С‘
uint8_t UART_TxBuffer[255];
volatile uint8_t   	USART_tx_buffer[255];
volatile uint16_t   USART_tx_count = 0; // Р С™Р С•Р В»Р С‘РЎвЂЎР ВµРЎРѓРЎвЂљР Р†Р С• Р Т‘Р В°Р Р…Р Р…РЎвЂ№РЎвЂ¦ Р Р…Р В° Р С•РЎвЂљР С—РЎР‚Р В°Р Р†Р С”РЎС“
volatile uint16_t   USART_tx_wr_index = 0; // Р пїЅР Р…Р Т‘Р ВµР С”РЎРѓ РЎвЂ¦Р Р†Р С•РЎРѓРЎвЂљР В° Р В±РЎС“РЎвЂћР ВµРЎР‚Р В° (Р С”РЎС“Р Т‘Р В° Р С—Р С‘РЎРѓР В°РЎвЂљРЎРЉ Р Т‘Р В°Р Р…Р Р…РЎвЂ№Р Вµ )
volatile uint16_t   USART_tx_rd_index = 0; // Р пїЅР Р…Р Т‘Р ВµР С”РЎРѓ Р Р…Р В°РЎвЂЎР В°Р В»Р В° Р В±РЎС“РЎвЂћР ВµРЎР‚Р В° (Р С•РЎвЂљР С”РЎС“Р Т‘Р В° РЎвЂЎР С‘РЎвЂљР В°РЎвЂљРЎРЉ Р Т‘Р В°Р Р…Р Р…РЎвЂ№Р Вµ)
volatile bool    		USART_tx_buffer_overflow = 0; // Р В¤Р В»Р В°Р С– Р С—Р ВµРЎР‚Р ВµР С—Р С•Р В»Р Р…Р ВµР Р…Р С‘РЎРЏ Р В±РЎС“РЎвЂћР ВµРЎР‚Р В°
// Р СџРЎР‚Р С‘Р Р…РЎРЏРЎвЂљР В°РЎРЏ РЎРѓРЎвЂљРЎР‚Р С•Р С”Р В° РЎРѓ Р С”Р С•Р С�Р В°Р Р…Р Т‘Р С•Р в„–
char UART_RxBuffer[255];
volatile uint8_t   	USART_rx_buffer[255];
volatile uint16_t   USART_rx_count = 0; // Р С™Р С•Р В»Р С‘РЎвЂЎР ВµРЎРѓРЎвЂљР Р†Р С• Р Т‘Р В°Р Р…Р Р…РЎвЂ№РЎвЂ¦ Р Р† Р С—РЎР‚Р С‘Р Р…РЎРЏРЎвЂљР С•Р С� Р В±РЎС“РЎвЂћР ВµРЎР‚Р Вµ
volatile uint16_t   USART_rx_wr_index = 0; // Р пїЅР Р…Р Т‘Р ВµР С”РЎРѓ РЎвЂ¦Р Р†Р С•РЎРѓРЎвЂљР В° Р В±РЎС“РЎвЂћР ВµРЎР‚Р В° (Р С”РЎС“Р Т‘Р В° Р С—Р С‘РЎРѓР В°РЎвЂљРЎРЉ Р Т‘Р В°Р Р…Р Р…РЎвЂ№Р Вµ )
volatile uint16_t   USART_rx_rd_index = 0; // Р пїЅР Р…Р Т‘Р ВµР С”РЎРѓ Р Р…Р В°РЎвЂЎР В°Р В»Р В° Р В±РЎС“РЎвЂћР ВµРЎР‚Р В° (Р С•РЎвЂљР С”РЎС“Р Т‘Р В° РЎвЂЎР С‘РЎвЂљР В°РЎвЂљРЎРЉ Р Т‘Р В°Р Р…Р Р…РЎвЂ№Р Вµ)
volatile bool    		USART_rx_buffer_overflow = 0; // Р В¤Р В»Р В°Р С– Р С—Р ВµРЎР‚Р ВµР С—Р С•Р В»Р Р…Р ВµР Р…Р С‘РЎРЏ Р В±РЎС“РЎвЂћР ВµРЎР‚Р В°


uint8_t BufferMsg[256];
uint16_t lengthBufferCmd = 0;
int byteUSART = -1;
int cmdID = 0;
int BufferDataPack[4];
