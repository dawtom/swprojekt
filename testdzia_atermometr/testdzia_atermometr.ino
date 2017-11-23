#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <DallasTemperature.h>
#include <OneWire.h>

#include <stdio.h>



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
  pinMode(2, INPUT_PULLUP);
  sensors.begin(); 
  Serial.begin(9600);

 
}
 
void loop(void){

  sensors.requestTemperatures();
    char arr [32] = "dddd";
        
    float zmienna = sensors.getTempCByIndex(0);

    int z = 5.0;
    char charVal[10];                
    //snprintf(arr,32, "%d",zmienna);// zmienna);
    dtostrf(zmienna, 10, 7, arr);
    //Serial.print(zmienna);
    Serial.print(arr);
  radio.write(&arr, sizeof(arr));
  delay(1000);
 
}
/*
#include <stdio.h>
#include <math.h>

int main()
{
    float x = 1.0/7.0;
    
    char arr [80];
    sprintf(arr, "Value of Pi = %f", x);
    
    printf(arr);

    return 0;
}
*/
