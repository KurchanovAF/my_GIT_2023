// Это мои функции на ассемблере
// начата работа 27 июля 2020

// Функции вызываются внутри static inline void UpdateDataADC2(void){}
// в файле stm32l4xx_it.c (строка 573)
// void my_DataADC2_1(void);

// The DCQ directive allocates one or more eight-byte blocks of memory
// The DCD directive allocates one or more words of memory
// The DCW directive allocates one or more halfwords of memory
// The DCB directive allocates one or more bytes of memory

.cpu cortex-m4
.syntax unified
.thumb

//	.section	my_section_2, "awx"
		//	.section	.data	// ТАК НЕ РАБОТАЕТ !!
//	.balign	4

//   AREA my_section_2, CODE, READWRITE, COMDEF, ALIGN=2
// THUMB

//.ascii	"Tolik Учится"
//.byte	0b11101100	// binary
//.byte	098			// ovtal НЕ РАБОТАЕТ
//.byte	75			// decimal
//.byte	0xFA		// hexadecimal
//.float	3.17E-5		// float

//.global pDataDMA2
//pDataDMA2:
//.word	0x00000000
.extern pDataDMA2

.global p_my_DMA2_Data
p_my_DMA2_Data:
.word	0x00000000

.global	p_my_DMA2_Data_F0
p_my_DMA2_Data_F0:
.word	0x00000000

.global p_my_DMA2_Data_F1
p_my_DMA2_Data_F1:
.word	0x00000000

.global p_my_DMA2_Data_F2
p_my_DMA2_Data_F2:
.word	0x00000000

.global p_my_DMA2_Data_F1_F2
p_my_DMA2_Data_F1_F2:
.word	0x00000000

.global p_my_F2F1_rez
p_my_F2F1_rez:
.word	0x00000000

.global p_my_F1F2_rez
p_my_F1F2_rez:
.word	0x00000000

.global p_sum_OUT_2R
p_sum_OUT_2R:
.word	0x00000000

//.global p_sum_OUT_2R_
//p_sum_OUT_2R_:
//.word	0x0000FFFF

.global p_sum_OUT_1N
p_sum_OUT_1N:
.word	0x00000000

//.global p_sum_OUT_0R_
//p_sum_OUT_0R_:
//.word	0x0000FFFF

.global p_rez_OUT_2R
p_rez_OUT_2R:
.word	0x00000000

.global p_sum_SD2
p_sum_SD2:
.word	0x00000000

//.global p_sum_SD2_
//p_sum_SD2_:
//.word	0x0000FFFF
		
.global	my_0x0000FFFF
my_0x0000FFFF:
.word	0x0000FFFF

.global	my_DataADC2_0
.global	my_DataADC2_2	// Ok!
.global	my_F1
.global	my_F1F2
.global	my_F1F2_P
.global	my_F2
.global	my_F2F1
.global	my_F2F1_P
.global	my_F1_F2

.extern sum_OUT_0R

.extern	my_F0_sum          [DATA, SIZE = 4]
.extern	my_DMA2_Data       [DATA, SIZE = 4]
.extern	my_DMA2_Data_F0    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F1    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F2    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F1_F2 [DATA, SIZE = 4]

.extern my_DMA2_Data
	   
.extern	my_DMA2_Data_       [DATA, SIZE = 4]
.extern	my_DMA2_Data_F0_    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F1_    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F2_    [DATA, SIZE = 4]
.extern	my_DMA2_Data_F1_F2_ [DATA, SIZE = 4]
	   
//.extern	p_my_DMA2_Data
//.extern	p_my_DMA2_Data_F0  	[DATA, SIZE = 4]
//.extern	p_my_DMA2_Data_F1  	[DATA, SIZE = 4]
//.extern	p_my_DMA2_Data_F2  	[DATA, SIZE = 4]
//.extern	p_my_DMA2_Data_F1_F2  [DATA, SIZE = 4]
//.extern	p_my_F1F2_rez      [DATA, SIZE = 4]
//.extern	p_my_F2F1_rez      [DATA, SIZE = 4]

/*
.extern	p_my_DMA2_Data_     	[DATA, SIZE = 4]
.extern	p_my_DMA2_Data_F0_  	[DATA, SIZE = 4]
.extern	p_my_DMA2_Data_F1_  	[DATA, SIZE = 4]
.extern	p_my_DMA2_Data_F2_  	[DATA, SIZE = 4]
.extern	p_my_DMA2_Data_F1_F2_  [DATA, SIZE = 4]
.extern	p_my_F1F2_rez_      [DATA, SIZE = 4]
.extern	p_my_F2F1_rez_      [DATA, SIZE = 4]
//*/
	   
	   
//.extern	pDataDMA2
	   
//.extern	p_sum_OUT_2R		[DATA, SIZE = 4]
//.extern	p_sum_OUT_2R_		[DATA, SIZE = 4]
//.extern	p_sum_OUT_0R		[DATA, SIZE = 4]
//.extern	p_sum_OUT_0R_		[DATA, SIZE = 4]
//.extern	p_sum_SD2			[DATA, SIZE = 4]
//.extern	p_sum_SD2_		[DATA, SIZE = 4]
	   
// EXTERN p_rez_OUT_2R		[DATA, SIZE = 4]

//my_F2F1_rez	DCD	0x00000000
//my_F1F2_rez	DCD	0x00000000
//my_F0_sum	DCD	0x00000000
//	 ADC_ARRAY_DMA2_HALF_SIZE  = 360 отсчетов, а не байт !
//	 ADC_ARRAY_DMA12_HALF_SIZE = 120

.func	my_DataADC2_0
my_DataADC2_0:
//	; Пересылка буфера DMA

	STMFD  SP!, {R0 - R9}
//	; =========================
	LDR R1, =my_DMA2_Data	// ��� ��������
	LDR R2, =pDataDMA2		// ����� ������ 120*3*(16 ���)
	LDR R2, [R2]			// Без этого зависает, с этим - работает
	MOV R0, #30				// 360 = 120*3 = 12*30
my_DataADC2_0_L1:
    LDMIA R2!, {R4-R9}		//  6 слов = 12 полуслов
    // Тест записи в my_DMA2_Data проходит верно
    //MOV	R4, 0x000000FF
    //MOV	R5, 0x0000AEAE
    //MOV	R6, 0x000000FF
    //MOV	R7, 0x0000AEAE
    //MOV	R8, 0x000000FF
    //MOV	R9, 0x0000AEAE
	STMIA R1!, {R4-R9}
	SUB R0, R0, #1
	CMP R0, #0
	BNE my_DataADC2_0_L1
//	Пересылка буфера DMA завершена
//	===========================
    LDMIA  SP!, {R0-R9}
	BX  LR
.endfunc


// Данные в DMA1_Data идут в следующем порядке: OUT_1R, CONTR, SD1, OUT_3R
// Данные в DMA2_Data идут в следующем порядке: OUT_2R, OUT_0R, SD2
// OUT_0R - выход аппаратного синхронного детектора 1
// SD1    - опорный уровень для аппаратных синхронных детекторов 1 и 2
// SD2    - выход аппаратного синхронного детектора 2
// OUT_3R - выход детектора мощности СВЧ, подаваемой на лазер (без усиления)
// CONTR  - выход усилителя моста датчика температуры лазера
.func
my_DataADC2_2:
	// Разбор сигналов на 3 разные части
	// Сохранение части №1 (выход OUT2)в массив my_DMA2_Data_F0
	// Суммирование для частей №2 (sum_OUT_2R_) и №3 (sum_OUT_0R) по отдельности
	STMDB  SP!, {R0-R12, LR}
	// Вначале сохраняем 56 старых отсчетов в массиве my_DMA2_Data_F0
	LDR R2, =my_DMA2_Data_F0
	ADD R1, R2, #240		//  120*2 = 240
	MOV R0, #4				//  14*4 = 56 полуслов

my_DataADC2_2_L1:
	LDMIA R1!, {R4-R10}		//  7 слов = 14 полуслов
	STMIA R2!, {R4-R10}
	// ==========================
	SUB R0, R0, #1
    CMP R0, #0
	BNE my_DataADC2_2_L1

	// ==========================
	// LR  - сумматор для sum_OUT_2R
	// R11 - сумматор для sum_OUT_0R
	// R12 - сумматор для sum_SD2
	// =========================

	LDR R1, =my_DMA2_Data
	MOV R11, #0
	MOV R12, #0
	MOV LR,  #0
	LDR R3, my_0x0000FFFF		// константа
	// R4 - вспомогательный
	LDMIA R1!, {R8-R10}
	MOV R0, #60

my_DataADC2_2_L2:
    MOV R5, R8
	MOV R6, R9
	MOV R7, R10
    LDMIA R1!, {R8-R10}			// 3 слова = 6 полуслов
    STRH R5, [R2]				// полуслово для my_DMA2_Data_F0
	AND  R4, R5, R3
	ADD LR, LR, R4
	ADD R2, R2, #2				// сумматор для sum_OUT_2R
	
	MOVS R4, R5, LSR #16
	ADD R11, R11, R4			// сумматор для sum_OUT_0R
	
	AND R4, R6, R3
	ADD R12, R12, R4			// сумматор для sum_SD2
	
	MOVS R4, R6, LSR #16
    STRH R4, [R2]				// полуслово для my_DMA2_Data_F0
	AND  R4, R4, R3
	ADD LR, LR, R4
	ADD R2, R2, #2				// сумматор для sum_OUT_2R
	
	AND R4, R7, R3
	ADD R11, R11, R4			// сумматор для sum_OUT_0R
	
	MOVS R4, R7, LSR #16
	ADD R12, R12, R4			// сумматор для sum_SD2
	
	SUB R0, R0, #1
    // Эти 6 полуслов равны 12 байтам и передачу нужно повторить 60 раз
    // (720 байт в буфере my_DMA2_Data)
	CMP R0, #0
	BNE my_DataADC2_2_L2
	// Разбор буфера на 3 части окончен

	//LDR R1, p_sum_OUT_2R_
	//STR LR, [R1]
	LDR R1, =p_sum_OUT_2R
	LDR R2, [R1]
	ADD R2, R2, LR
	STR R2, [R1]
	//

	//LDR R1, p_sum_OUT_0R_
	//STR R11, [R1]
	LDR R1, =sum_OUT_0R			// адрес объекта sum_OUT_0R
	LDR R2, [R1]				// значение величины sum_OUT_0R
	ADD R2, R2, R11
	STR R2, [R1]
	//
	//LDR R1, p_sum_SD2_
	//STR R12, [R1]
	LDR R1, =p_sum_SD2
	LDR R2, [R1]
	ADD R2, R2, R12
	STR R2, [R1]
	// =========================
    LDMIA  SP!, {R0-R12, LR}		// 1+13=14
	BX  LR						// 1
.endfunc

.func
my_F1:
	// Режекция частоты F1 = 10 кГц (модуляция для ЧАСТОТЫ)
	// Сохранение результата в массив my_DMA2_Data_F1
	//
	// 120 + 6 + 5 + (1 просто так)
	// 120 + 6 для F1 126 = 3*42
	// 120 +5 + (1 просто так) для F2 126 = 3*42
	// 120 для F1_F2
	//
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// LR - не изменяем
	// =========================
	MOV LR, #12					// 120 полуслов в выходном буфере
	LDR R0, =my_DMA2_Data_F0	// 	адрес начала входного буфера
	ADD R0, R0, #52				// 52 = 26*2
	ADD R1, R0, #60				// 60 = 30*2
    LDR R2, =my_DMA2_Data_F1	//	адрес начала массива для результата
    // смещение при режекции равно 30 отсчетов
	//
my_F1_L1:
	LDMIA R0!, {R3-R7  }			// 3 слова = 6 полуслов
    LDMIA R1!, {R8-R12 }			// 3 слова = 6 полуслов R13 = LR

	ADD R3, R3, R8
    STR R3, [R2]
	ADD R2, R2, #4

	ADD R4, R4, R9
    STR R4, [R2]
	ADD R2, R2, #4

	ADD R5, R5, R10
    STR R5, [R2]
	ADD R2, R2, #4
	
	ADD R6, R6, R11
    STR R6, [R2]
	ADD R2, R2, #4
	
	ADD R7, R7, R12
    STR R7, [R2]
	ADD R2, R2, #4

	// сохранили 5 слов, 10 полуслов

	SUB LR, LR, #1
	CMP LR, #0
	BNE my_F1_L1
	//
	// Режекция частоты F1 с периодом 12 отсчетов окончена
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

.func
my_F2:
	// Режекция частоты F2 = 12 кГц
	// Сохранение результата в массив my_DMA2_Data_F1
	//
	// период = 10, 5/2 периода = 25
	// длина my_DMA2_Data_F0 = 176*3 полуслов = 88*3 слов
	// длина my_DMA2_Data_F1 = 150 = 120 + 30
	//
	STMDB  SP!, {R0-R12, LR}
	// =========================
	//
	MOV LR, #25					// 150 = 6*25
	//
	LDR R0, =my_DMA2_Data_F2	//	адрес начала массива для результата
	LDR R1, =my_DMA2_Data_F0	//	адрес начала (120+56)*3*(32 бит)
	//
	//ADD R1, R1, #2			нельзя, не кратно 4
	ADD R2, R1, #52				// 52 = 26*2
	MOV R9, #0
	//
	LDMIA R1!, {R3}				// 1 слово = 2 полуслова
my_F2_L1:
	LDMIA R1!, {R4-R6}			// 4 слова = 8 полуслов
	LDMIA R2!, {R7-R9}			// 3 слова = 6 полуслов
	//
	//							   не использовано				A1D
	MOVS R10, R3, LSR #16		// старшее полуслово 			A1U
	MOVS R11, R4, LSL #16		// младшее полуслово			A2D
	ADD  R7, R7, R10			// добавляем к младшей части 	B1D
	MOVS R12, R4, LSR #16		// старшее полуслово			A2U
	ADD  R7, R7, R11			// добавляем к старшей части	B1U
	ADD  R8, R8, R12			// добавляем к младшей части	B2D
	MOVS R10, R5, LSL #16		// младшее полуслово			A3D
	ADD  R8, R8, R10			// добавляем к старшей части	B2U
	STR  R7, [R0]				// результат, слово №1			C1
	ADD  R0, R0, #4				// новый адрес для результата
	MOVS R10, R5, LSR #16		// старшее полуслово			A3U
	//
	STR  R8, [R0]				// результат, слово №2			C2
	ADD  R0, R0, #4				// новый адрес для результата
	//
	ADD  R9, R9, R10			// добавляем к младшей части	B3D
	MOVS R11, R6, LSL #16		// младшее полуслово			A3D
	MOV  R3, R6					// старшее полуслово будет обработано
								// в начале следующего цикла
	ADD  R9, R9, R11			// добавляем к старшей части	B3U
	SUB LR, LR, #1				// 1
	STR  R9, [R0]				// результат, слово №3
	ADD  R0, R0, #4				// новый адрес для результата
	//
	CMP LR, #0					// 1
	//
	BNE my_F2_L1
	// Режекция частоты F2 с периодом 10 отсчетов окончена
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

// 5 фаз, половина периода =5 это "ДЛИНА ВОЛНЫ = F2"
// 6 фаз, половина периода =6 это "ЧАСТОТА	   = F1"
// 12 положительных и 12 отрицательных разностей, всего 24 в сумме
.func
my_F1F2:
	// синхронный детектор частоты F1 после режектирования F2
	STMDB  SP!, {R0-R12, LR}
	// =========================
	MOV R0, #12	// счетчик циклов
	LDR R1, =my_DMA2_Data_F1	//	адрес начала (120)*(16 бит)
	// R1 - адрес для p_my_DMA2_Data_F1[6]

	//LDR R14, =0x0000FFFF	// так зависает
	LDR R14, my_0x0000FFFF	// так не зависает
	//
	MOV R8,	 #0		// сумматор №1
	MOV R9,  #0		// сумматор №2
	MOV R10, #0		// сумматор №3
	MOV R11, #0		// сумматор №4
	MOV R12, #0		// сумматор №5
my_F1F2_L1:
    // в цикле 5 результатов суммирования разностей, всего нужно 120
	// цикл нужно повторять 12 раз
	LDMIA R1!, {R3-R7}		// загрузили 10 полуслов, в периоде 10 полуслов
							// в 1/2 периода 5 полуслов
	STMDB  SP!, {R0}		// освободили для вычислений
	// НАЧАЛО ВЫЧ�?СЛЕН�?Я 5 ПРЯМЫХ ФАЗ, половина периода
	// R15 == LR
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[0]
	SUB  R2, R0, R2
	ADD  R8, R8, R2			// сумматор №1 ВЕРНО

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - свободен
	SUB  R2, R0, R2
	ADD  R9, R9, R2			// сумматор №2 ВЕРНО
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6
	MOV R6, R7				// R7 - теперь не определен
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[2]
	SUB  R2, R0, R2
	ADD  R10, R10, R2		// сумматор №3 ОШ�?БКА (отличие на 1)

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - свободен
	SUB  R2, R0, R2
	ADD  R11, R11, R2		// сумматор №4 ВЕРНО
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6				// R6 - теперь не определен
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[4]
	SUB  R2, R0, R2
	ADD  R12, R12, R2		// сумматор №5 ОШ�?БКА (отличие на 2)
	//
	//
	//
	LDMIA  SP!, {R0}
	SUB R0, R0, #1
	CMP R0, #0
	BNE my_F1F2_L1
	// =========================
	LDR R2, =my_F1F2_rez	//	адрес сумматора разностей №1 (далее до №5)
	STR R8, [R2]
	ADD R2, R2, #4
	STR R9, [R2]
	ADD R2, R2, #4
	STR R10, [R2]
	ADD R2, R2, #4
	STR R11, [R2]
	ADD R2, R2, #4
	STR R12, [R2]
	//
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

//========================================
.func
my_F1F2_P:
	// синхронный детектор 2-й гармоники частоты F1 после режектирования F2
	// детектируем частоту с половиной периода 6 тактов
	// детектируем 2-ю производную спектра пропускания ячейки
	// отличие от my_F1F2 - вместо 6 фаз разностей находим 6 фаз сумм,
	// а уже потом эти суммы будут превращаться в разности....
	STMDB  SP!, {R0-R12, LR}
	// =========================
	MOV R0, #12	// счетчик циклов
	LDR R1, =my_DMA2_Data_F1	//	адрес начала (120)*(16 бит)
	// R1 - адрес для p_my_DMA2_Data_F1[6]

	//LDR R14, =0x0000FFFF	// так зависает
	LDR R14, my_0x0000FFFF	// так не зависает
	//
	MOV R8,	 #0		// сумматор №1
	MOV R9,  #0		// сумматор №2
	MOV R10, #0		// сумматор №3
	MOV R11, #0		// сумматор №4
	MOV R12, #0		// сумматор №5
my_F1F2_P_L1:
    // в цикле 5 результатов суммирования сумм, всего нужно 120
	// цикл нужно повторять 12 раз
	LDMIA R1!, {R3-R7}		// загрузили 10 полуслов, в периоде 10 полуслов
							// в 1/2 периода 5 полуслов
	STMDB  SP!, {R0}		// освободили для вычислений
	// НАЧАЛО ВЫЧИСЛЕНИЯ 5 ПРЯМЫХ ФАЗ, половина периода
	// R15 == LR
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[0]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2			// младшее полуслово из R3 плюс старшее полуслово из R5, разница 5 отсчетов АЦП
	ADD  R8, R8, R2			// сумматор №1 ВЕРНО

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - свободен
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R9, R9, R2			// сумматор №2 ВЕРНО
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6
	MOV R6, R7				// R7 - теперь не определен
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[2]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R10, R10, R2		// сумматор №3 ОШ�?БКА (отличие на 1)

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - свободен
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R11, R11, R2		// сумматор №4 ВЕРНО
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6				// R6 - теперь не определен
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// в младшей половине R3 my_DMA2_Data_F1_[4]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R12, R12, R2		// сумматор №5 ОШ�?БКА (отличие на 2)
	//
	//	сейчас R1 указывает на позицию 0 + 10 = 10
	//
	LDMIA  SP!, {R0}
	SUB R0, R0, #1
	CMP R0, #0
	BNE my_F1F2_P_L1
	// =========================
	LDR R2, =my_F1F2_P_rez	//	адрес сумматора разностей №1 (далее до №5)
	STR R8, [R2]
	ADD R2, R2, #4
	STR R9, [R2]
	ADD R2, R2, #4
	STR R10, [R2]
	ADD R2, R2, #4
	STR R11, [R2]
	ADD R2, R2, #4
	STR R12, [R2]
	//
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

//========================================

.func
my_F2F1:
	// синхронный детектор частоты F2 после режектирования F1
	// детектируем частоту с половиной периода 5 тактов
	// детектируем ДЛ�?НУ ВОЛНЫ
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// =========================
	MOV R0, #10
	LDR R1,  =my_DMA2_Data_F2	//	адрес начала (120+30)*(16 бит)
	ADD R1, R1, #60				//  адрес для my_DMA2_Data_F2[0] (+30 отсчетов)
	LDR R7, my_0x0000FFFF		//  так не зависает

	MOV R8,	 #0		// сумматор №1
	MOV R9,  #0		// сумматор №2
	MOV R10, #0		// сумматор №3
	MOV R11, #0		// сумматор №4
	MOV R12, #0		// сумматор №5
	MOV R14, #0		// сумматор №6
	//
my_F2F1_L1:
    // в цикле 6 результатов суммирования разностей, всего нужно 120
	// цикл нужно повторять 10 раз
	//
	LDMIA R1!, {R3-R6}		// загрузили 8 полуслов, в периоде 12 полуслов
							// в 1/2 периода 6 полуслов
	STMDB  SP!, {R0}		// освободили для вычислений
	//
	//
	// НАЧАЛО ВЫЧ�?СЛЕН�?Я 6 ПРЯМЫХ ФАЗ, половина периода
	AND R0, R6, R7
	AND R2, R3, R7
	SUB R2, R0, R2
	ADD R8, R8, R2			// сумматор №1
	//
	MOVS R0, R6, LSR #16
	MOVS R2, R3, LSR #16
	SUB  R2, R0, R2
	ADD  R9, R9, R2			// сумматор №2
	//
	MOV R3, R4				// сдвиг на 1 слово
	MOV R4, R5
	MOV R5, R6
	LDMIA R1!, {R6}			// всего загружено 10 полуслов
	//
	AND R0,   R6, R7
	AND R2,   R3, R7
	SUB R2,   R0, R2
	ADD R10, R10, R2		// сумматор №3
	//
	MOVS R0,   R6, LSR #16
	MOVS R2,   R3, LSR #16
	SUB  R2,   R0, R2
	ADD  R11, R11, R2		// сумматор №4
	//
	MOV R3, R4				// сдвиг на 1 слово
	MOV R4, R5	// эту команду тут можно убрать, R4 не нужен
	MOV R5, R6	// эту команду тут можно убрать, R5 не нужен
	LDMIA R1!, {R6}			// всего загружено 12 полуслов
	//
	AND  R0,  R6, R7
	AND  R2,  R3, R7
	SUB  R2,  R0, R2
	ADD R12, R12, R2		// сумматор №5
	//
	MOVS  R0,  R6, LSR #16
	MOVS  R2,  R3, LSR #16
	SUB   R2,  R0, R2
	ADD  R14, R14, R2		// сумматор №6
	//
	LDMIA  SP!, {R0}
	//
	SUB R0, R0, #1		// 1
	CMP R0, #0			// 1
	BNE my_F2F1_L1		// 2
	// =========================
	LDR R2, =my_F2F1_rez	//	адрес сумматора разностей №1 (далее до №5)
	STR R8, [R2]
	ADD R2, R2, #4
	STR R9, [R2]
	ADD R2, R2, #4
	STR R10, [R2]
	ADD R2, R2, #4
	STR R11, [R2]
	ADD R2, R2, #4
	STR R12, [R2]
	ADD R2, R2, #4
	STR R14, [R2]
	//
    LDMIA  SP!, {R0-R12, LR}	// 1+13=14
	BX  LR
.endfunc

//===================================
.func
my_F2F1_P:
	// синхронный детектор 2-й гармоники частоты F2 после режектирования F1
	// детектируем частоту с половиной периода 5 тактов
	// детектируем производную от дискриминатора частоты
	// отличие от my_F2F1 - вместо 5 фаз разностей находим 5 фаз сумм,
	// а уже потом эти суммы будут превращаться в разности....
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// =========================
	MOV R0, #10
	LDR R1,  =my_DMA2_Data_F2	//	адрес начала (120+30)*(16 бит)
	ADD R1, R1, #60				//  адрес для my_DMA2_Data_F2[0] (+30 отсчетов)
	LDR R7, my_0x0000FFFF		//  так не зависает

	MOV R8,	 #0		// сумматор №1
	MOV R9,  #0		// сумматор №2
	MOV R10, #0		// сумматор №3
	MOV R11, #0		// сумматор №4
	MOV R12, #0		// сумматор №5
	MOV R14, #0		// сумматор №6
	//
my_F2F1_P_L1:
    // в цикле 6 результатов суммирования разностей, всего нужно 120
	// цикл нужно повторять 10 раз
	//
	LDMIA R1!, {R3-R6}		// загрузили 8 полуслов, в периоде 12 полуслов
							// в 1/2 периода 6 полуслов
	STMDB  SP!, {R0}		// освободили для вычислений
	//
	//
	// НАЧАЛО ВЫЧ�?СЛЕН�?Я 6 ПРЯМЫХ ФАЗ, половина периода
	AND R0, R6, R7
	AND R2, R3, R7
	//SUB R2, R0, R2
	ADD R2, R0, R2
	ADD R8, R8, R2			// сумматор №1
	//
	MOVS R0, R6, LSR #16
	MOVS R2, R3, LSR #16
	//SUB  R2, R0, R2
	ADD R2, R0, R2
	ADD  R9, R9, R2			// сумматор №2
	//
	MOV R3, R4				// сдвиг на 1 слово
	MOV R4, R5
	MOV R5, R6
	LDMIA R1!, {R6}			// всего загружено 10 полуслов
	//
	AND R0,   R6, R7
	AND R2,   R3, R7
	//SUB R2,   R0, R2
	ADD R2, R0, R2
	ADD R10, R10, R2		// сумматор №3
	//
	MOVS R0,   R6, LSR #16
	MOVS R2,   R3, LSR #16
	//SUB  R2,   R0, R2
	ADD R2, R0, R2
	ADD  R11, R11, R2		// сумматор №4
	//
	MOV R3, R4				// сдвиг на 1 слово
	MOV R4, R5	// эту команду тут можно убрать, R4 не нужен
	MOV R5, R6	// эту команду тут можно убрать, R5 не нужен
	LDMIA R1!, {R6}			// всего загружено 12 полуслов
	//
	AND  R0,  R6, R7
	AND  R2,  R3, R7
	//SUB  R2,  R0, R2
	ADD R2, R0, R2
	ADD R12, R12, R2		// сумматор №5
	//
	MOVS  R0,  R6, LSR #16
	MOVS  R2,  R3, LSR #16
	//SUB   R2,  R0, R2
	ADD R2, R0, R2
	ADD  R14, R14, R2		// сумматор №6
	//
	LDMIA  SP!, {R0}
	//
	SUB R0, R0, #1		// 1
	CMP R0, #0			// 1
	BNE my_F2F1_P_L1		// 2
	// =========================
	LDR R2, =my_F2F1_P_rez	//	адрес сумматора сумм №1 (далее до №5)
	STR R8, [R2]
	ADD R2, R2, #4
	STR R9, [R2]
	ADD R2, R2, #4
	STR R10, [R2]
	ADD R2, R2, #4
	STR R11, [R2]
	ADD R2, R2, #4
	STR R12, [R2]
	ADD R2, R2, #4
	STR R14, [R2]
	//
    LDMIA  SP!, {R0-R12, LR}	// 1+13=14
	BX  LR
.endfunc
//===================================


.func
my_F1_F2:
	// режекция частоты F2 после режекции частоты F1, интервал 30 отсчетов
	//
	// Сохранение результата в массив DMA2_Data_F1_F2
	//
	STMDB  SP!, {R0-R12, LR}
	// =========================
	//
	//MOV R0, #20
	// 150 полуслов = 75 слов = 4 + 57(=3*19) + 2
	// в последнем цикле чтение LDMIA R1!, {R7-R9}
	// и 4 команды MOV в конце не влияют ни на что - они лишние, но структуру портить не хочется
	//
	//LDR R1, =my_DMA2_Data_F1		//	адрес начала (120+30)*(16 бит)
    //LDR R2, =my_DMA2_Data_F1_F2		//	адрес начала массива для результата
	//
	//LDMIA R1!, {R3-R6}

	LDR R0, =my_DMA2_Data_F1_F2		//	адрес начала массива для результата
	LDR R1, =my_DMA2_Data_F2		//	адрес начала (120+30)*(16 бит)
	ADD R2, R1, #60					//  60 = 2*30, 30 отсчетов
	MOV	LR, #15						//  75 = 5*15

my_F1_F2_L1:
	LDMIA R1!, {R3-R7}				// 5 слов
	LDMIA R2!, {R8-R12}				// 5 слов
	ADD	R8,  R3, R8
	ADD R9,  R4, R9
	ADD R10, R5, R10
	ADD R11, R6, R11
	ADD R12, R7, R12
	STMIA R0!, {R8-R12}
	//
	SUB LR, LR, #1
	CMP LR, #0
	//
	BNE my_F1_F2_L1
	//
	// Режекция частоты F2 с периодом 10 отсчетов окончена
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc
		
.end
