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



uint8_t mode = 0;
uint32_t ledStat = 0;

void home()
{
	play();
	uint8_t st = readTouch();
	if (ledStat)
	{
		if (st)
			ledStat = millis();
		else if (millis() - ledStat > 10000 && mode < 8)
		{
			ledWrite(0);
			mode = 0;
			ledStat = 0;
		}
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
				mode = TEMP;
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
				mode = TEMP;
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
			Serial.println(getAlarmMode());
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
		playOnce();
		if (getPlayStat() == 0)
			mode = CLOCK;
		break;

		case PLAY_LOOP:
		getPlayStat();
		playOnce();
		if (st >= 0x10)
			mode = CLOCK;
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