#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <DallasTemperature.h>
#include <OneWire.h>




#include<SPI.h>

#define ONE_WIRE_BUS 2 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


// ce, csn pins
RF24 radio(9, 10);
 
void setup(void){

  // radio initialization
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

  // temperature sensor initialization
  sensors.begin(); 
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
 
}
 
void loop(void){

  sensors.requestTemperatures();
    char *text;
    text = (char *)malloc(32);
    
    float zmienna = sensors.getTempCByIndex(0);
    Serial.write("tekst %lf",zmienna);
  radio.write(&zmienna, sizeof(text));
  delay(1000);
 
}

