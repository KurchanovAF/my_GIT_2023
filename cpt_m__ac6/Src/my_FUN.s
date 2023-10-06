// ��� ��� ������� �� ����������
// ������ ������ 27 ���� 2020

// ������� ���������� ������ static inline void UpdateDataADC2(void){}
// � ����� stm32l4xx_it.c (������ 573)
// void my_DataADC2_1(void);

// The DCQ directive allocates one or more eight-byte blocks of memory
// The DCD directive allocates one or more words of memory
// The DCW directive allocates one or more halfwords of memory
// The DCB directive allocates one or more bytes of memory

.cpu cortex-m4
.syntax unified
.thumb

//	.section	my_section_2, "awx"
		//	.section	.data	// ��� �� �������� !!
//	.balign	4

//   AREA my_section_2, CODE, READWRITE, COMDEF, ALIGN=2
// THUMB

//.ascii	"Tolik ������"
//.byte	0b11101100	// binary
//.byte	098			// ovtal �� ��������
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

.global p_sum_OUT_0R
p_sum_OUT_0R:
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
.extern sum_OUT_1N

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
//	 ADC_ARRAY_DMA2_HALF_SIZE  = 360 ��������, � �� ���� !
//	 ADC_ARRAY_DMA12_HALF_SIZE = 120

.func	my_DataADC2_0
my_DataADC2_0:
//	; ��������� ������ DMA

	STMFD  SP!, {R0 - R9}
//	; =========================
	LDR R1, =my_DMA2_Data	// ??? ????????
	LDR R2, =pDataDMA2		// ????? ?????? 120*3*(16 ???)
	LDR R2, [R2]			// ��� ����� ��������, � ���� - ��������
	MOV R0, #30				// 360 = 120*3 = 12*30
my_DataADC2_0_L1:
    LDMIA R2!, {R4-R9}		//  6 ���� = 12 ��������
    // ���� ������ � my_DMA2_Data �������� �����
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
//	��������� ������ DMA ���������
//	===========================
    LDMIA  SP!, {R0-R9}
	BX  LR
.endfunc


// ������ � DMA1_Data ���� � ��������� �������: OUT_1R, CONTR, SD1, OUT_3R
// ������ � DMA2_Data ���� � ��������� �������: OUT_2R, OUT_0R, SD2 	(��� ����)
// ������ � DMA2_Data ���� � ��������� �������: OUT_2R, OUT_1N, OUT_0R 	(��� �����)
// OUT_0R - ����� ����������� ����������� ��������� 1
// SD1    - ������� ������� ��� ���������� ���������� ���������� 1 � 2
// SD2    - ����� ����������� ����������� ��������� 2
// OUT_1N - ����� ������� DC ������� �������������
// OUT_3R - ����� ��������� �������� ���, ���������� �� ����� (��� ��������)
// CONTR  - ����� ��������� ����� ������� ����������� ������
.func
my_DataADC2_2:
	// ������ �������� �� 3 ������ �����
	// ���������� ����� �1 (����� OUT2)� ������ my_DMA2_Data_F0
	// ������������ ��� ������ �2 (sum_OUT_2R_) � �3 (sum_OUT_0R) �� �����������
	STMDB  SP!, {R0-R12, LR}
	// ������� ��������� 56 ������ �������� � ������� my_DMA2_Data_F0
	LDR R2, =my_DMA2_Data_F0
	ADD R1, R2, #240		//  120*2 = 240
	MOV R0, #4				//  14*4 = 56 ��������

my_DataADC2_2_L1:
	LDMIA R1!, {R4-R10}		//  7 ���� = 14 ��������
	STMIA R2!, {R4-R10}
	// ==========================
	SUB R0, R0, #1
    CMP R0, #0
	BNE my_DataADC2_2_L1

	// ==========================
	// LR  - �������� ��� sum_OUT_2R
	// R11 - �������� ��� sum_OUT_0R
	// R12 - �������� ��� sum_SD2
	// =========================

	LDR R1, =my_DMA2_Data
	MOV R11, #0
	MOV R12, #0
	MOV LR,  #0
	LDR R3, my_0x0000FFFF		// ���������
	// R4 - ���������������
	LDMIA R1!, {R8-R10}
	MOV R0, #60

my_DataADC2_2_L2:
    MOV R5, R8
	MOV R6, R9
	MOV R7, R10
    LDMIA R1!, {R8-R10}			// 3 ����� = 6 ��������
    STRH R5, [R2]				// ��������� ��� my_DMA2_Data_F0
	AND  R4, R5, R3
	ADD LR, LR, R4
	ADD R2, R2, #2				// �������� ��� sum_OUT_2R
	
	MOVS R4, R5, LSR #16
	ADD R11, R11, R4			// �������� ��� (sum_OUT_0R) sum_OUT_1N
	
	AND R4, R6, R3
	ADD R12, R12, R4			// �������� ��� (sum_SD2) sum_OUT_0R
	
	MOVS R4, R6, LSR #16
    STRH R4, [R2]				// ��������� ��� my_DMA2_Data_F0
	AND  R4, R4, R3
	ADD LR, LR, R4
	ADD R2, R2, #2				// �������� ��� sum_OUT_2R
	
	AND R4, R7, R3
	ADD R11, R11, R4			// �������� ��� sum_OUT_0R
	
	MOVS R4, R7, LSR #16
	ADD R12, R12, R4			// �������� ��� sum_SD2
	
	SUB R0, R0, #1
    // ��� 6 �������� ����� 12 ������ � �������� ����� ��������� 60 ���
    // (720 ���� � ������ my_DMA2_Data)
	CMP R0, #0
	BNE my_DataADC2_2_L2
	// ������ ������ �� 3 ����� �������

	//LDR R1, p_sum_OUT_2R_
	//STR LR, [R1]
	LDR R1, =p_sum_OUT_2R
	LDR R2, [R1]
	ADD R2, R2, LR
	STR R2, [R1]
	//

	//LDR R1, p_sum_OUT_0R_
	//STR R11, [R1]
	//LDR R1, =sum_OUT_0R			// ����� ������� sum_OUT_0R		��� ����
	LDR R1, =sum_OUT_1N			// ����� ������� sum_OUT_1N
	LDR R2, [R1]				// �������� �������� sum_OUT_0R
	ADD R2, R2, R11
	STR R2, [R1]
	//
	//LDR R1, p_sum_SD2_
	//STR R12, [R1]
	//LDR R1, =p_sum_SD2	��� ����
	LDR R1, =sum_OUT_0R
	LDR R2, [R1]
	ADD R2, R2, R12
	STR R2, [R1]
	// =========================
    LDMIA  SP!, {R0-R12, LR}		// 1+13=14
	BX  LR						// 1
.endfunc

.func
my_F1:
	// �������� ������� F1 = 10 ��� (��������� ��� �������)
	// ���������� ���������� � ������ my_DMA2_Data_F1
	//
	// 120 + 6 + 5 + (1 ������ ���)
	// 120 + 6 ��� F1 126 = 3*42
	// 120 +5 + (1 ������ ���) ��� F2 126 = 3*42
	// 120 ��� F1_F2
	//
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// LR - �� ��������
	// =========================
	MOV LR, #12					// 120 �������� � �������� ������
	//LDR R0, =my_DMA2_Data_F0	// ����� ������ �������� ������ ��� ����
	LDR R0, =my_Data_F0			// ����� ������ � ������� ������ �������� ������
	LDR R0, [R0]				// ����� ������ �������� ������ ��� �����
	ADD R0, R0, #52				// 52 = 26*2
	ADD R1, R0, #60				// 60 = 30*2
    //LDR R2, =my_DMA2_Data_F1	// ����� ������ ������� ��� ���������� ��� ����
    LDR R2, =my_Data_F1	// ����� ������ � ������� ������ ������� ��� ����������
    LDR R2, [R2]				// ����� ������ ������� ��� ���������� ��� �����
    // �������� ��� �������� ����� 30 ��������
	//
my_F1_L1:
	LDMIA R0!, {R3-R7  }			// 3 ����� = 6 ��������
    LDMIA R1!, {R8-R12 }			// 3 ����� = 6 �������� R13 = LR

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

	// ��������� 5 ����, 10 ��������

	SUB LR, LR, #1
	CMP LR, #0
	BNE my_F1_L1
	//
	// �������� ������� F1 � �������� 12 �������� ��������
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

.func
my_F2:
	// �������� ������� F2 = 12 ���
	// ���������� ���������� � ������ my_DMA2_Data_F1
	//
	// ������ = 10, 5/2 ������� = 25
	// ����� my_DMA2_Data_F0 = 176*3 �������� = 88*3 ����
	// ����� my_DMA2_Data_F1 = 150 = 120 + 30
	//
	STMDB  SP!, {R0-R12, LR}
	// =========================
	//
	MOV LR, #25					// 150 = 6*25
	//
	//LDR R0, =my_DMA2_Data_F2	//	����� ������ ������� ��� ���������� ��� ����
	LDR R0, =my_Data_F2			//
	LDR R0, [R0]				// ��� �����
	//LDR R1, =my_DMA2_Data_F0	//	����� ������ (120+56)*3*(32 ���)    ��� ����
	LDR R1, =my_Data_F0			//
	LDR R1, [R1]				// ��� �����
	//
	//ADD R1, R1, #2			������, �� ������ 4
	ADD R2, R1, #52				// 52 = 26*2
	MOV R9, #0
	//
	LDMIA R1!, {R3}				// 1 ����� = 2 ���������
my_F2_L1:
	LDMIA R1!, {R4-R6}			// 4 ����� = 8 ��������
	LDMIA R2!, {R7-R9}			// 3 ����� = 6 ��������
	//
	//							   �� ������������				A1D
	MOVS R10, R3, LSR #16		// ������� ��������� 			A1U
	MOVS R11, R4, LSL #16		// ������� ���������			A2D
	ADD  R7, R7, R10			// ��������� � ������� ����� 	B1D
	MOVS R12, R4, LSR #16		// ������� ���������			A2U
	ADD  R7, R7, R11			// ��������� � ������� �����	B1U
	ADD  R8, R8, R12			// ��������� � ������� �����	B2D
	MOVS R10, R5, LSL #16		// ������� ���������			A3D
	ADD  R8, R8, R10			// ��������� � ������� �����	B2U
	STR  R7, [R0]				// ���������, ����� �1			C1
	ADD  R0, R0, #4				// ����� ����� ��� ����������
	MOVS R10, R5, LSR #16		// ������� ���������			A3U
	//
	STR  R8, [R0]				// ���������, ����� �2			C2
	ADD  R0, R0, #4				// ����� ����� ��� ����������
	//
	ADD  R9, R9, R10			// ��������� � ������� �����	B3D
	MOVS R11, R6, LSL #16		// ������� ���������			A3D
	MOV  R3, R6					// ������� ��������� ����� ����������
								// � ������ ���������� �����
	ADD  R9, R9, R11			// ��������� � ������� �����	B3U
	SUB LR, LR, #1				// 1
	STR  R9, [R0]				// ���������, ����� �3
	ADD  R0, R0, #4				// ����� ����� ��� ����������
	//
	CMP LR, #0					// 1
	//
	BNE my_F2_L1
	// �������� ������� F2 � �������� 10 �������� ��������
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc

// 5 ���, �������� ������� =5 ��� "����� ����� = F2"
// 6 ���, �������� ������� =6 ��� "�������	   = F1"
// 12 ������������� � 12 ������������� ���������, ����� 24 � �����
.func
my_F1F2:
	// ���������� �������� ������� F1 ����� �������������� F2
	STMDB  SP!, {R0-R12, LR}
	// =========================
	MOV R0, #12	// ������� ������
	//LDR R1, =my_DMA2_Data_F1	// ����� ������ (120)*(16 ���)	 ��� ����
	LDR R1, =my_Data_F1			//
	LDR R1, [R1]				// ��� �����
	// R1 - ����� ��� p_my_DMA2_Data_F1[6]

	//LDR R14, =0x0000FFFF	// ��� ��������
	LDR R14, my_0x0000FFFF	// ��� �� ��������
	//
	MOV R8,	 #0		// �������� �1
	MOV R9,  #0		// �������� �2
	MOV R10, #0		// �������� �3
	MOV R11, #0		// �������� �4
	MOV R12, #0		// �������� �5
my_F1F2_L1:
    // � ����� 5 ����������� ������������ ���������, ����� ����� 120
	// ���� ����� ��������� 12 ���
	LDMIA R1!, {R3-R7}		// ��������� 10 ��������, � ������� 10 ��������
							// � 1/2 ������� 5 ��������
	STMDB  SP!, {R0}		// ���������� ��� ����������
	// ������ ���??����??� 5 ������ ���, �������� �������
	// R15 == LR
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[0]
	SUB  R2, R0, R2
	ADD  R8, R8, R2			// �������� �1 �����

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - ��������
	SUB  R2, R0, R2
	ADD  R9, R9, R2			// �������� �2 �����
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6
	MOV R6, R7				// R7 - ������ �� ���������
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[2]
	SUB  R2, R0, R2
	ADD  R10, R10, R2		// �������� �3 ��??��� (������� �� 1)

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - ��������
	SUB  R2, R0, R2
	ADD  R11, R11, R2		// �������� �4 �����
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6				// R6 - ������ �� ���������
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[4]
	SUB  R2, R0, R2
	ADD  R12, R12, R2		// �������� �5 ��??��� (������� �� 2)
	//
	//
	//
	LDMIA  SP!, {R0}
	SUB R0, R0, #1
	CMP R0, #0
	BNE my_F1F2_L1
	// =========================
	//LDR R2, =my_F1F2_rez	//	����� ��������� ��������� �1 (����� �� �5)	��� ����
	LDR R2, =my_F1F2_rez_A	//
	LDR R2, [R2]			// ��� �����
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
	// ���������� �������� 2-� ��������� ������� F1 ����� �������������� F2
	// ����������� ������� � ��������� ������� 6 ������
	// ����������� 2-� ����������� ������� ����������� ������
	// ������� �� my_F1F2 - ������ 6 ��� ��������� ������� 6 ��� ����,
	// � ��� ����� ��� ����� ����� ������������ � ��������....
	STMDB  SP!, {R0-R12, LR}
	// =========================
	MOV R0, #12	// ������� ������
	LDR R1, =my_DMA2_Data_F1	//	����� ������ (120)*(16 ���)
	// R1 - ����� ��� p_my_DMA2_Data_F1[6]

	//LDR R14, =0x0000FFFF	// ��� ��������
	LDR R14, my_0x0000FFFF	// ��� �� ��������
	//
	MOV R8,	 #0		// �������� �1
	MOV R9,  #0		// �������� �2
	MOV R10, #0		// �������� �3
	MOV R11, #0		// �������� �4
	MOV R12, #0		// �������� �5
my_F1F2_P_L1:
    // � ����� 5 ����������� ������������ ����, ����� ����� 120
	// ���� ����� ��������� 12 ���
	LDMIA R1!, {R3-R7}		// ��������� 10 ��������, � ������� 10 ��������
							// � 1/2 ������� 5 ��������
	STMDB  SP!, {R0}		// ���������� ��� ����������
	// ������ ���������� 5 ������ ���, �������� �������
	// R15 == LR
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[0]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2			// ������� ��������� �� R3 ���� ������� ��������� �� R5, ������� 5 �������� ���
	ADD  R8, R8, R2			// �������� �1 �����

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - ��������
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R9, R9, R2			// �������� �2 �����
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6
	MOV R6, R7				// R7 - ������ �� ���������
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[2]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R10, R10, R2		// �������� �3 ��??��� (������� �� 1)

    AND  R0, R6, R14
	MOVS R2, R3, LSR #16	// R3 - ��������
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R11, R11, R2		// �������� �4 �����
	//
	MOV R3, R4
	MOV R4, R5
	MOV R5, R6				// R6 - ������ �� ���������
	//
	MOVS R0, R5, LSR #16
	AND  R2, R3, R14		// � ������� �������� R3 my_DMA2_Data_F1_[4]
	//SUB  R2, R0, R2
	ADD  R2, R0, R2
	ADD  R12, R12, R2		// �������� �5 ��??��� (������� �� 2)
	//
	//	������ R1 ��������� �� ������� 0 + 10 = 10
	//
	LDMIA  SP!, {R0}
	SUB R0, R0, #1
	CMP R0, #0
	BNE my_F1F2_P_L1
	// =========================
	LDR R2, =my_F1F2_P_rez	//	����� ��������� ��������� �1 (����� �� �5)
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
	// ���������� �������� ������� F2 ����� �������������� F1
	// ����������� ������� � ��������� ������� 5 ������
	// ����������� ��??�� �����
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// =========================
	MOV R0, #10
	//LDR R1,  =my_DMA2_Data_F2	//	����� ������ (120+30)*(16 ���)					��� ����
	LDR R1,  =my_Data_F2		//
	LDR R1, [R1]				// 													��� �����
	ADD R1, R1, #60				//  ����� ��� my_DMA2_Data_F2[0] (+30 ��������)
	LDR R7, my_0x0000FFFF		//  ��� �� ��������

	MOV R8,	 #0		// �������� �1
	MOV R9,  #0		// �������� �2
	MOV R10, #0		// �������� �3
	MOV R11, #0		// �������� �4
	MOV R12, #0		// �������� �5
	MOV R14, #0		// �������� �6
	//
my_F2F1_L1:
    // � ����� 6 ����������� ������������ ���������, ����� ����� 120
	// ���� ����� ��������� 10 ���
	//
	LDMIA R1!, {R3-R6}		// ��������� 8 ��������, � ������� 12 ��������
							// � 1/2 ������� 6 ��������
	STMDB  SP!, {R0}		// ���������� ��� ����������
	//
	//
	// ������ ���??����??� 6 ������ ���, �������� �������
	AND R0, R6, R7
	AND R2, R3, R7
	SUB R2, R0, R2
	ADD R8, R8, R2			// �������� �1
	//
	MOVS R0, R6, LSR #16
	MOVS R2, R3, LSR #16
	SUB  R2, R0, R2
	ADD  R9, R9, R2			// �������� �2
	//
	MOV R3, R4				// ����� �� 1 �����
	MOV R4, R5
	MOV R5, R6
	LDMIA R1!, {R6}			// ����� ��������� 10 ��������
	//
	AND R0,   R6, R7
	AND R2,   R3, R7
	SUB R2,   R0, R2
	ADD R10, R10, R2		// �������� �3
	//
	MOVS R0,   R6, LSR #16
	MOVS R2,   R3, LSR #16
	SUB  R2,   R0, R2
	ADD  R11, R11, R2		// �������� �4
	//
	MOV R3, R4				// ����� �� 1 �����
	MOV R4, R5	// ��� ������� ��� ����� ������, R4 �� �����
	MOV R5, R6	// ��� ������� ��� ����� ������, R5 �� �����
	LDMIA R1!, {R6}			// ����� ��������� 12 ��������
	//
	AND  R0,  R6, R7
	AND  R2,  R3, R7
	SUB  R2,  R0, R2
	ADD R12, R12, R2		// �������� �5
	//
	MOVS  R0,  R6, LSR #16
	MOVS  R2,  R3, LSR #16
	SUB   R2,  R0, R2
	ADD  R14, R14, R2		// �������� �6
	//
	LDMIA  SP!, {R0}
	//
	SUB R0, R0, #1		// 1
	CMP R0, #0			// 1
	BNE my_F2F1_L1		// 2
	// =========================
	//LDR R2, =my_F2F1_rez	//	����� ��������� ��������� �1 (����� �� �5)	��� ����
	LDR R2, =my_F2F1_rez_A	//
	LDR R2, [R2]			// 												��� �����
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
	// ���������� �������� 2-� ��������� ������� F2 ����� �������������� F1
	// ����������� ������� � ��������� ������� 5 ������
	// ����������� ����������� �� �������������� �������
	// ������� �� my_F2F1 - ������ 5 ��� ��������� ������� 5 ��� ����,
	// � ��� ����� ��� ����� ����� ������������ � ��������....
	STMDB  SP!, {R0-R12, LR}	// 1+13=14
	// =========================
	MOV R0, #10
	LDR R1,  =my_DMA2_Data_F2	//	����� ������ (120+30)*(16 ���)
	ADD R1, R1, #60				//  ����� ��� my_DMA2_Data_F2[0] (+30 ��������)
	LDR R7, my_0x0000FFFF		//  ��� �� ��������

	MOV R8,	 #0		// �������� �1
	MOV R9,  #0		// �������� �2
	MOV R10, #0		// �������� �3
	MOV R11, #0		// �������� �4
	MOV R12, #0		// �������� �5
	MOV R14, #0		// �������� �6
	//
my_F2F1_P_L1:
    // � ����� 6 ����������� ������������ ���������, ����� ����� 120
	// ���� ����� ��������� 10 ���
	//
	LDMIA R1!, {R3-R6}		// ��������� 8 ��������, � ������� 12 ��������
							// � 1/2 ������� 6 ��������
	STMDB  SP!, {R0}		// ���������� ��� ����������
	//
	//
	// ������ ���??����??� 6 ������ ���, �������� �������
	AND R0, R6, R7
	AND R2, R3, R7
	//SUB R2, R0, R2
	ADD R2, R0, R2
	ADD R8, R8, R2			// �������� �1
	//
	MOVS R0, R6, LSR #16
	MOVS R2, R3, LSR #16
	//SUB  R2, R0, R2
	ADD R2, R0, R2
	ADD  R9, R9, R2			// �������� �2
	//
	MOV R3, R4				// ����� �� 1 �����
	MOV R4, R5
	MOV R5, R6
	LDMIA R1!, {R6}			// ����� ��������� 10 ��������
	//
	AND R0,   R6, R7
	AND R2,   R3, R7
	//SUB R2,   R0, R2
	ADD R2, R0, R2
	ADD R10, R10, R2		// �������� �3
	//
	MOVS R0,   R6, LSR #16
	MOVS R2,   R3, LSR #16
	//SUB  R2,   R0, R2
	ADD R2, R0, R2
	ADD  R11, R11, R2		// �������� �4
	//
	MOV R3, R4				// ����� �� 1 �����
	MOV R4, R5	// ��� ������� ��� ����� ������, R4 �� �����
	MOV R5, R6	// ��� ������� ��� ����� ������, R5 �� �����
	LDMIA R1!, {R6}			// ����� ��������� 12 ��������
	//
	AND  R0,  R6, R7
	AND  R2,  R3, R7
	//SUB  R2,  R0, R2
	ADD R2, R0, R2
	ADD R12, R12, R2		// �������� �5
	//
	MOVS  R0,  R6, LSR #16
	MOVS  R2,  R3, LSR #16
	//SUB   R2,  R0, R2
	ADD R2, R0, R2
	ADD  R14, R14, R2		// �������� �6
	//
	LDMIA  SP!, {R0}
	//
	SUB R0, R0, #1		// 1
	CMP R0, #0			// 1
	BNE my_F2F1_P_L1		// 2
	// =========================
	LDR R2, =my_F2F1_P_rez	//	����� ��������� ���� �1 (����� �� �5)
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
	// �������� ������� F2 ����� �������� ������� F1, �������� 30 ��������
	//
	// ���������� ���������� � ������ DMA2_Data_F1_F2
	//
	STMDB  SP!, {R0-R12, LR}
	// =========================
	//
	//MOV R0, #20
	// 150 �������� = 75 ���� = 4 + 57(=3*19) + 2
	// � ��������� ����� ������ LDMIA R1!, {R7-R9}
	// � 4 ������� MOV � ����� �� ������ �� �� ��� - ��� ������, �� ��������� ������� �� �������
	//
	//LDR R1, =my_DMA2_Data_F1		//	����� ������ (120+30)*(16 ���)
    //LDR R2, =my_DMA2_Data_F1_F2		//	����� ������ ������� ��� ����������
	//
	//LDMIA R1!, {R3-R6}

	//LDR R0, =my_DMA2_Data_F1_F2	//	����� ������ ������� ��� ����������		��� ����
	LDR R0, =my_Data_F1_F2			//
	LDR R0, [R0]					// 											��� �����
	//LDR R1, =my_DMA2_Data_F2		//	����� ������ (120+30)*(16 ���)			��� ����
	LDR R1, =my_Data_F2				//
	LDR R1, [R1]					// 											��� �����
	ADD R2, R1, #60					//  60 = 2*30, 30 ��������
	MOV	LR, #15						//  75 = 5*15

my_F1_F2_L1:
	LDMIA R1!, {R3-R7}				// 5 ����
	LDMIA R2!, {R8-R12}				// 5 ����
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
	// �������� ������� F2 � �������� 10 �������� ��������
	// =========================
    LDMIA  SP!, {R0-R12, LR}
	BX  LR
.endfunc
		
.end
