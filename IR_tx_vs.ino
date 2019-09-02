/*
* arduino遥控空调
*/

//By Yang Shuo
//http://blog.csdn.net/worldmakewayfordream
//Update: Pin 3 IR LED test function

#include "GREE_510.h"
#include <IRremote.h>                  // 引用 IRRemote 函式库
#include <avr/pgmspace.h>
#define KEY11 digitalRead(11)
#define KEY12 digitalRead(12)
#define KEY10 digitalRead(10)
unsigned short i=26;
unsigned int buffer[279];

IRsend irsend;                          // 定义 IRsend 物件来发射红外线讯号
void Flash2RAM(const unsigned int *pointer)
{
	for (int j = 0; j < 279; j++)
	{
		buffer[j]= pgm_read_word_near(pointer + j);
	}
}
void key11_down()
{
	if (KEY11 == 0&&KEY10==1)
	{
		delay(30);
		i++; Serial.println(i);
		digitalWrite(2, LOW);
		if (i > 30)i = 30;
		Temp_ctrl(i);
		delay(50);
	}
}
void key12_down()
{
	if (KEY12 == 0&&KEY10 == 0)
	{
		delay(30);
		i--;
		Serial.println(i);
		digitalWrite(2, HIGH);
		if (i <16)i = 16;
		Temp_ctrl(i);
		delay(50);
	}
}

void Temp_ctrl(unsigned int tmp)
{
	switch (tmp) 
	{
		case 30:
			Flash2RAM(Temp_30); irsend.sendRaw(buffer, 279, 38); break;
		case 29:
			Flash2RAM(Temp_29); irsend.sendRaw(buffer, 279, 38); break;
		case 28:
			Flash2RAM(Temp_28); irsend.sendRaw(buffer, 279, 38); break;
		case 27:
			Flash2RAM(Temp_27); irsend.sendRaw(buffer, 279, 38); break;
		case 26:
			Flash2RAM(SweepOn_26); irsend.sendRaw(buffer, 279, 38); break;
		case 25:
			Flash2RAM(Temp_25); irsend.sendRaw(buffer, 279, 38); break;
		case 24:
			Flash2RAM(Temp_24); irsend.sendRaw(buffer, 279, 38); break;
		case 23:
			Flash2RAM(Temp_23); irsend.sendRaw(buffer, 279, 38); break;
		case 22:
			Flash2RAM(Temp_22); irsend.sendRaw(buffer, 279, 38); break;
		case 21:
			Flash2RAM(Temp_21); irsend.sendRaw(buffer, 279, 38); break;
		case 20:
			Flash2RAM(Temp_20); irsend.sendRaw(buffer, 279, 38); break;
		case 19:
			Flash2RAM(Temp_19); irsend.sendRaw(buffer, 279, 38); break;
		case 18:
			Flash2RAM(Temp_18); irsend.sendRaw(buffer, 279, 38); break;
		case 17:
			Flash2RAM(Temp_17); irsend.sendRaw(buffer, 279, 38); break;
		case 16:
			Flash2RAM(Temp_16); irsend.sendRaw(buffer, 279, 38); break;
		default :
			Flash2RAM(SweepOff_26); irsend.sendRaw(buffer, 279, 38); break;
	}
}
void setup()
{
	Serial.begin(115200);
	pinMode(3, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(11, INPUT);
	pinMode(12, INPUT);
	pinMode(10, INPUT);
	digitalWrite(3, HIGH);   
	delay(3000);             // 等待3秒
	digitalWrite(3, LOW);    // 结束测试
	//digitalWrite(11, HIGH);
	//digitalWrite(12, HIGH);
}

void loop()
{
	// digitalWrite(3, HIGH); 
	//	Serial.print("SendIR: ");
	key11_down();
	key12_down();
	

}

/*Flash2RAM(SweepOn_26);
irsend.sendRaw(buffer, 279, 38);
delay(1000);   */          // 等待3秒