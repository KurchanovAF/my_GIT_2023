#ifndef _HIST
#define _HIST

#include <stdbool.h>
#include <stdint.h>

#define num_cell 400  				// кол-во €чеек гистограммы

extern uint16_t maxfreq;   			//максимальна€ частота в миллисекунду
extern uint16_t minfreq;   			//минимальна€ частота в миллисекунду
extern uint16_t diff[2000]; 		// массив с подсчитанными разницами частот
extern uint16_t cell[num_cell]; 	//массив с кол-вом разниц частот в одной €чейке
extern uint16_t rez_cell[num_cell]; //массив с кол-вом разниц частот в одной €чейке дл€ передачи
extern uint16_t tmp; 				// временные переменные дл€ поиска мин и макс
extern uint16_t step_diff; 			// шаг €чейки
extern uint16_t max_diff;  			// максимум гистограммы
extern uint16_t* p_diff; 			// указатель на элемент diff[]
extern int no; 						// номер элемента массива diff[]
extern int numPosHist;				// Ќомер позиции в длинном буфере
extern int num_sec_Hist;      		// номер итерации подсчета €чеек (не более 20)
//extern const int num_cell;  		// кол-во €чеек гистограммы
extern bool flagHist; 				// флаг на формирование cell[]
extern bool b_buf_HIST; 			// флаг на формирование буфера передачи


//static inline void Difference(void);
void HIST();
//static inline void funWork_HIST(void);

#endif
