#include <WSWire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void rtcInit()
{
	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
	}
	if (rtc.lostPower()) 
	{
    	rtc.adjust(DateTime(2016, 10, 14, 20, 22, 55));
	}
}

void setTime(int hr, int min, int sec)
{
	TimeSpan span(0, hr, min, sec);
	DateTime now = rtc.now() + span;
	rtc.adjust(now);
}

void setTime(DateTime tm)
{
	rtc.adjust(tm);
}

DateTime getTime()
{
	return rtc.now();
}