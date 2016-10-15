#include <EEPROM.h>

#define HR_ADDR 0x05
#define MIN_ADDR 0x06

void setAlarmTime(uint8_t hr, uint8_t min)
{
	EEPROM.write(HR_ADDR, hr);
	EEPROM.write(MIN_ADDR, min);
}

void setAlarmTime(uint16_t altime)
{
	setAlarmTime(altime >> 8, altime & 0xFF);
}

uint16_t readAlarmTime()
{
	return (EEPROM.read(HR_ADDR) << 8) + EEPROM.read(MIN_ADDR);
}

uint8_t readAlarmHr()
{
	return EEPROM.read(HR_ADDR);
}

uint8_t readAlarmMin()
{
	return EEPROM.read(MIN_ADDR);
}