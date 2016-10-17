#include <EEPROM.h>

#define DOWN_SHORT 0x01
#define UP_SHORT 0x02
#define SET_SHORT 0x04
#define AL_SHORT 0x08
#define DOWN_LONG 0x10
#define UP_LONG 0x20
#define SET_LONG 0x40
#define AL_LONG 0x80

#define CLOCK 0
#define DATE 1
#define TEMP 2
#define ALARM_HOME 3
#define SET_ALARM_HR 4
#define SET_ALARM_MIN 5
#define SET_TIME_HR 6
#define SET_TIME_MIN 7
#define PLAY_ONCE 8
#define PLAY_LOOP 9
#define SET_MON 10
#define SET_DAY 11
#define SET_YEAR 12

#define TEXT_COUNT 7
const String dayText[] = {
	"Can't have a day without missing you baby",
	"I'm in love with you baby",
	"Miss you baby",
	"Wo Hao Xi Huan Ni",
	"HeeHee~~~~",
	"Each day with you is a perfect day",
	"Baby so cute"
};


uint8_t mode = 0;
uint32_t ledStat = 0;
uint8_t textIndex = 0;

void randomInit()
{
	DateTime now = getTime();
	if (EEPROM.read(0x20) == now.day())
	{
		textIndex = EEPROM.read(0x24);
		return;
	}
	randomSeed(now.secondstime() * 2 / 86400 % 300);
	uint8_t seed[5];
	do
	{
		seed[4] = random(TEXT_COUNT);
		for (int i = 0; i < 4; i++)
		{
			seed[i] = EEPROM.read(0x21 + i);
			if (seed[i] == seed[4])
				seed[4] = TEXT_COUNT + 1;
		}
	} while (seed[4] > TEXT_COUNT);

	textIndex = seed[4];

	for (int i = 0; i < 4; i++)
	{
		EEPROM.write(0x21 + i, seed[i + 1]);
	}
	EEPROM.write(0x20, now.day());
}

void home()
{
	DateTime now = getTime();
	if (getAlarmMin() == now.minute() && now.second() < 5)
	{
		if (getAlarmMode() == 3)
			mode = PLAY_ONCE;
		else if(getAlarmHr() == now.hour() && getAlarmMode() > 0)
		{
			mode = PLAY_LOOP;
			if (getAlarmMode() == 1)
				setAlarmMode(0);
		}
	}
	play();
	alarmLed();

	uint8_t st = readTouch();
	if (ledStat)
	{
		if (st)
			ledStat = millis();
		else if (millis() - ledStat > 5000 && mode < 8)
		{
			ledWrite(0);
			mode = 0;
			ledStat = 0;
		}
		else if (mode == PLAY_LOOP || mode == PLAY_ONCE)
			ledWrite(0);
	}
	else if (st)
	{
		ledWrite(0x0F);
		ledStat = millis();
		st = 0;
	}


	switch (mode)
	{
		case CLOCK:
		{
			printTime(getTime(), HIGH);
			if (st == DOWN_SHORT)
				mode = DATE;
			else if (st == UP_SHORT)
				mode = DATE;
			else if (st == SET_LONG)
				mode = SET_TIME_HR;
			else
				switchFunction(st);
		}

		break;

		case DATE:
		{
			printDate(getTime(), 1);
			if (st == DOWN_SHORT)
				mode = CLOCK;
			else if (st == UP_SHORT)
				mode = CLOCK;
			else if (st == SET_LONG)
				mode = SET_YEAR;
			else
				switchFunction(st);
		}
		break;

		case TEMP:
		{
			printTemp(getTemp());
			if (st == DOWN_SHORT)
				mode = DATE;
			else if (st == UP_SHORT)
				mode = CLOCK;
			else
				switchFunction(st);
		}
		break;

		case ALARM_HOME:
		{
			DateTime alarm(2016, 10, 14, getAlarmHr(), getAlarmMin(), 55);
			printAlarmHome(alarm, getAlarmMode(), 0);
			ledWrite(0xF);
			if (st == DOWN_SHORT || st == DOWN_LONG)
				setAlarmMode(getAlarmMode() - 1);
			else if (st == UP_SHORT || st == UP_LONG)
				setAlarmMode(getAlarmMode() + 1);
			else if (st == SET_LONG)
				mode = SET_ALARM_HR;
			else if (st == AL_SHORT || st == AL_LONG)
				mode = CLOCK;

		}
		break;

		case SET_ALARM_HR:
		{
			DateTime alarm(2016, 10, 14, getAlarmHr(), getAlarmMin(), 55);
			printAlarmHome(alarm, getAlarmMode(), 2);
			if (st == DOWN_SHORT || st == DOWN_LONG)
				setAlarmHr(getAlarmHr() - 1);
			else if (st == UP_SHORT || st == UP_LONG)
				setAlarmHr(getAlarmHr() + 1);
			else if (st == SET_LONG)
				mode = ALARM_HOME;
			else if (st == SET_SHORT)
				mode = SET_ALARM_MIN;
		}
		break;

		case SET_ALARM_MIN:
		{
			DateTime alarm(2016, 10, 14, getAlarmHr(), getAlarmMin(), 55);
			printAlarmHome(alarm, getAlarmMode(), 4);
			if (st == DOWN_SHORT || st == DOWN_LONG)
				setAlarmMin(getAlarmMin() - 1);
			else if (st == UP_SHORT || st == UP_LONG)
				setAlarmMin(getAlarmMin() + 1);
			else if (st == SET_LONG || st == SET_SHORT)
			{
				mode = ALARM_HOME;
				if (getAlarmMode() == 0)
					setAlarmMode(1);
			}	
		}
		break;

		case SET_TIME_HR:
		{
			DateTime now = getTime();
			printTime(getTime(), 3);
			if (st == DOWN_SHORT || st == DOWN_LONG)
			{
				now = now - TimeSpan(0, 1, 0, 0);
				setTime(now);
			}
			else if (st == UP_SHORT || st == UP_LONG)
			{
				now = now + TimeSpan(0, 1, 0, 0);
				setTime(now);
			}
			else if (st == SET_SHORT)
				mode = SET_TIME_MIN;
			else if (st == SET_LONG)
				mode = CLOCK;	
		}
		break;

		case SET_TIME_MIN:
		{
			DateTime now = getTime();
			printTime(getTime(), 5);
			if (st == DOWN_SHORT || st == DOWN_LONG)
			{
				now = now - TimeSpan(0, 0, 1, 0);
				setTime(now);
			}
			else if (st == UP_SHORT || st == UP_LONG)
			{
				now = now + TimeSpan(0, 0, 1, 0);
				setTime(now);
			}
			else if (st == SET_SHORT || st == SET_LONG)
				mode = CLOCK;
		}
		break;

		case SET_YEAR:
		{
			DateTime now = getTime();
			printYear(getTime(), 3);
			if (st == DOWN_SHORT || st == DOWN_LONG)
			{
				now = now - TimeSpan(365, 0, 0, 0);
				setTime(now);
			}
			else if (st == UP_SHORT || st == UP_LONG)
			{
				now = now + TimeSpan(365, 0, 0, 0);
				setTime(now);
			}
			else if (st == SET_SHORT)
				mode = SET_MON;
			else if (st == SET_LONG)
				mode = DATE;	
		}
		break;

		case SET_MON:
		{
			DateTime now = getTime();
			printDate(getTime(), 3);
			if (st == DOWN_SHORT || st == DOWN_LONG)
			{
				now = now - TimeSpan(30, 0, 0, 0);
				setTime(now);
			}
			else if (st == UP_SHORT || st == UP_LONG)
			{
				now = now + TimeSpan(30, 0, 0, 0);
				setTime(now);
			}
			else if (st == SET_SHORT)
				mode = SET_DAY;
			else if (st == SET_LONG)
				mode = DATE;	
		}
		break;

		case SET_DAY:
		{
			DateTime now = getTime();
			printDate(getTime(), 5);
			if (st == DOWN_SHORT || st == DOWN_LONG)
			{
				now = now - TimeSpan(1, 0, 0, 0);
				setTime(now);
			}
			else if (st == UP_SHORT || st == UP_LONG)
			{
				now = now + TimeSpan(1, 0, 0, 0);
				setTime(now);
			}
			else if (st == SET_SHORT || st == SET_LONG)
				mode = DATE;
		}
		break;

		case PLAY_ONCE:
		{
			static uint32_t startTime = millis();
			DateTime now = getTime();
			showText(now, 1, startTime);
			playOnce();
			if (getPlayStat() == 0)
				mode = CLOCK;
		}
		break;

		case PLAY_LOOP:
		{
			static uint8_t loopStat = 9;
			static uint32_t startTime = millis();
			DateTime now = getTime();
			showText(now, loopStat == 0, startTime);
			playOnce();
			if (getPlayStat() == 0)
			{
				Serial.println(loopStat);
				if (loopStat == 0)
				{
					mode = CLOCK;
					loopStat = 9;
				}
				else
					loopStat--;
			}
			if (st >= 0x10)
				loopStat = 0;
		}
		break;


		default:
		break;
	}
	
	touchPoll();

}

void switchFunction(uint8_t st)
{
	switch (st)
	{
		case SET_SHORT:
		mode = CLOCK;
		break;
		case AL_SHORT:
		case AL_LONG:
		mode = ALARM_HOME;
		break;
		case UP_LONG:
		mode = PLAY_ONCE;
		break;
		case DOWN_LONG:
		mode = PLAY_LOOP;
		break;
	}
}

String getSentence(DateTime tm)
{
	if (tm.month() == 10 && tm.day() == 22)
	{
		return String("Happy birthday my dear YowYow! You are the apple of my eye") + String(char(3));
	}
	if (tm.day() == 12)
	{
		if (tm.month() == 8)
		{
			return "Today is our anniversary! Thank you for being a part of my life, my babe. I love you from the bottom of my heart.";
		}
		int count = (tm.year() - 2016) * 12 + tm.month() - 8;
		return String("It's our ") + String(count) + String("-month anniversary! Jim") + String(char(3)) + String("Yow");
	}
	TimeSpan dayCount = tm - DateTime(2016, 8, 12, 0, 0, 0);
	if (dayCount.days() % 100 == 0)
		return String("It's our ") + String(dayCount.days()) + String("-day anniversary! You are my baby") + String(char(3));
	return dayText[textIndex] + String(char(3));

}

void showText(DateTime tm, uint8_t color, uint32_t startTime)
{
	static uint32_t st = 0;
	if (startTime > st)
		st = startTime;
	if (!scrollText(getSentence(tm), color, st))
	{
		static uint32_t clockTime = 0;
		if (clockTime == 0)
			clockTime = millis();
		printTime(tm, color);
		if (millis() - clockTime > 4000)
		{
			clockTime = 0;
			st = millis();
		}
	}
}