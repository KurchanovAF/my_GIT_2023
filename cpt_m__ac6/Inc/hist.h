#ifndef _HIST
#define _HIST

#include <stdbool.h>
#include <stdint.h>

#define num_cell 400  				// ���-�� ����� �����������

extern uint16_t maxfreq;   			//������������ ������� � ������������
extern uint16_t minfreq;   			//����������� ������� � ������������
extern uint16_t diff[2000]; 		// ������ � ������������� ��������� ������
extern uint16_t cell[num_cell]; 	//������ � ���-��� ������ ������ � ����� ������
extern uint16_t rez_cell[num_cell]; //������ � ���-��� ������ ������ � ����� ������ ��� ��������
extern uint16_t tmp; 				// ��������� ���������� ��� ������ ��� � ����
extern uint16_t step_diff; 			// ��� ������
extern uint16_t max_diff;  			// �������� �����������
extern uint16_t* p_diff; 			// ��������� �� ������� diff[]
extern int no; 						// ����� �������� ������� diff[]
extern int numPosHist;				// ����� ������� � ������� ������
extern int num_sec_Hist;      		// ����� �������� �������� ����� (�� ����� 20)
//extern const int num_cell;  		// ���-�� ����� �����������
extern bool flagHist; 				// ���� �� ������������ cell[]
extern bool b_buf_HIST; 			// ���� �� ������������ ������ ��������


//static inline void Difference(void);
void HIST();
//static inline void funWork_HIST(void);

#endif
