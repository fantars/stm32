#include "SYS_Include.h"
#include "main.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "SYS_time.h"

/*********************************************************************
Tim2��ʱ����ʼ������
Tim2ʱ�ӣ�72MHZ
�жϼ��ʱ�䣺10ms
*********************************************************************/

int shijian1=0;
void SYS_TimBase_Init(void){
//Timxʱ��72MHZ��10ms�ж�һ��
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;
	
	//��TIM2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//����TIMʱ��
	//((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+199)/72M)*(1+3599)=0.01��
	TIM_TimeBaseStructure.TIM_Period = 199;//999;
	TIM_TimeBaseStructure.TIM_Prescaler = 3599;//719;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


	TIM_ARRPreloadConfig(TIM2,ENABLE); 	
	
	//ʹ��TIM2����ж�
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	//����Tim2�ж����ȼ���	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//ʹ�� TIM2��ʱ�� */
	TIM_Cmd(TIM2, ENABLE); 
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}




/*********************************************************************
Tim2�жϷ������
Tim2ʱ�ӣ�72MHZ
�жϼ��ʱ�䣺10ms
*********************************************************************/	
void TIM2_IRQHandler()

{ 
	
	static unsigned char Count_10ms_For_Flash;
 
   
  TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);  //����ж�λ
  KeyScan();
	
		
  if(++Count_10ms_For_Flash>=60)
  	{
	   Count_10ms_For_Flash=0;
    }
  
  switch(Count_10ms_For_Flash)
  	{
	  case 0:
		  Sys.Flag_LCD_Update= TRUE;	  //LCD����
		  break;
	  case 30:
		  Sys.Flag_LCD_Update  = TRUE;
		  break;
  
	  default:
		  ;    
  }


}

/*********************************************************************
Tim3�жϷ������
Tim2ʱ�ӣ�72MHZ
�жϼ��ʱ�䣺1s
*********************************************************************/	

void TIM3_IRQHandler(void)   //TIM3�ж�                                                   important                                                                                      important
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������           important
{
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־                     important
{
	
	shijian1 +=1; 
		}
}

}
}

