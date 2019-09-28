#include "beep.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ��ӢSTM32������
//��������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
 
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);//���0���رշ��������

}

	
		void test()  //̥ѹ����
		{ 
			//KeyScan();			
			if (Key.Flag==1)
				t99t++;
			if(pressure[0]<standard1|pressure[2]<standard1|pressure[3]<standard1|pressure[3]<standard1)
			{
					LED0=!LED0;
				 LED1=!LED1;
				if(t99t>=1)
				{BEEP=0;} //      beep=1     ��������
	      else
				{BEEP=1;
					delay_ms(30);//��ʱ300ms
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
		    delay_ms(300);//��ʱ300ms
				BEEP=0;       //beep����
				LED0=1;       //����
			printf("chenggongjinru");
			AAA();        //�趨��ֵ����
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
				LCD_ShowxNum(30,120,standard1,4,16,0);//��ʾ��ֵ 
			  break;
			
			  case 1:
				 LCD_ShowString(30,90,210,24,24," tire pressure low");	
				LCD_ShowxNum(30,120,standard1,4,16,0);//��ʾ��ֵ 
			  break;
				
        case 2:
				LCD_ShowString(30,90,210,24,24," temperature");
				LCD_ShowxNum(30,120,standard1,4,16,0);//��ʾ��ֵ 
			  break;

        case 3:
				LCD_ShowString(30,90,210,24,24," battery");
				LCD_ShowxNum(30,120,standard1,4,16,0);//��ʾ��ֵ 
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
		 
	