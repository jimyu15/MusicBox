const uint8_t ledPin[4] = {6, 5, 0, 1};

void ledInit()
{
	for (int i = 0; i < 4; i++)
	{
		pinMode(ledPin[i], OUTPUT);
		digitalWrite(ledPin[i], LOW);
	}
}

void ledWrite(uint8_t state)
{
	for (int i = 0; i < 4; i++)
	{
		digitalWrite(ledPin[i], state & 1);
		state /= 2;
	}
}

void ledWrite(uint8_t num, uint8_t state)
{
	digitalWrite(ledPin[num], state);
}