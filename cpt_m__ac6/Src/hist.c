#include "hist.h"
#include "var.h"



uint16_t maxfreq;   //максимальная частота в миллисекунду
uint16_t minfreq;   //минимальная частота в миллисекунду
uint16_t diff[2000]; // массив с подсчитанными разницами частот
//const int num_cell = 24;  // кол-во ячеек гистограммы
uint16_t cell[num_cell]; //массив с кол-вом разниц частот в одной ячейке
uint16_t rez_cell[num_cell]; //массив с кол-вом разниц частот в одной ячейке для передачи
uint16_t tmp; // временные переменные для поиска мин и макс
uint16_t step_diff; // шаг ячейки
uint16_t max_diff = 4000;  // максимум гистограммы
uint16_t* p_diff; // указатель на элемент diff[]
int no = 0; // номер элемента массива diff[]
int numPosHist = 0;		// Номер позиции в длинном буфере
int num_sec_Hist = 0;   // номер итерации подсчета ячеек (не более 20)
bool flagHist = false; // флаг на формирование cell[]
bool b_buf_HIST = false; // флаг на формирование буфера передачи

/*
static inline void Difference(){           // функция поиска  разницы частот в 1 мс

  maxfreq = 0;
  minfreq = 65535;
  for(int i = 0; i < 120; i++){
	  tmp = p_my_DMA2_Data_F1_F2_[i];             // поиск мин и макс частоты
	  if(minfreq > tmp)
	  minfreq = tmp;
	  if(maxfreq < tmp)
	  maxfreq = tmp;
  }

  diff[no] = maxfreq - minfreq;      // формируем m-элементов массива разниц частот
  no++;

  if( no == 1000) flagHist=true;     // при заполнении 1000 элементов начинается строение гистограммы (флаг на построение = true)
  if( no == 2000)                    // при заполнении 2000 элементов флаг на построение = true, формирование diff[] начинается с начала
  {
	  flagHist = true;
	  no = 0;
  }
}

//*/


void HIST()              // функция построения гистограммы
{
	if(flagHist) {               // работает, если флаг  на построение = true
		flagHist=false;          // сбрасываем флаг на построение
		if(no >= 1000)           // если индекс diff[] >=1000, то обрабатываем значения гистограммы с нулевого элемента
		{

			p_diff = &diff[0];
		}
		if(no < 1000)         // если индекс >1000, то обрабатываем с тысячного элемента
		{

			p_diff = &diff[1000];
		}

		for(int i; i < 1000; i++)       //формируем значения ячеек гистограммы
		{
			int k;
			k = p_diff[i];
			k = k/step_diff;
			if(k >= num_cell) k = num_cell - 1;
			cell[k]++;
		}
		num_sec_Hist++;        // отсчитываем кол-во секунд
		if(num_sec_Hist == 20)
		{
			for(int i = 0; i < num_cell; i++)  // сохраняем полученные значения для передачи на компьютер
			{
				rez_cell[i] = cell[i];
				cell[i] = 0;
			}
			num_sec_Hist = 0; // сброс кол-ва секунд

			b_buf_HIST = true;   // ставим флаг на передачу данных на компьютер
		}

	}
}



/*

static inline void funWork_HIST(void){     // функция передачи гистограммы на компьютер
	static uint32_t dataSend[9];
	static int delaySend = 0;
	if(b_buf_HIST){
		delaySend++;
		if (delaySend % 100 == 0){
			dataSend[8] = numPosHist;
			for(int i = 0; i < 8; i++)
			{
				dataSend[i] = rez_cell[numPosHist + i];
			}
			numPosHist += 8;  // номер порции
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);

			if(numPosHist >= num_cell) {
				numPosHist = 0; // сбрасываем номер порции
				b_buf_HIST = false; //сброс флага на передачу данных на компьютер
				}
		}
	}
}
//*/
