#include "stm32f10x.h"


//----------**************************8--------------
//1.��������ȫ�����Ĺ�����Ŀ
//2.������delay.c,usart.c,sys.c�����ӳ���---���Գɹ�--20180725-1600
//3.������lcd.c,led.c,key.c�����ӳ���---���Գɹ�--20180725-2000
//4.������SYS_time�ӳ���,��������LCD��ʾ�л�---���Գɹ�--20180923-2000 
//5.�����˰�����ʾ״̬������---���Գɹ�--20180924-1100 
 
 
 
 
/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "SYS_time.h"
#include "main.h"
#include "beep.h"

unsigned char Flag_Timer_True,Count_Timer; 
int fortime1;
Sys_Struct Sys;
int pressure[4],temperature[4],vol[4];
 int pressure[4]={192, 193, 193, 194,};
  int standard1=180;


 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	
	 delay_init();			  //��ʱ������ʼ��	   
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart_init(115200); 	 //���ڳ�ʼ��Ϊ115200
	 LED_Init();			  //LED�˿ڳ�ʼ��
	 LCD_Init();
	 POINT_COLOR=RED;
	 KEY_Init();
   BEEP_Init();

	 Sys.Mode.Main_Mode=MAIN_MODE1;     //MAIN_MODE1�кü���ֵ,��ֵ���ж����ĸ���ģʽ
	 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
	 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
	 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;

	 SYS_TimBase_Init();//ʱ����ʼ��

    
	 while(1) 
	 	{
	 	  test();
		  if (Key.Flag==TRUE)  //
		  {
				if(Key.Value == WKUP_3)
				{ Key.Status=FREE;
	        Key.Flag = FALSE;
          Key.Value=KEY_IDLE;
					set_up();	
    //��λ������ʼ״̬
				}
			  KeyDeal();
				
				//LcdUpdata_Flag=1;
		  }
	/****************************************/		
			else
			{	fortime1=time10delay();
				if(fortime1==1)				//�ж���û�а���10s
				{Sys.Mode.Main_Mode=MAIN_MODE1,Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
					Disp_Proc();
			  Sys.Flag_LCD_Update=FALSE;
				}
			}
	/****************************************/		
		  if (Sys.Flag_LCD_Update==TRUE)
		  {
			  Disp_Proc();
			  Sys.Flag_LCD_Update=FALSE;
		  }
	 	}
 }
