#ifndef _my_FUN
#define _my_FUN
/*
	Это заголовочный файл объявлений для
	моих функций на ассемблере
*/

#include <stdint.h>
#include "var.h"

//uint16_t * DMA2_Data_TMP;
 #ifdef my_ASM_fun
void my_tst_1(void);
void my_F0_S(void);
void my_DataADC2_0(void);	// пересылка
void my_DataADC2_2(void);	// разбор буфера на 3 части
void my_F1(void);			// режекция частоты F1 (период 30 = 5*6, 5 полупериодов по 6 отсчетов, период 12, частота 10 кГц - модуляция ЧАСТОТЫ)
void my_F1F2(void);			// синхронный детектор частоты F2 (12 кГц) после режектирования F1 (10 кГц), вычисление 1-й производной СПЕКТРА ПРОПУСКАНИЯ (дискриминатор ДЛИНЫ ВОЛНЫ)
void my_F1F2_P(void);		// находим суммы для частоты F2 (12 кГц) для вычисления производной дискриминатора ДЛИНЫ ВОЛНЫ (2-й производной СПЕКТРА ПРОПУСКАНИЯ)
void my_F2(void);			// режекция частоты F2 (период 25 = 5*5, 5 полупериодов по 5 отсчетов, период 10, частота 12 кГц - модуляция ДЛИНЫ ВОЛНЫ)
void my_F2F1(void);			// синхронный детектор частоты F1 (10 кГц) после режектирования F2 (12 кГц) детектируем ЧАСТОТУ
void my_F2F1_P(void);		// находим суммы для частоты F1 (10 кГц) для вычисления производной дискриминатора ЧАСТОТЫ
void my_F1_F2(void);		// режекция частоты F2 после режекции частоты F1
 #endif

//extern int32_t my_F2F1_rez[6];
//extern int32_t my_F1F2_rez[5];
//extern int32_t my_F0_sum;

 #ifdef my_C_fun
void my_DataADC2_1_(void);
void my_DataADC2_2_(void);
void my_F1_(void);
void my_F2_(void);
void my_F1F2_(void);
void my_F2F1_(void);
void my_F1_F2_(void);
 #endif

// 749

// Функции для сравнения результатов выполнения кода
// на С и на ассемблере, поэтапно
// создаем массивы для функций на ассемблере
// p_my_DMA2_Data
// p_my_DMA2_Data_F0
// p_my_DMA2_Data_F1
// p_my_DMA2_Data_F2
// p_my_DMA2_Data_F1_F2
//
// при этом массивы для функций на С
// p_my_DMA2_Data_
// p_my_DMA2_Data_F0_
// p_my_DMA2_Data_F1_
// p_my_DMA2_Data_F2_
// p_my_DMA2_Data_F1_F2
//
//
// 
 #ifdef my_EQ_test
void my_EQ_test_1();	// my_DataADC2_1_() на С и на ассемблере my_DataADC2_0()
void my_EQ_test_2();	// my_DataADC2_2_() на С и на ассемблере my_DataADC2_2()
void my_EQ_test_3();	// my_F1_() на С и на ассемблере my_F1()
void my_EQ_test_4();	// my_F2_() на С и на ассемблере my_F2()
void my_EQ_test_5();	// my_F1F2_() на С и на ассемблере my_F1F2()
void my_EQ_test_6();	// my_F2F1_() на С и на ассемблере my_F2F1()
void my_EQ_test_7();	// my_F1_F2_() на С и на ассемблере my_F1_F2()
 #endif

#endif
