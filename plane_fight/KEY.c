#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"
#include "KEY.h"

uint8_t Key_Flg =0; //按键检测次数标志位
uint8_t Key_Dely =70;//按键延迟次数，为了解决按一下按键多次返回key值的问题
//按键初始化函数
void key_init(void)
{
	GPIO_PORTN_DIR_R = 0x03;
	GPIO_PORTM_DIR_R = 0x28;
	GPIO_PORTH_AHB_DIR_R = 0x0c;
	GPIO_PORTP_DIR_R = 0x00;
	GPIO_PORTD_AHB_DIR_R = 0x02;
	//GPIO_PORTF_AHB_DIR_R = 0x11;
	//GPIO_PORTL_DIR_R = 0x0f;

	//GPIO_PORTM_ODR_R=0x08;
	//GPIO_PORTH_AHB_ODR_R=0x0c;
//	GPIO_PORTD_AHB_ODR_R=0x02;

	GPIO_PORTN_DEN_R = 0x0f;
	GPIO_PORTM_DEN_R = 0x28;
	GPIO_PORTH_AHB_DEN_R = 0x0c;
	GPIO_PORTP_DEN_R = 0x04;
	GPIO_PORTD_AHB_DEN_R = 0x03;
	//GPIO_PORTL_DEN_R = 0x0f;

}

int identify_key()
{
	GPIO_PORTD_AHB_DATA_R &= 0xfd;
	GPIO_PORTH_AHB_DATA_R |= 0x0c;
	GPIO_PORTM_DATA_R |= 0x08;
	if ((GPIO_PORTP_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 1;
	}
	else if ((GPIO_PORTN_DATA_R & 0x08) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 5;

	}
	else if ((GPIO_PORTN_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 9;
	}
	else if ((GPIO_PORTD_AHB_DATA_R & 0x01) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 13;
	}

	GPIO_PORTD_AHB_DATA_R |= 0x02;
	GPIO_PORTH_AHB_DATA_R &= 0xf7;
	GPIO_PORTH_AHB_DATA_R |= 0x04;
	GPIO_PORTM_DATA_R |= 0x08;

	if ((GPIO_PORTP_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 2;
	}
	else if ((GPIO_PORTN_DATA_R & 0x08) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 6;
	}
	else if ((GPIO_PORTN_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 10;
	}
	else if ((GPIO_PORTD_AHB_DATA_R & 0x01) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 14;
	}

	GPIO_PORTD_AHB_DATA_R |= 0x02;
	GPIO_PORTH_AHB_DATA_R &= 0xfb;
	GPIO_PORTH_AHB_DATA_R |= 0x08;
	GPIO_PORTM_DATA_R |= 0x08;

	if ((GPIO_PORTP_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 3;
	}
	else if ((GPIO_PORTN_DATA_R & 0x08) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 7;
	}
	else if ((GPIO_PORTN_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 11;
	}
	else if ((GPIO_PORTD_AHB_DATA_R & 0x01) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 15;
	}

	GPIO_PORTD_AHB_DATA_R |= 0x02;
	GPIO_PORTH_AHB_DATA_R |= 0x0c;
	GPIO_PORTM_DATA_R &= 0xf7;

	if ((GPIO_PORTP_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 4;
	}
	else if ((GPIO_PORTN_DATA_R & 0x08) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 8;
	}
	else if ((GPIO_PORTN_DATA_R & 0x04) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 12;
	}
	else if ((GPIO_PORTD_AHB_DATA_R & 0x01) == 0x00)
	{
		if ((++Key_Flg) < Key_Dely) return 0;
		Key_Flg = 0;
		return 16;
	}

	Key_Flg = 0;
	return 0;
}
