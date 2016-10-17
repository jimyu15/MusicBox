#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define FRAME_CYCLE 60

Max72xxPanel matrix = Max72xxPanel(4, 3, 1);

const byte NUMBERS[][8] PROGMEM = {
{
  B11111000,
  B11011000,
  B11011000,
  B11011000,
  B11011000,
  B11011000,
  B11111000,
  B00000000
},{
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B00000000
},{
  B01111000,
  B00011000,
  B00011000,
  B11111000,
  B11000000,
  B11000000,
  B11111000,
  B00000000
},{
  B11111000,
  B00011000,
  B00011000,
  B01111000,
  B00011000,
  B00011000,
  B11111000,
  B00000000
},{
  B11011000,
  B11011000,
  B11011000,
  B11111000,
  B00011000,
  B00011000,
  B00011000,
  B00000000
},{
  B11110000,
  B11000000,
  B11000000,
  B11111000,
  B00011000,
  B00011000,
  B11111000,
  B00000000
},{
  B11110000,
  B11000000,
  B11000000,
  B11111000,
  B11011000,
  B11011000,
  B11111000,
  B00000000
},{
  B11111000,
  B00011000,
  B00011000,
  B00110000,
  B00110000,
  B00110000,
  B00110000,
  B00000000
},{
  B11111000,
  B11011000,
  B11011000,
  B11111000,
  B11011000,
  B11011000,
  B11111000,
  B00000000
},{
  B11111000,
  B11011000,
  B11011000,
  B11111000,
  B00011000,
  B00011000,
  B01111000,
  B00000000
},{
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  B00000000
}};

const byte SMALL_NUMBERS[][8] PROGMEM = {
{
  B11100000,
  B10100000,
  B10100000,
  B10100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B00100000,
  B11100000,
  B10000000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B00100000,
  B11100000,
  B00100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B10100000,
  B10100000,
  B11100000,
  B00100000,
  B00100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B10000000,
  B11100000,
  B00100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B10000000,
  B11100000,
  B10100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B00100000,
  B01000000,
  B01000000,
  B01000000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B10100000,
  B11100000,
  B10100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B11100000,
  B10100000,
  B11100000,
  B00100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B10000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};

const byte IMAGES[][8] PROGMEM = {
{
  B11111111,
  B11001111,
  B10110111,
  B01101011,
  B01011011,
  B10110111,
  B11001111,
  B11111111
},{
  B11111111,
  B11101111,
  B11001111,
  B11101111,
  B11101111,
  B11101111,
  B11000111,
  B11111111
},{
  B11111111,
  B10001111,
  B10110111,
  B10110111,
  B10110111,
  B10110111,
  B10001111,
  B11111111
},{
  B11111111,
  B11111111,
  B01011111,
  B01011111,
  B00010011,
  B01010111,
  B01010111,
  B11111111
}};

void matrixInit()
{
	matrix.setIntensity(7);
	matrix.setRotation(2);
	matrix.setTextColor(HIGH, LOW);
	matrix.setTextSize(1);
	matrix.setTextWrap(false);
}

void matrixTest()
{
	matrix.fillScreen(LOW);
	matrix.setCursor(millis() / 40 % 200 * -1 + 24, 0);
	matrix.print("Happy birthday, my babe <3");
    matrix.write(); // Send bitmap to display

    delay(20);

}


void printTime(DateTime tm, uint8_t color)
{
	matrix.fillScreen(!color);
	matrix.drawBitmap(0, 0, NUMBERS[tm.hour() / 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(6, 0, NUMBERS[tm.hour() % 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(11, 0, NUMBERS[10], 2, 8, millis() / 500 % 2);
	matrix.drawBitmap(13, 0, NUMBERS[tm.minute() / 10], 5, 8, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(19, 0, NUMBERS[tm.minute() % 10], 5, 8, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.write();
}


void printTimeSmall(DateTime tm, uint8_t color, int x, int y)
{
	
	matrix.drawBitmap(x, y, SMALL_NUMBERS[tm.hour() / 10], 3, 5, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(x + 4, y, SMALL_NUMBERS[tm.hour() % 10], 3, 5, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(x + 8, y, SMALL_NUMBERS[10], 1, 5, color);
	matrix.drawBitmap(x + 10, y, SMALL_NUMBERS[tm.minute() / 10], 3, 5, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(x + 14, y, SMALL_NUMBERS[tm.minute() % 10], 3, 5, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.write();
}


void printDate(DateTime tm, uint8_t color)
{
	matrix.fillScreen(!color);
	matrix.drawBitmap(0, 0, NUMBERS[tm.month() / 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(6, 0, NUMBERS[tm.month() % 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(11, 4, NUMBERS[10], 2, 8, HIGH);
	matrix.drawBitmap(13, 0, NUMBERS[tm.day() / 10], 5, 8, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(19, 0, NUMBERS[tm.day() % 10], 5, 8, color & 0x4 ? millis() / 500 % 2 : color & 1);
	matrix.write();
}

void printYear(DateTime tm, uint8_t color)
{
	matrix.fillScreen(!color);
	matrix.drawBitmap(0, 0, NUMBERS[tm.year() / 1000], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(6, 0, NUMBERS[tm.year() / 100 % 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(12, 0, NUMBERS[tm.year() / 10 % 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.drawBitmap(18, 0, NUMBERS[tm.year() % 10], 5, 8, color & 0x2 ? millis() / 500 % 2 : color & 1);
	matrix.write();
}

void printTemp(int temp)
{
	matrix.fillScreen(LOW);
	matrix.drawBitmap(0, 0, NUMBERS[temp / 10], 5, 8, HIGH);
	matrix.drawBitmap(6, 0, NUMBERS[temp % 10], 5, 8, HIGH);
	matrix.drawBitmap(11, 4, NUMBERS[10], 2, 8, HIGH);
	matrix.drawBitmap(14, 0, NUMBERS[temp * 10 % 10], 5, 8, HIGH);
	matrix.write();
}

void printAlarmHome(DateTime tm, uint8_t mode, uint8_t flash)
{
	matrix.fillScreen(HIGH);
	matrix.drawBitmap(18, 0, IMAGES[mode], 7, 8, LOW);
	printTimeSmall(tm, flash, 0, 2);
}

void printText(String txt, uint8_t color, int x, int y)
{
	matrix.setCursor(x, y);
	matrix.setTextColor(color, !color);
	matrix.print(txt);
}

uint8_t scrollText(String txt, uint8_t color, uint32_t startTime)
{
	if (txt.length() * 6 + 48 < (millis() - startTime) / FRAME_CYCLE)
	{
		//Serial.print((int)sizeof(txt));
		//Serial.println();
		return 0;
	}
	matrix.fillScreen(!color);
	printText(txt, color, 24 + (millis() - startTime) / FRAME_CYCLE * -1, 0);
	matrix.write();
	return 1;
}