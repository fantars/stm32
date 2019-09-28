#include "beep.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 精英STM32开发板
//蜂鸣器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB8为输出口.并使能这个口的时钟		    
//蜂鸣器初始化
extern int shijian1;
extern int pressure[4],standard1;
int t99t=0;
extern int change=40;
void keysolver();
void AAA();
void back_and_clear();
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能GPIOB端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8
 
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出

}

	
		void test()  //胎压报警
		{ 
			//KeyScan();			
			if (Key.Flag==1)
				t99t++;
			if(pressure[0]<standard1|pressure[2]<standard1|pressure[3]<standard1|pressure[3]<standard1)
			{
					LED0=!LED0;
				 LED1=!LED1;
				if(t99t>=1)
				{BEEP=0;} //      beep=1     蜂鸣器响
	      else
				{BEEP=1;
					delay_ms(30);//延时300ms
				  BEEP=0;
				}					
			}							
		 }
		
		
	int time10delay(void)
	{
		 	if(shijian1<1)
		 TIM3_Int_Init(7999,8999);   
		  if(shijian1>=10)
			{	shijian1=0;
				TIM_Cmd(TIM3, DISABLE);  //?????????
		    return 1;
      }			
		}	
	 void set_up(void)    
		{
		
				BEEP=1;	
		    delay_ms(300);//延时300ms
				BEEP=0;       //beep不响
				LED0=1;       //灯灭
			printf("chenggongjinru");
			AAA();        //设定数值函数
		} 
  		
		  void AAA(void)
    {		
			 while(1)
			 {	
				  delay_ms(30);				 
          keysolver();
           				 

          				 
					if(Key.Flag==0)
						{ 
							time10delay();
								if(time10delay()==1)
									
								return;
						}
					else	
						{  
							 if(Key.Value == WKUP_3)
               							 
							 return;
						}
				}	
	  }
		  void keysolver(void)
		{
			KeyScan();
			switch (change)
			{	
			  case 0:
			  LCD_ShowString(30,90,210,24,24," tire pressure high");
				LCD_ShowxNum(30,120,standard1,4,16,0);//显示的值 
			  break;
			
			  case 1:
				 LCD_ShowString(30,90,210,24,24," tire pressure low");	
				LCD_ShowxNum(30,120,standard1,4,16,0);//显示的值 
			  break;
				
        case 2:
				LCD_ShowString(30,90,210,24,24," temperature");
				LCD_ShowxNum(30,120,standard1,4,16,0);//显示的值 
			  break;

        case 3:
				LCD_ShowString(30,90,210,24,24," battery");
				LCD_ShowxNum(30,120,standard1,4,16,0);//显示的值 
			  break;
			}
			
			
			
			
			if(Key.Value == WKUP_S)
			{change++;
				change=change%4;
			  back_and_clear(); }
			if(Key.Value == KEY0_S)
			{	
				standard1=minus20(standard1);
			back_and_clear();  }
			if(Key.Value == KEY1_S)
			{ 
				standard1=plus20(standard1);
			  back_and_clear();   }
			if(standard1>400|standard1<120)
				standard1=200;
			
			
		}
		 void back_and_clear(void)
		 {
			 Key.Status=FREE;
      Key.Flag = 0;
       Key.Value=KEY_IDLE; 
		 }
		 
		 int plus20(int a)
		 { a=a+20; 
       return a; 
		 }
		 
		 int minus20(int a)
		 { a=a-20; 
			 return a; 
		 }
		 
	