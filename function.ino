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
#define ALARM_HOME 5
#define SET_TIME 6
#define PLAY_ONCE 7
#define PLAY_LOOP 8
#define SET_DATE 9


uint8_t mode = 0;
uint32_t ledStat = 0;

void home()
{
	uint8_t st = readTouch();
	if (ledStat)
	{
		if (st)
			ledStat = millis();
		else if (millis() - ledStat > 5000)
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
				mode = DATE;
			else if (st == UP_SHORT)
				mode = TEMP;
			else if (st == SET_LONG)
				mode = SET_TIME;
			else
				switchFunction(st);
		}

		break;

		case DATE:
		{
			printDate(getTime());
			if (st == DOWN_SHORT)
				mode = TEMP;
			else if (st == UP_SHORT)
				mode = CLOCK;
			else if (st == SET_LONG)
				mode = SET_DATE;
			else
				switchFunction(st);
		}
		break;

		case TEMP:
		{
			printTemp(getTemp());
			if (st == DOWN_SHORT)
				mode = CLOCK;
			else if (st == UP_SHORT)
				mode = DATE;
			else
				switchFunction(st);
		}
		break;

		case ALARM_HOME:
		{
			DateTime alarm(2016, 10, 14, readAlarmHr(), readAlarmMin(), 55);
			printTime(alarm, LOW);
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
		case DOWN_SHORT:
		mode = PLAY_LOOP;
		break;
	}
}