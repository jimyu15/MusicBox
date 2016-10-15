#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

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
	matrix.drawBitmap(0, 0, NUMBERS[tm.hour() / 10], 5, 8, color);
	matrix.drawBitmap(6, 0, NUMBERS[tm.hour() % 10], 5, 8, color);
	matrix.drawBitmap(11, 0, NUMBERS[10], 2, 8, millis() / 1000 % 2);
	matrix.drawBitmap(13, 0, NUMBERS[tm.minute() / 10], 5, 8, color);
	matrix.drawBitmap(19, 0, NUMBERS[tm.minute() % 10], 5, 8, color);
	matrix.write();
}

void printDate(DateTime tm)
{
	matrix.fillScreen(LOW);
	matrix.drawBitmap(0, 0, NUMBERS[tm.month() / 10], 5, 8, HIGH);
	matrix.drawBitmap(6, 0, NUMBERS[tm.month() % 10], 5, 8, HIGH);
	matrix.drawBitmap(11, 4, NUMBERS[10], 2, 8, HIGH);
	matrix.drawBitmap(13, 0, NUMBERS[tm.day() / 10], 5, 8, HIGH);
	matrix.drawBitmap(19, 0, NUMBERS[tm.day() % 10], 5, 8, HIGH);
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