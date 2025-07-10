#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
// address through which two modules communicate
const byte address[6] = "00001";

struct Data {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};
Data data;

// declare OLED display 
Adafruit_SSD1306 display(OLED_RESET);
const byte SSD1306_ADDR_3 = 0x3C;

void setup()
{
  /* UNCOMMENT TO START SERIAL MONITOR */
  // Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDR_3);

  // setup radio write pipe
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);

  data.ch1 = 0;
  data.ch2 = 0;
  data.ch3 = 0;
  data.ch4 = 0;
}

void loop()
{
  display.clearDisplay();

  // map analog joy stick values
  data.ch1 = 255 - map(analogRead(A0), 0, 1024, 0, 255);
  data.ch2 = map(analogRead(A1), 0, 1024, 0, 255);
  data.ch3 = map(analogRead(A7), 0, 1024, 0, 255);
  data.ch4 = 255 - map(analogRead(A6), 0, 1024, 0, 255);

  // write to radio address
  radio.write(&data, sizeof(Data));
  
  //configure and write mapped joy stick values to display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.print("LV: "); display.print(data.ch2); 
  display.print(" LH: "); display.print(data.ch1);
  display.println();
  display.print("RV: "); display.print(data.ch4);
  display.print(" RH: "); display.print(data.ch3);
  display.println();
  
  display.display();
  delay(100);
}