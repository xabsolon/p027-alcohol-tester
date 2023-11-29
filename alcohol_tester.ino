#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define MQ3pin 3

#define Sober 250

float sensor_value;

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool should_measure = false;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  display.display();
  delay(2000);

  display.clearDisplay();

  Serial.println("MQ3 warming up!");
	warmingUpText();
  should_measure = true;
}

void loop() {
  if (should_measure) {
    sensor_value = analogRead(MQ3pin);
    renderSensorValue();
  }
}

void renderSensorValue(void) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 0);
  display.print(F("Sensor value: "));
  display.print(sensor_value);
  display.setTextSize(2);
  display.setCursor(5, 10);
  if (sensor_value < Sober) {
    display.print(F("Sober"));
	} else {
    display.print(F("Drunk"));
	}
  display.display();
  delay(100);
}

void warmingUpText(void) {
  for (int i = 10; i >= 0; i--) {
    Serial.println(i);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5, 0);
    display.print(F("Warming up: "));
    display.setTextSize(2);
    display.setCursor(5, 10);
    display.print(i);
    display.print("s");
    display.display();
    delay(1000);
  }
}
