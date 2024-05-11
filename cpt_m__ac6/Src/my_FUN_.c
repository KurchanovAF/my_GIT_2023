#include "var.h"
#include "my_FUN.h"

	//my_F1_();		// 6323 тактов (с поиском экстемумов)
	//my_F2_();		// 6708 тактов (с поиском экстемумов)
	//my_F1F2_();		//  969 тактов
	//my_F2F1_();		// 1057 тактов, измеренная сумма = 14808
	//my_F1_F2_();	// 3642 тактов (без поиска экстемумов)

#ifdef my_EQ_test
extern volatile uint16_t* volatile pDataDMA2;

void my_EQ_test_1()
{
	// 360+3*55=525
	for(int i = 0; i < 360; i++)
	{
		if(my_DMA2_Data_[i] != my_DMA2_Data[i])
		{
			b_eq = false;
		}
	}
};

void my_EQ_test_2()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 176; i++)
	{
		if(my_DMA2_Data_F0_[i] != my_DMA2_Data_F0[i])
		{
			b_eq = false;
		}
	}
};

void my_EQ_test_3()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 120; i++)
	{
		if(my_DMA2_Data_F1_[i] != my_DMA2_Data_F1[i])
		{
			b_eq = false;
		}
	}
};

void my_EQ_test_4()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 150; i++)
	{
		if(my_DMA2_Data_F2_[i] != my_DMA2_Data_F2[i])
		{
			b_eq = false;
		}
	}
};

void my_EQ_test_5()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 5; i++)
	{
		if(my_F1F2_rez_[i] != my_F1F2_rez[i])
		{
			b_eq = false;
		}
	}
};

void my_EQ_test_6()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 6; i++)
	{
		if(my_F2F1_rez_[i] != my_F2F1_rez[i]) b_eq = false;
	}
};

void my_EQ_test_7()
{
	//b_eq = true;
	int i;
	for(i = 0; i < 120; i++)
	{
		if(my_DMA2_Data_F1_F2_[i] != my_DMA2_Data_F1_F2[i]) b_eq = false;
	}
};
#endif

#ifdef my_C_fun

void my_DataADC2_1_()
{
	for(int i = 0; i < ADC_ARRAY_DMA2_HALF_SIZE; i++)
	{
		my_DMA2_Data_[i] = pDataDMA2[i];
	}
}

void my_DataADC2_2_()
{
	// При режекции используются суммы с разносом в 5/2 периода
	// 165 = 3*55, 55 = 30 + 25, 30 = 12*5/2, 25 = 10*5/2
	// однако, замена 55 на 56 позволяет выровнять данные на границу слова
	//
	for(int i = 0; i < 56; i++)
	{
		my_DMA2_Data_F0_[i] = my_DMA2_Data_F0_[i + 120];
	}
	for(int i = 0; i < 120; i++)
	{
		sum_OUT_2R_ +=
				my_DMA2_Data_F0_[i + 56] = my_DMA2_Data_[3*i + 0];
		sum_OUT_0R_ += my_DMA2_Data_[3*i + 1];
		sum_SD2_	+= my_DMA2_Data_[3*i + 2];
	}
}

void my_F1_()
{
	uint16_t	uiH;
	// +5 отсчетов, 120 + 5 = 125
	// Анализируем на участке длиной 120 отсчетов
	max_Data_F1_ = 0;
	min_Data_F1_ = 0;
	for(int i = 0; i < 120; i++)
	{
		my_DMA2_Data_F1_[i] = uiH =
		  my_DMA2_Data_F0_[i + 26] +
		  my_DMA2_Data_F0_[i + 56];
		// 5/2 периода для 10 кГц = 30
		//if(max_Data_F1_ <= uiH) max_Data_F1_ = uiH;
		//if(min_Data_F1_ >= uiH) min_Data_F1_ = uiH;
	}
}

void my_F2_()
{
	uint16_t	uiH;
	// +30 отсчетов, 120 + 30 = 150
	for(int i = 0; i < 30; i++)
	{
		my_DMA2_Data_F2_[i] =
			my_DMA2_Data_F0_[i + 1] +
			my_DMA2_Data_F0_[i + 26];
			// 5/2 периода для 12 кГц = 25
			// ВАЖНО - начало массива Data_F2_ нужно только
			// для расчета массива Data_F1_F2_, а не для
			// синхронного детектирования
		}
	// Анализируем на участке длиной 120 отсчетов
	max_Data_F2_ = 0;
	min_Data_F2_ = 0;
	for(int i = 30; i < 150; i++)
	{
		my_DMA2_Data_F2_[i] = uiH =
		  my_DMA2_Data_F0_[i + 1] +
		  my_DMA2_Data_F0_[i + 26];
		// 5/2 периода для 12 кГц = 25
		// ВАЖНО - начало массива Data_F2_ нужно только
		// для расчета массива Data_F1_F2_, а не для
		// синхронного детектирования
		//if(max_Data_F2_ <= uiH) max_Data_F2_ = uiH;
		//if(min_Data_F2_ >= uiH) min_Data_F2_ = uiH;
	}
}

void my_F1F2_()
{
	// Частота 10 кГц в Data_F1_[120] уже вырезана
	// Детектируем частоту 12 кГц
	for(int i = 0; i < 5; i++)
	{
		p_my_F1F2_rez_[i] = 0;
	}
	for(int i = 0; i < 12; i++)
	{
		my_F1F2_rez_[0] +=													// совпадение с ASM
		    (my_DMA2_Data_F1_[10*i + 5 + 0] - my_DMA2_Data_F1_[10*i + 0]);
		my_F1F2_rez_[1] +=													// совпадение с ASM
		    (my_DMA2_Data_F1_[10*i + 5 + 1] - my_DMA2_Data_F1_[10*i + 1]);
		my_F1F2_rez_[2] +=													// отличие от ASM на 1
		    (my_DMA2_Data_F1_[10*i + 5 + 2] - my_DMA2_Data_F1_[10*i + 2]);
		my_F1F2_rez_[3] +=													// совпадение с ASM
		    (my_DMA2_Data_F1_[10*i + 5 + 3] - my_DMA2_Data_F1_[10*i + 3]);
		my_F1F2_rez_[4] +=													// отличие от ASM на 2
		    (my_DMA2_Data_F1_[10*i + 5 + 4] - my_DMA2_Data_F1_[10*i + 4]);
	}
}

void my_F2F1_()
{
	// Частота 12 кГц в Data_F2_[150] уже вырезана
	// Детектируем частоту 10 кГц
	for(int i = 0; i < 6; i++)
	{
		p_my_F2F1_rez_[i] = 0;
	}
	for(int i = 0; i < 10; i++)
	{
		my_F2F1_rez_[0] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 0] - my_DMA2_Data_F2_[12*i + 30 + 0]);
		my_F2F1_rez_[1] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 1] - my_DMA2_Data_F2_[12*i + 30 + 1]);
		my_F2F1_rez_[2] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 2] - my_DMA2_Data_F2_[12*i + 30 + 2]);
		my_F2F1_rez_[3] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 3] - my_DMA2_Data_F2_[12*i + 30 + 3]);
		my_F2F1_rez_[4] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 4] - my_DMA2_Data_F2_[12*i + 30 + 4]);
		my_F2F1_rez_[5] +=
		    (my_DMA2_Data_F2_[12*i + 36 + 5] - my_DMA2_Data_F2_[12*i + 30 + 5]);
		// Первые 30 отсчетов в буфере _Data_F2_ мы здесь не используем, они нужны
		// для построения буфера Data_F1_F2_ и анализа шумов и пульсаций лазера
	}
}

void my_F1_F2_()
{
	uint16_t	uiH;
	// Частота 12 кГц в Data_F2_[150] уже вырезана
	// Вырезаем частоту 10 кГц
	// Анализируем на участке длиной 120 отсчетов
	max_Data_F1_F2_ = 0;
	min_Data_F1_F2_ = 0;
	for(int i = 0; i < 120; i++)
	{
		my_DMA2_Data_F1_F2_[i] = uiH =
		  my_DMA2_Data_F2_[i] +
		  my_DMA2_Data_F2_[i + 30];
		//if(max_Data_F1_F2_ <= uiH) max_Data_F1_F2_ = uiH;
		//if(min_Data_F1_F2_ >= uiH) min_Data_F1_F2_ = uiH;
	}
}
#endif
