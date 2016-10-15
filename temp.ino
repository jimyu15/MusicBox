#include <WSWire.h>
#include <LM75.h>

LM75 sensor;

void tempInit()
{
	Wire.begin();
	//sensor.shutdown(false);
}

int getTemp()
{
	return sensor.temp();
}