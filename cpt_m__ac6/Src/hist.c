#include "hist.h"
#include "var.h"



uint16_t maxfreq;   			//������������ ������� � ������������
uint16_t minfreq;   			//����������� ������� � ������������
uint16_t diff[2000]; 			// ������ � ������������� ��������� ������
//const int num_cell = 24;  	// ���-�� ����� �����������
uint16_t cell[num_cell]; 		//������ � ���-��� ������ ������ � ����� ������
uint16_t rez_cell[num_cell]; 	//������ � ���-��� ������ ������ � ����� ������ ��� ��������
uint16_t tmp; 					// ��������� ���������� ��� ������ ��� � ����
uint16_t step_diff; 			// ��� ������
uint16_t max_diff = 4000;  		// �������� �����������
uint16_t* p_diff; 				// ��������� �� ������� diff[]
int no = 0; 					// ����� �������� ������� diff[]
int numPosHist = 0;				// ����� ������� � ������� ������
int num_sec_Hist = 0;   		// ����� �������� �������� ����� (�� ����� 20)
bool flagHist = false; 			// ���� �� ������������ cell[]
bool b_buf_HIST = false; 		// ���� �� ������������ ������ ��������

/*
static inline void Difference(){           // ������� ������  ������� ������ � 1 ��

  maxfreq = 0;
  minfreq = 65535;
  for(int i = 0; i < 120; i++){
	  tmp = p_my_DMA2_Data_F1_F2_[i];             // ����� ��� � ���� �������
	  if(minfreq > tmp)
	  minfreq = tmp;
	  if(maxfreq < tmp)
	  maxfreq = tmp;
  }

  diff[no] = maxfreq - minfreq;      // ��������� m-��������� ������� ������ ������
  no++;

  if( no == 1000) flagHist=true;     // ��� ���������� 1000 ��������� ���������� �������� ����������� (���� �� ���������� = true)
  if( no == 2000)                    // ��� ���������� 2000 ��������� ���� �� ���������� = true, ������������ diff[] ���������� � ������
  {
	  flagHist = true;
	  no = 0;
  }
}

//*/


void HIST()              		// ������� ���������� �����������
{
	if(flagHist) {              // ��������, ���� ����  �� ���������� = true
		flagHist=false;        	// ���������� ���� �� ����������
		if(no >= 1000)          // ���� ������ diff[] >=1000, �� ������������ �������� ����������� � �������� ��������
		{

			p_diff = &diff[0];
		}
		if(no < 1000)         	// ���� ������ >1000, �� ������������ � ��������� ��������
		{

			p_diff = &diff[1000];
		}

		for(int i; i < 1000; i++)       //��������� �������� ����� �����������
		{
			int k;
			k = p_diff[i];
			k = k/step_diff;
			if(k >= num_cell) k = num_cell - 1;
			cell[k]++;
		}
		num_sec_Hist++;        			// ����������� ���-�� ������
		if(num_sec_Hist == 20)
		{
			for(int i = 0; i < num_cell; i++)  // ��������� ���������� �������� ��� �������� �� ���������
			{
				rez_cell[i] = cell[i];
				cell[i] = 0;
			}
			num_sec_Hist = 0; 			// ����� ���-�� ������

			b_buf_HIST = true;   		// ������ ���� �� �������� ������ �� ���������
		}

	}
}



/*

static inline void funWork_HIST(void){	// ������� �������� ����������� �� ���������
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
			numPosHist += 8;  			// ����� ������
			SendPkgData(STREAM_DATA, ((uint8_t*)&dataSend), 9*4);

			if(numPosHist >= num_cell) {
				numPosHist = 0; 		// ���������� ����� ������
				b_buf_HIST = false; 	//����� ����� �� �������� ������ �� ���������
				}
		}
	}
}
//*/
