#ifndef __ADT7410_H
#define __ADT7410_H


#define ADT7410_ADDRESS				(0x48)

//=========================================================
// REGISTER ADDRESS MAP
//=========================================================
#define ADT7410_REG_RESULT	(0x00)
#define ADT7410_REG_CONF    (0x03)

//=========================================================
// CONFIGURATION REGISTER (0x03)
//=========================================================

#define ADT7410_CT_HIGH 					(0x04)	

#define ADT7410_INT_HIGH 					(0x08)	

#define ADT7410_MODE_COMPARATOR 	(0x10)

#define ADT7410_CONV_CONT 				(0x00)
#define ADT7410_CONV_ONE_SHOT 		(0x20)
#define ADT7410_CONV_SPS 					(0x40)
#define ADT7410_CONV_SHUTDOWN 		(0x60)

#define ADT7410_RES_13 						(0x00)
#define ADT7410_RES_16 						(0x80)

  
#endif


