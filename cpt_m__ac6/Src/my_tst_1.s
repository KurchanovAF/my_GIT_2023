.cpu cortex-m4
.syntax unified
.thumb

.extern	my_dat_1
.extern	my_dat_2

.global my_dat__1
my_dat__1:
.word	0x0000f00f
.global my_dat__2
my_dat__2:
.word	0x0000ffff

.global	my_tst_1
.func	my_tst_1
my_tst_1:
	  STMDB  SP!, {R0-R12, LR}
	  
      //;LDR R1, my_dat__1	; Load register. The address is an offset from the PC
	  LDR R1, =my_dat_1	//; Load a register with either a 32-bit immediate value or an address
	  LDR R1, [R1]			; 
	  //;LDR R2, my_dat__2	; Load register. The address is an offset from the PC
	  LDR R2, =my_dat_2	//; Load a register with either a 32-bit immediate value or an address
	  //MOV R1, 0x0000aeae
	  STR R1, [R2]			//; Store with immediate offset
	  //;STR R1, my_dat__2
	  
      LDMIA  SP!, {R0-R12, LR}
	  BX  LR
	  //;LDMIA  SP!, {SP, PC}
	  //;LDMIA  FP!, {R4-FP, SP, PC}
	  /*
	  ;R11 = FP
	  ;R12 = IP
	  ;R13 = SP
	  ;R14 = LR - address to return
	  ;R15 = PC
	  ; https://radiohlam.ru/stm32_8/
	  ; http://www.keil.com/support/docs/3607.htm
	  ; https://sourceware.org/legacy-ml/binutils/2010-01/msg00581.html
	  ; https://habr.com/ru/post/188712/
	  ; http://stm32asm.ru/new_clear.html
	  ; http://www.keil.com/support/man/docs/armasm/
	  ; https://sourceware.org/legacy-ml/binutils/2010-01/msg00581.html*/
.endfunc

.end
