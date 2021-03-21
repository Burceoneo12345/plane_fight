
#include"picture.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epi.h"
#include "inc/hw_ints.h"
#include "driverlib/epi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"
#include "driverlib/fpu.h"
#include "utils/uartstdio.h"
#include "TFTinit/TFT_400x240_OTM4001A_16bit.h"
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"
#include "KEY.h"
#include "inc/hw_nvic.h"
#include "driverlib/timer.h"
#include "EPIinit/EPIinit.h"
#include "IQmath/IQmathLib.h"
#include "backpicture.h"
#include "menupicture.h"

#ifndef M_PI
#define M_PI                    3.14159265358979323846F //宏定义
#endif
volatile uint32_t key;//按键值
int score=0;          //计分
bool start=0;        //游戏开始标志位
bool flag_bullet=0;  //子弹标志位  ，置0表示当前不存在子弹
bool flag_stone=0;   //陨石标志位
uint32_t g_ui32SysClock;
int T_Flag=0; //定时器扫描次数技术
static volatile unsigned long g_ulTickCount;
#define SERIES_LENGTH 240
uint32_t x_stone,x_bullet,x_plane=60;    //子弹陨石坐标
uint32_t y_stone,y_bullet,y_plane=340;
uint32_t old_plane[7200];

#define TICKS_PER_SECOND 1000
#define FSECONDS_PER_TICK (1.0F/(float)TICKS_PER_SECOND)
void //滴答计时器中断函数
SysTickIntHandler(void)
{
	g_ulTickCount++;
	if(g_ulTickCount>=480)
		g_ulTickCount=0;
	}
void //串口初始化函数
ConfigureUART(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//使能GPIOA口
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//使能 UART0
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}
//定时器中断初始化函数
void TimerIntInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR  | TIMER_CFG_B_PERIODIC | TIMER_CFG_A_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_B, 10*g_ui32SysClock/1000);
	TimerLoadSet(TIMER0_BASE, TIMER_A, 10*g_ui32SysClock/1000);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_B);
	TimerEnable(TIMER0_BASE, TIMER_A);
	IntEnable(INT_TIMER0B);
	IntEnable(INT_TIMER0A);
}


 //画飞机
 void DrawPlane(x,y){

		uint32_t temp,i,j,m;
		m=0;
		for(i=y;i<y+60;i++)
		{
			for(j=x;j<x+60;j++)
			{
				temp=plane[m];
				temp |= plane[m+1]<<8;
				TFTLCD_DrawPoint( j, i,temp);
				m++;
				m++;
			}
		}

 }
 //清除飞机
 void ClearPlane(x,y){
     uint32_t temp,i,j,m;
     m = 240*2*y+2*x;
     for(i=y;i<y+60;i++)
     {
         for(j=x;j<x+60;j++)
         {
             temp=game_back[m];
             temp |= game_back[m+1]<<8;
             TFTLCD_DrawPoint(j,i,temp);
             m++;
             m++;
         }
         m += 360;
     }
 }
 //游戏开始界面
 void DrawMenu(){

		start=0;
		TFTLCD_ShowChineseChar(20,10,0,WHITE,BLACK);
		TFTLCD_ShowChineseChar(70,10,1,WHITE,BLACK);
		TFTLCD_ShowChineseChar(120,10,2,WHITE,BLACK);
		TFTLCD_ShowChineseChar(170,10,3,WHITE,BLACK);
		TFTLCD_Showoption(30,100,0,WHITE,BLACK);
		TFTLCD_Showoption(70,100,1,WHITE,BLACK);
		TFTLCD_Showoption(110,100,2,WHITE,BLACK);
		TFTLCD_Showoption(150,100,3,WHITE,BLACK);
		TFTLCD_Showoption2(30,160,0,WHITE,BLACK);
        TFTLCD_Showoption2(70,160,1,WHITE,BLACK);
        TFTLCD_Showoption2(110,160,2,WHITE,BLACK);
        TFTLCD_Showoption2(150,160,3,WHITE,BLACK);
        TFTLCD_Showoption3(55,220,0,WHITE,BLACK);
        TFTLCD_Showoption3(130,220,1,WHITE,BLACK);
 }
 //游戏结束函数
 void GameOver(){
		start=0;
		uint32_t temp,i,j,m;
		m=0;
		for(i=0;i<400;i++)
		{
			for(j=0;j<240;j++)
			{
				temp=gameover[m];
				temp |= gameover[m+1]<<8;
				TFTLCD_DrawPoint( j, i,temp);
				m++;
				m++;
			}
		}
	 		start=0,flag_bullet=0,flag_stone=0;
	 		UARTprintf("Gameover!\n");
	 		UARTprintf("Your score:%d\n",score);
 }
 //爆炸
 void DrawBoom(x,y){

		uint32_t temp,i,j,m;
		m=0;
		for(i=y;i<y+60;i++)
		{
			for(j=x;j<x+60;j++)
			{
				temp=boom[m];
				temp |= boom[m+1]<<8;
				TFTLCD_DrawPoint( j, i,temp);
				m++;
				m++;
			}
		}
 }
 //清除爆炸
void ClearBoom(x,y){
    uint32_t temp,i,j,m;
    m = 240*2*y+2*x;
    for(i=y;i<y+80;i++)
    {
        for(j=x;j<x+60;j++)
        {
            temp=game_back[m];
            temp |= game_back[m+1]<<8;
            TFTLCD_DrawPoint(j,i,temp);
            m++;
            m++;
        }
        m += 360;
    }
}


//游戏界面
void DrawGameback(){

       uint32_t temp,i,j,m,x,y;
       x=0;
       y=0;
       m=0;
       for(i=y;i<y+400;i++)
       {
           for(j=x;j<x+240;j++)
           {
               temp=game_back[m];
               temp |= game_back[m+1]<<8;
               TFTLCD_DrawPoint( j, i,temp);
               m++;
               m++;
           }
       }
}

//画陨石
 void DrawStone(x,y){
		uint32_t temp,i,j,m;
		m=0;
		for(i=y;i<y+60;i++)
		{
			for(j=x;j<x+60;j++)
			{
				temp=stone[m];
				temp |= stone[m+1]<<8;
				TFTLCD_DrawPoint( j, i,temp);
				m++;
				m++;
			}
		}
 }
 //清除陨石
 void ClearStone(x,y){
         uint32_t temp,i,j,m;
         m = 240*2*y+2*x;
         for(i=y;i<y+60;i++)
         {
             for(j=x;j<x+60;j++)
             {
                 temp=game_back[m];
                 temp |= game_back[m+1]<<8;
                 TFTLCD_DrawPoint(j,i,temp);
                 m++;
                 m++;
             }
             m += 360;
         }
  }
 //画子弹
 void DrawBullet(x,y){
		uint32_t temp,i,j,m;
		m=0;
		for(i=y;i<y+20;i++)
		{
			for(j=x;j<x+20;j++)
			{
				temp=bullet[m];
				temp |= bullet[m+1]<<8;
				TFTLCD_DrawPoint( j, i,temp);
				m++;
				m++;
			}
		}
 }
 //清除子弹
 void ClearBullet(x,y){
	     uint32_t temp,i,j,m;
	     m = 240*2*y+2*x;
	     for(i=y;i<y+20;i++)
	     {
	         for(j=x;j<x+20;j++)
	         {
	             temp=game_back[m];
	             temp |= game_back[m+1]<<8;
	             TFTLCD_DrawPoint(j,i,temp);
	             m++;
	             m++;
	         }
	         m += 440;
	     }
 }
 void main()
 {

	    //FPUEnable();//使能FPU
	   //FPULazyStackingEnable();
	    SYSCTL_RCGCGPIO_R |= (SYSCTL_RCGCGPIO_R13 | SYSCTL_RCGCGPIO_R12 | SYSCTL_RCGCGPIO_R11 |SYSCTL_RCGCGPIO_R10| SYSCTL_RCGCGPIO_R7 |SYSCTL_RCGCGPIO_R3 );
	    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
	                SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
	                SYSCTL_CFG_VCO_480), 120000000);
	    SysTickPeriodSet(g_ui32SysClock / TICKS_PER_SECOND);
	    IntMasterEnable();
	    SysTickIntEnable();//使能中断
	    SysTickEnable();//使能SysTick
	    ConfigureUART();//初始化UART
	    EPIGPIOinit();
	    key_init();
	    TFT_400x240_OTM4001Ainit(g_ui32SysClock);
	    // Open BackLight.
	    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
	    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
	    UARTprintf("Game start!\n");
	    DrawMenu(); //画菜单
	    TimerIntInitial();
	    while(1)
	    {
	    	if(start==1)
	    	{
	    		//计分
		    	TFTLCD_ShowString(50,10,"score:",CYAN,LIGHTBLUE);
				TFTLCD_ShowData(100,10,score,CYAN,LIGHTBLUE);
	    	}

	    }
	  //TFTLCD的参数设置

 }


  void Timer0BIntHandler(void)
  {
  	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);//清中断
  	int a;
  	key=identify_key();
  	a=key;
  	switch (a)
  				{
  				case 1:
  				{
  					if (x_plane >0&&start==1)
  					{
  						ClearPlane(x_plane, y_plane);
  						DrawPlane(x_plane -=60, y_plane);
  					}//向左
  					a = 0;
  					break;
  				}
  				case 5:
  				{
  					if (y_plane < 340&&start==1)
  					{
  						ClearPlane(x_plane, y_plane);
  						DrawPlane(x_plane, y_plane += 60);
  					}//向下
  					a = 0;
  					break;
  				}
  				case 9:
  				{
  					if (x_plane < 180&&start==1)
  					{
  						ClearPlane(x_plane, y_plane);
  						DrawPlane(x_plane +=60, y_plane);
  					}//向右
  					a = 0;
  					break;
  				}
  				case 6:
  				{
  					if (y_plane > 60&&start==1)
  					{
  						ClearPlane(x_plane, y_plane);
  						DrawPlane(x_plane, y_plane -= 60);
  					}//向上
  					a = 0;
  					break;
  				}
  				case 14:
  				{
  					if (start == 0)
  					{
  						start = 1;
  						x_plane=60;
  						y_plane=340;
  						TFTLCD_CLEAR(BLACK);
  				        DrawGameback();
  						DrawPlane(x_plane, y_plane);
  						UARTprintf("Game start!\n");
  						score=0;
  					} //开始游戏
  					a = 0;
  					break;
  				}
  				case 13:
  				{
  					if (flag_bullet == 0&&start==1)
  					{
  						DrawBullet(x_plane+20, y_plane-20);
  						flag_bullet = 1;
  						x_bullet=x_plane+20;
  						y_bullet=y_plane-20;
  					}   //发射子弹
  					a = 0;
  					break;
  				}
  			}
  	//判断子弹是否击中陨石，若击中，则爆炸
  	if((x_bullet-20)==x_stone&&(y_bullet-y_stone)<70&&flag_bullet==1&&flag_stone==1)
	{
  		flag_bullet=0;
  		flag_stone=0;
  		int i=0;
  		GPIO_PORTL_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;
  		DrawBoom(x_stone,y_stone);  //爆炸
  		//SysCtlDelay(g_ui32SysClock/3000/500);
  		while(i++<1000)    //延迟一会儿
  		{}
  		ClearBoom(x_stone,y_stone);
  		GPIO_PORTM_DATA_R&=0xdf;
  		score++;

  	}

  	//判断陨石和飞机是否相撞
  	if(x_plane==x_stone&&(y_plane-y_stone)<30&&start==1&&flag_stone==1)
	{
  		int i=0;
  		GPIO_PORTL_DATA_R = 0x01;GPIO_PORTM_DATA_R|=0x20;
  		DrawBoom(x_stone,y_stone);  //爆炸
  		while(i++<1000)    //延迟一会儿
  		{}
  		ClearBoom(x_stone,y_stone);
  		GPIO_PORTN_DATA_R = 0x00;
  		GPIO_PORTM_DATA_R&=0xdf;
  		GameOver();
  	}

  }
  void Timer0AIntHandler(void){
 	 TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
 	 //随机生成陨石
 	 if(T_Flag++>100)
 	 {
 	if(start==1)
 	{
 	 uint16_t s_rand;
 	 if(flag_stone==0)
 	 {
 		 s_rand=(rand()%4)*60;
 		 DrawStone(s_rand,30);
 		 x_stone=s_rand;
 		 y_stone=30;
 		 flag_stone=1;//生成陨石后陨石标志位置1
 	 }
 	 //子弹移动
 	 if(y_bullet>0&&y_bullet<340)
 	 {
 		 if(flag_bullet==1)
 		 {
 			ClearBullet(x_bullet,y_bullet);   //擦去之前的子弹
 			DrawBullet(x_bullet,y_bullet-=30);   //画上新的子弹+随着分数增高而加速
 		 }
 	 }
 	 else
 	 {
 		 ClearBullet(x_bullet,y_bullet);
 		 flag_bullet=0; //如果子弹到达尽头未命中陨石，设置子弹标志位为0以便清除。
 	 }
 	 //陨石移动
 	 if(y_stone<340)
 	 {
 		if(flag_stone==1)
 		{
 			ClearStone(x_stone,y_stone);
 			DrawStone(x_stone,y_stone+=30);
 		}
 	 }
 	 else
 	 {
 		 ClearStone(x_stone,y_stone);
 		 flag_stone=0;
 	 }

 	}
 	T_Flag=0;
 	 }

  }




