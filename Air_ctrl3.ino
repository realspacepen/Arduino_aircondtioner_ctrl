#include <SoftwareSerial.h>
//#include "IRremote.h"
//#include "GREE_510.h"
//IRsend irsend;
volatile int NET;
SoftwareSerial mySerial(12, 11);
volatile int a;
String acture,acture_5;
String at_ok;
volatile int biaozhiwei;
volatile int biaozhiwei2;
volatile int datastate, datastate_5;
String getdata,getdata_5;
String item;
String item1;
String item2;
String item3;
volatile int long2,long5;
char * mylist[] = { 0 };
boolean Tap_Flag = 1;
volatile boolean panduan;
String pinjie;
String pinjie1;
String pinjie2;
String temp1;
String temp2;
String value,value_5;
String value1;
String value2;
volatile int value_int,value_int_5=5;
volatile int wendu;

void AT_COMEBACK(String command) {
	Serial.println(command);
	while (Serial.available() > 0) {
		at_ok = Serial.readString();
		Serial.flush();
		mySerial.println("*******");
		mySerial.println(at_ok);
		mySerial.println("*******");
	}
	for (int i = (1); i <= (String(at_ok).length()); i = i + (1)) {
		if (String(String(at_ok).charAt(i)).equals(String('O')) && String(String(at_ok).charAt((i + 1))).equals(String('K'))) {
			panduan = true;
			mySerial.println("Comeback OK");
			at_ok = '0';

		}
	}
	if(command=="Open"){ key1_down(); }
	else if(command=="Close"){ key2_down(); }
	Tap_Flag = 1;
	delay(50);
}
void AT_COMEBACK5(String x) {
	while (Serial.available() > 0) {
		if (Serial.read() == 0X2B) {
			getdata_5 = Serial.readString();
			Serial.flush();
			mySerial.println("*******");
			mySerial.println(getdata_5);
			mySerial.println("*******");

		}
	}
	long5 = String(getdata_5).length();
	if (long5 < 1024 && long5 > 0) {
		for (int i = (1); i <= (long5); i = i + (1)) {
			if (datastate_5 == 2) {
				mySerial.println(acture_5);
				if (String(acture_5).equals(String(x))) {
					datastate_5 = 3;
					mySerial.println("the value_5 is ok");

				}

			}
			if (datastate_5 == 0 && String(String(getdata_5).charAt(i)).equals(String('"'))) {
				mySerial.println("find_value_5");
				datastate_5 = 1;

			}
			if (datastate_5 == 1) {
				acture_5 = String(acture_5) + String(String(getdata_5).charAt(i + 1));
				if (String(String(getdata_5).charAt(i + 2)).equals(String('"'))) {
					datastate_5 = 2;

				}

			}
			if (datastate_5 == 3 && String(String(getdata_5).charAt(i + 2)).equals(String(':'))) {
				value_5 = String(value_5) + String(String(getdata_5).charAt(i + 3));
				if (String(String(getdata_5).charAt(i + 4)).equals(String('}'))) {
					datastate_5 = 0;
					value_int_5 = String(value_5).toInt();
					
					value_5 = "";

				}
				mySerial.println("success");

			}
		}
		datastate_5 = 0;
		acture_5 = "";
		getdata_5 = "";

	}
	delay(50);
}
void AT_COMEBACK2(String x) {
	while (Serial.available() > 0) {
		if (Serial.read() == 0X2B) {
			getdata = Serial.readString();
			Serial.flush();
			mySerial.println("*******");
			mySerial.println(getdata);
			mySerial.println("*******");

		}
	}
	long2 = String(getdata).length();
	if (long2 < 1024 && long2 > 0) {
		for (int i = (1); i <= (long2); i = i + (1)) {
			if (datastate == 2) {
				mySerial.println(acture);
				if (String(acture).equals(String(x))) {
					datastate = 3;
					mySerial.println("the value is ok");

				}

			}
			if (datastate == 0 && String(String(getdata).charAt(i)).equals(String('"'))) {
				mySerial.println("find_value");
				datastate = 1;

			}
			if (datastate == 1) {
				acture = String(acture) + String(String(getdata).charAt(i + 1));
				if (String(String(getdata).charAt(i + 2)).equals(String('"'))) {
					datastate = 2;

				}

			}
			if (datastate == 3 && String(String(getdata).charAt(i + 2)).equals(String(':'))) {
				value = String(value) + String(String(getdata).charAt(i + 3));
				if (String(String(getdata).charAt(i + 4)).equals(String('}'))) {
					datastate = 0;
					value_int = String(value).toInt();
					value = "";

				}
				mySerial.println("success");

			}
		}
		datastate = 0;
		acture = "";
		getdata = "";

	}
	delay(50);
}

void AT_COMEBACK4() {
	while (Serial.available() > 0) {
		if (Serial.read() == 0x2B) {
			item2 = Serial.readString();
			mySerial.println(item2);

		}
	}
	Serial.flush();
	delay(10);
	if (String(item2).charAt(0) == 0x49) {
		NET = 2;

	}
}

void KEY() {
//	AT_COMEBACK2("VerticalSwitch");
	AT_COMEBACK5("WorkMode");
}

void SANYUANZU() {
	AT_COMEBACK("AT+ILOPSET=a1Jm8P7vFE8,ClAw5hmSTEC9QEp5 ,ets7t8800PMm7uV3ueMlLPdKcXqU4hIV,Air_device_01");
}

void connet() {
	while (panduan == false) {
		AT_COMEBACK("AT+ILOPSTOP");
	}
	mySerial.println("stop_LOP");
	panduan = false;
	while (panduan == false) {
		AT_COMEBACK("AT+ILOPRESET");
	}
	mySerial.println("reset_LOP");
	panduan = false;
	delay(1000);
	while (panduan == false) {
		AT_COMEBACK("AT+REBOOT");
	}
	mySerial.println("reset");
	panduan = false;
	delay(1000);
	while (panduan == false) {
		AT_COMEBACK("AT");
	}
	mySerial.println("AT_model");
	panduan = false;
	while (panduan == false) {
		AT_COMEBACK("AT+UARTE=OFF");
	}
	mySerial.println("Closed serial echo successfully");
	panduan = false;
	while (panduan == false) {
		SANYUANZU();
	}
	mySerial.println("Set ilop parameter successfully");
	panduan = false;
	while (panduan == false) {
		AT_COMEBACK("AT+ILOPDOMAIN=0");
	}
	mySerial.println("The location of server ilop was set successfully");
	panduan = false;
	while (panduan == false) {
		AT_COMEBACK("AT+ILOPSTART");
	}
	mySerial.println("Service ilop started successfully");
	panduan = false;
	while (panduan == false) {
		AT_COMEBACK("AT+ILOPAWSSTART");
	}
	mySerial.println("In router configuration mode");
	for (int i = 1; i <= 10; i = i + (1)) {
		digitalWrite(2, HIGH);
		delay(200);
		digitalWrite(2, LOW);
		delay(200);
	}
	NET = 1;
	while (NET == 1) {
		AT_COMEBACK4();
	}
	if (NET == 2) {
		for (int i = 10; i <= 13; i = i + (1)) {
			item3 = String(item3) + String(String(item2).charAt(i));
		}
		mySerial.println(item3);
		if (String(item3).equals(String(":ILOP"))) {
			mySerial.println("The second step OK");
			item3 = String(item2).charAt(15);
			for (int i = 16; i <= 23; i = i + (1)) {
				item3 = String(item3) + String(String(item2).charAt(i));
			}
			mySerial.println(item3);
			if (String(item3).equals(String("CONNECTED"))) {
				mySerial.println("The third step OK");
				NET = 3;
				biaozhiwei = 0;

			}
			item3 = ":";

		}

	}
	if (NET == 3) {
		mySerial.println("Distribution network successs");

	}
}
void key1_down()
{
	digitalWrite(10, HIGH);
	digitalWrite(11, LOW);
	delay(50);
	Tap_Flag = 0;

	digitalWrite(11, HIGH);
	delay(50);
}
void key2_down()
{
	digitalWrite(10, LOW);
	digitalWrite(12, LOW);
	delay(50);
	Tap_Flag = 0;

	digitalWrite(12, HIGH);
	delay(50);
}
void function() {
	while (1) {
		if (NET == 3) {
			KEY();
			a = a + 1;
			mySerial.print("getvalue:");
			mySerial.println(value_int);
			//if (value_int == 0) {
			//	digitalWrite(5, HIGH);
			//	mySerial.println("open");// irsend.sendRaw(SweepOn_26, 279, 38);

			//}
			//if (value_int == 1) {..
			//	digitalWrite(5, LOW);
			//	mySerial.println("close"); //irsend.sendRaw(SweepOff_26, 279, 38);

			//&&Tap_Flag}
			if (value_int_5 == 0) {
			//	digitalWrite(2, HIGH);
				AT_COMEBACK("Open");
				value_int_5 = 2;
			//	key1_down();
				mySerial.println("open");// irsend.sendRaw(SweepOn_26, 279, 38);

			}
			if (value_int_5 == 1) {
				//digitalWrite(2, LOW);
				AT_COMEBACK("Close");
				value_int_5 = 2;
			//	key2_down();
				mySerial.println("close"); //irsend.sendRaw(SweepOff_26, 279, 38);

			}

		}
	}
}
//主机，接收手机信号
void setup() {
	mySerial.begin(115200);
	pinjie = "";
	pinjie1 = "";
	pinjie2 = "";
	wendu = 0;
	temp1 = "mhumi";
	temp2 = "mtemp";
	value1 = "";
	value2 = "";
	panduan = 0;
	NET = 0;
	item = "+";
	item1 = "";
	item2 = "";
	item3 = ":";
	biaozhiwei = 0;
	biaozhiwei2 = 0;
	at_ok = "";
	getdata = "";
	getdata_5 = "";
	datastate = 0;
	datastate_5 = 0;
	acture = "";
	value = "";
	value_int = 0;
	acture_5 = "";
	value_5 = "";
	value_int_5 = 0;
	a = 0;
	long2 = 0; long5 = 0;
	Serial.begin(115200);
	pinMode(5, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(10, OUTPUT);
	digitalWrite(11, HIGH);
	digitalWrite(12, HIGH);
	digitalWrite(10, HIGH);
}

void loop() {
	while (panduan == false) {
		AT_COMEBACK("AT");
	}
	mySerial.println("AT_model");
	delay(500);
	connet();
	function();

}