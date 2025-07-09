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
Data myData;

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

  myData.ch1 = 0;
  myData.ch2 = 0;
  myData.ch3 = 0;
  myData.ch4 = 0;
}

void loop()
{
  display.clearDisplay();

  // map analog joy stick values
  myData.ch1 = 255 - map(analogRead(A0), 0, 1024, 0, 255);
  myData.ch2 = map(analogRead(A1), 0, 1024, 0, 255);
  myData.ch3 = map(analogRead(A7), 0, 1024, 0, 255);
  myData.ch4 = 255 - map(analogRead(A6), 0, 1024, 0, 255);

  // write to radio address
  radio.write(&myData, sizeof(Data));
  
  //configure and write mapped joy stick values to display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.print("LV: "); display.print(myData.ch2); 
  display.print(" LH: "); display.print(myData.ch1);
  display.println();
  display.print("RV: "); display.print(myData.ch4);
  display.print(" RH: "); display.print(myData.ch3);
  display.println();
  
  display.display();
  delay(100);
}