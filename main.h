#ifndef _MAIN_H_
#define _MAIN_H_
#include "stm32f10x.h"

#define BUFF_SIZE	10
#define TIRE_NUM	4
#define TIRE_DATA_NUM	7



typedef enum {FALSE = 0, TRUE = !FALSE} bool;

/********************************************************************************************************
//?????????????
********************************************************************************************************/

/*?????????????*/
typedef enum {MAIN_MODE1=0, MAIN_MODE2=1, MAIN_MODE3=2, MAIN_MODE4=3}
			  Sys_State_Enum;


typedef enum {MAINMODE1_SUBMODE1=0, MAINMODE1_SUBMODE2=1, MAINMODE1_SUBMODE3=2, MAINMODE1_SUBMODE4=3}
			  Sub_MAIN_MODE1_Enum;

typedef enum {MAINMODE2_SUBMODE1=0, MAINMODE2_SUBMODE2=1, MAINMODE2_SUBMODE3=2, MAINMODE2_SUBMODE4=3}
			  Sub_MAIN_MODE2_Enum;

typedef enum {MAINMODE3_SUBMODE1=0, MAINMODE3_SUBMODE2=1, MAINMODE3_SUBMODE3=2, MAINMODE3_SUBMODE4=3}
			  Sub_MAIN_MODE3_Enum;

typedef enum {MAINMODE4_SUBMODE1=0, MAINMODE4_SUBMODE2=1, MAINMODE4_SUBMODE3=2, MAINMODE4_SUBMODE4=3}
			  Sub_MAIN_MODE4_Enum;

/********************************************************************************************************
//????????????
********************************************************************************************************/
typedef struct {
    Sys_State_Enum      Main_Mode;     //
    Sub_MAIN_MODE1_Enum      Sub_MAIN_MODE1;     //
    Sub_MAIN_MODE2_Enum      Sub_MAIN_MODE2;     //
    Sub_MAIN_MODE3_Enum      Sub_MAIN_MODE3;     //
}Sys_Mode_Struct;


/********************************************************************************************************
//????????????????
********************************************************************************************************/

typedef struct {
    Sys_Mode_Struct     Mode;                     //????
    bool Flag_LCD_Update;	       //LCD??¡À??¦Ë
    
}Sys_Struct;



extern unsigned char Flag_Timer_True,Count_Timer; 
extern Sys_Struct Sys;


#endif
