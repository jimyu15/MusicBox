extern const uint8_t touchPin[4] = {7, A1, 8, A0};
uint8_t touchPos = 0, touchStat = 0;
uint32_t touchTime = 0;

void touchInit()
{
	for (int i = 0; i < 4; i++)
	{
		pinMode(i, INPUT);
	}
}

uint8_t touchTest(uint8_t num)
{
	return digitalRead(touchPin[num]);
}

int getTouchPos()
{
	uint8_t touchRead = 0;
	for (int i = 0; i < 4; i++)
	{
		touchRead *= 2;
		touchRead += digitalRead(touchPin[i]);
	}
	return touchRead;
}

void touchPoll()
{
	int touchRead = getTouchPos();
	
	if (touchPos == 0 && touchRead > 0)
	{
		touchTime = millis();
		touchPos = touchRead;
		return;
	}

	else if (touchRead == 0 && touchPos > 0)
	{
		if (millis() - touchTime > 20 && millis() - touchTime < 500)
			touchStat = touchPos;
		touchPos = 0;
	}

	else if (touchPos > 0 && touchPos < 0x10 && millis() - touchTime > 1500)
	{
		touchStat = touchPos << 4;
		touchPos = 0x10;
	}

	if (touchPos == 0)
		touchPos = touchRead;

}

uint8_t readTouch()
{
	touchPoll();
	uint8_t st = touchStat;
	touchStat = 0;
	if (st)
		Serial.println(st);
	return st;
}