#include <EEPROM.h>

#define HR_ADDR 0x05
#define MIN_ADDR 0x06
#define MODE_ADDR 0x07
#define NUM_ALARM_MODE 4

uint8_t alarmMode = 0;

void eepromInit()
{
	setAlarmTime(0, 0);
	setAlarmMode(0);
}

void setAlarmTime(uint8_t hr, uint8_t min)
{
	EEPROM.write(HR_ADDR, hr);
	EEPROM.write(MIN_ADDR, min);
}

void setAlarmTime(uint16_t altime)
{
	setAlarmTime(altime >> 8, altime & 0xFF);
}

uint16_t getAlarmTime()
{
	return (EEPROM.read(HR_ADDR) << 8) + EEPROM.read(MIN_ADDR);
}

int getAlarmHr()
{
	return EEPROM.read(HR_ADDR);
}

int getAlarmMin()
{
	return EEPROM.read(MIN_ADDR);
}

void setAlarmHr(int hr)
{
	EEPROM.write(HR_ADDR, (hr + 24) % 24);
}

void setAlarmMin(int min)
{
	EEPROM.write(MIN_ADDR, (min + 60) % 60);
}

int getAlarmMode()
{
	return EEPROM.read(MODE_ADDR);
}

void setAlarmMode(int m)
{
	EEPROM.write(MODE_ADDR, (m + NUM_ALARM_MODE) % NUM_ALARM_MODE);
}