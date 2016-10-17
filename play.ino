#define MOTOR1 9
#define MOTOR2 10
#define SENSOR1 A2
#define SENSOR2 14
#define PLAYTIME 40000

uint32_t startTime;
uint8_t playStat = 0;
uint8_t sensorBuffer[2][30];

void playInit()
{
	pinMode(MOTOR1, OUTPUT);
	pinMode(MOTOR2, OUTPUT);
	pinMode(SENSOR2, INPUT);
	pinMode(SENSOR1, INPUT);
	digitalWrite(MOTOR1, LOW);
	digitalWrite(MOTOR2, LOW);
	for (int i = 0; i < 10; i++)
	{
		sensorBuffer[0][i] = 0;
		sensorBuffer[1][i] = 0;
	}

}

uint8_t readSensor()
{
	uint8_t sum[2] = {0, 0};
	for (int i = 29; i > 0; i--)
	{
		sum[0] += sensorBuffer[0][i];
		sum[1] += sensorBuffer[1][i];
		sensorBuffer[0][i] = sensorBuffer[0][i - 1];
		sensorBuffer[1][i] = sensorBuffer[1][i - 1];
	}
	sensorBuffer[0][0] = digitalRead(SENSOR1);
	sensorBuffer[1][0] = digitalRead(SENSOR2);
	return (sum[1] > 5) * 2 + (sum[0] == 29);
}

uint8_t getPlayStat()
{
	if (playStat == 1)
		playStat = 0;
	return playStat;
}

void playOnce()
{
	if (playStat == 0)
		playStat = 4;
}

void playLoop()
{
	if (playStat == 0)
		playOnce();
}

void play()
{
	
	switch(playStat)
	{
		case 4:
		startTime = millis();
		digitalWrite(MOTOR1, HIGH);
		digitalWrite(MOTOR2, HIGH);
		playStat = 3;
		break;

		case 3:
		if (millis() - startTime > 6000)
		{
			if (readSensor() & 1 || millis() - startTime > PLAYTIME)
			{
				digitalWrite(MOTOR1, LOW);
				playStat = 1;
			}
			
		}
		break;

		default:
		if (readSensor() & 2 || millis() - startTime > PLAYTIME + 10000)
		{
			digitalWrite(MOTOR2, LOW);
			playInit();
		}
		break;

		

	}

}
