#include "SYS_Include.h"
#include "main.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "SYS_time.h"

/*********************************************************************
Tim2定时器初始化配置
Tim2时钟：72MHZ
中断间隔时间：10ms
*********************************************************************/

int shijian1=0;
void SYS_TimBase_Init(void){
//Timx时钟72MHZ，10ms中断一次
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;
	
	//打开TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//设置TIM时基
	//((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+199)/72M)*(1+3599)=0.01秒
	TIM_TimeBaseStructure.TIM_Period = 199;//999;
	TIM_TimeBaseStructure.TIM_Prescaler = 3599;//719;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


	TIM_ARRPreloadConfig(TIM2,ENABLE); 	
	
	//使能TIM2溢出中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	//设置Tim2中断优先级别	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//使能 TIM2定时器 */
	TIM_Cmd(TIM2, ENABLE); 
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
  
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}




/*********************************************************************
Tim2中断服务程序
Tim2时钟：72MHZ
中断间隔时间：10ms
*********************************************************************/	
void TIM2_IRQHandler()

{ 
	
	static unsigned char Count_10ms_For_Flash;
 
   
  TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);  //清除中断位
  KeyScan();
	
		
  if(++Count_10ms_For_Flash>=60)
  	{
	   Count_10ms_For_Flash=0;
    }
  
  switch(Count_10ms_For_Flash)
  	{
	  case 0:
		  Sys.Flag_LCD_Update= TRUE;	  //LCD更新
		  break;
	  case 30:
		  Sys.Flag_LCD_Update  = TRUE;
		  break;
  
	  default:
		  ;    
  }


}

/*********************************************************************
Tim3中断服务程序
Tim2时钟：72MHZ
中断间隔时间：1s
*********************************************************************/	

void TIM3_IRQHandler(void)   //TIM3中断                                                   important                                                                                      important
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否           important
{
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志                     important
{
	
	shijian1 +=1; 
		}
}

}
}

