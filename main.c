#include "stm32f10x.h"


//----------**************************8--------------
//1.创建了完全纯净的工程项目
//2.增加了delay.c,usart.c,sys.c三个子程序---测试成功--20180725-1600
//3.增加了lcd.c,led.c,key.c三个子程序---测试成功--20180725-2000
//4.增加了SYS_time子程序,用来触发LCD显示切换---测试成功--20180923-2000 
//5.增加了按键显示状态机程序---测试成功--20180924-1100 
 
 
 
 
/************************************************
 ALIENTEK 精英STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
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
	 delay_init();			  //延时函数初始化	   
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 uart_init(115200); 	 //串口初始化为115200
	 LED_Init();			  //LED端口初始化
	 LCD_Init();
	 POINT_COLOR=RED;
	 KEY_Init();
   BEEP_Init();

	 Sys.Mode.Main_Mode=MAIN_MODE1;     //MAIN_MODE1有好几个值,靠值来判断是哪个主模式
	 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
	 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
	 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;

	 SYS_TimBase_Init();//时基初始化

    
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
    //复位按键初始状态
				}
			  KeyDeal();
				
				//LcdUpdata_Flag=1;
		  }
	/****************************************/		
			else
			{	fortime1=time10delay();
				if(fortime1==1)				//判断有没有按够10s
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
