#include <stdlib.h>
#include <avr/pgmspace.h>

#include "SSD1306_minimal.h"

#define OLED_I2C_ADDR b0111100

SSD1306_Mini oled;

//byte array of bitmap 17x16 px
const unsigned char img_heart_small[] PROGMEM = {
    0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00
};

//byte array of bitmap 17x16 px
const unsigned char img_heart_big[] PROGMEM = {
    0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00
};

void heartBeat() {
	static char big = 1;
	static long startTime = 0;

	// get current time
	long currentTime = millis();

	// update if 1000ms passed
	if ((currentTime - startTime) > 200) {
		startTime = currentTime;

		big = 1 - big;
		if (big) {
			//digitalWrite(1, HIGH);
			oled.drawImage(img_heart_big, 10, 0, 17, 1);
		} else {
			//digitalWrite(1, LOW);
			oled.drawImage(img_heart_small, 10, 0, 17, 2);
		}
	}
}

void setup() {
	for (int pin = 0; pin < 6; pin++) {
		pinMode(pin, OUTPUT);
	}

	digitalWrite(0, LOW);
	digitalWrite(1, LOW);
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);

	oled.init(0x3c);
	oled.clear();

	delay(100);

	oled.startScreen();
	oled.clear();

	oled.cursorTo(0, 2);
	oled.printString("Lynx loves");
	oled.cursorTo(0, 3);
	oled.printString("Lioness!");

	delay(500);
}

void loop() {
	heartBeat();
}
