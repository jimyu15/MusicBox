#define MOTOR1 9
#define MOTOR2 10
#define SENSOR1 14
#define SENSOR2 A2
#define PLAYTIME 15000

uint32_t startTime;
uint8_t playStat = 2;

void playInit()
{
	pinMode(MOTOR1, OUTPUT);
	pinMode(MOTOR2, OUTPUT);
	pinMode(SENSOR2, INPUT);
	pinMode(SENSOR1, INPUT);
	digitalWrite(MOTOR1, LOW);
	digitalWrite(MOTOR2, LOW);

}

void play()
{
	if (playStat == 0)
	{
		startTime = millis();
		digitalWrite(MOTOR1, HIGH);
		digitalWrite(MOTOR2, HIGH);
		playStat = 1;
	}

	if (playStat)
	{
		if (millis() - startTime > 1500)
		{
			if (digitalRead(SENSOR1) || millis() - startTime > PLAYTIME)
			{
				digitalWrite(MOTOR1, LOW);
				playStat = 2;
			}
			if (digitalRead(SENSOR2) || millis() - startTime > PLAYTIME)
			{
				digitalWrite(MOTOR2, LOW);
				playStat = 3;
			}
		}
	}

}
