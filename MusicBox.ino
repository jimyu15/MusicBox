#include "RTClib.h"



void setup()
{
	
	Serial.begin(115200);
	matrixInit();
	touchInit();
	ledInit();
	delay(100);
	rtcInit();
	tempInit();
	playInit();

	
	randomInit();

	

}

void loop()
{
	home();
}



void touch()
{
	uint8_t tt = readTouch();
	if (tt)
		Serial.println(tt);
}
void functionTest()
{
	for (int i = 0; i < 4; i++)
	{
		ledWrite(i, (millis() / 1000 % 4) == i ? 1 : 0);
		Serial.print("\ttouch");
		Serial.print(i);
		Serial.print(": ");
		Serial.print(touchTest(i));
	}
	Serial.println();

	uint8_t bm[24] = {0};
	if (millis()/ 1000 % 2)
	{
		for (int i = 0; i < 24; i++)
			if (i % 8 == 1)
				bm[i] = 0x03;
	}

	//matrixFill(bm);
	//matrixRefresh();



}