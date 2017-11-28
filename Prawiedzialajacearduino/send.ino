#include <DallasTemperature.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24_config.h>
#include <RF24.h>



#include<SPI.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#include "main.h"

#define ONE_WIRE_BUS 2 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


//void setupStructure(struct DataToSendToRaspberry * data, int id, int key){
//    data->id = id;
//    data->key= key;
//}

// ce, csn pins
RF24 radio(9, 10);

 struct DataToSendToRaspberry dataToSendToRaspberry;

char temperatureString[8];
char toSendString[24];


float temperature;

int temperatureLength;
int temperaturePrecision;
void setup(void){
  
  //dataToSendToRaspberry = (struct DataToSendToRaspberry *)malloc(sizeof(struct DataToSendToRaspberry));

  dataToSendToRaspberry = {1234,5768,0.0,0};
  
  // radio initialization
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

  // temperature sensor initialization
  sensors.begin(); 
  pinMode(2, INPUT_PULLUP);

    

    Serial.begin(9600);
 
}
 
void loop(void){


    sensors.requestTemperatures();
Serial.print("test\n");
//     actual temperature reading
    temperature = sensors.getTempCByIndex(0);
//    Serial.print("1");
    dataToSendToRaspberry.temperature = temperature;
//    Serial.print("2");
    
    temperatureLength = setTemperatureLength(dataToSendToRaspberry.temperature);
//    Serial.print("25");
    temperaturePrecision = setTemperaturePrecision(dataToSendToRaspberry.temperature);
//    Serial.print(temperature);
    
//Serial.print("3");

    dtostrf(temperature,temperatureLength,temperaturePrecision,temperatureString);
//Serial.print(temperatureString);
    sprintf(toSendString, "%d%d%s",
            dataToSendToRaspberry.id,
            dataToSendToRaspberry.key,
            temperatureString);
//Serial.print("       ");
Serial.print("To send string: ");Serial.print(toSendString);
    int checksum = calculateChecksum(toSendString);
    int digits = howManyDigits(checksum);
//Serial.print("        6");
    if (digits > 8){
        checksum = checksum % 100000000;
        digits = 8;
    }
Serial.print("Digits: ");Serial.print(digits);
    char * zeros;
    zeros = (char *) malloc((8 - digits) * sizeof(char));
    for (int i = 0; i < 8 - digits; ++i) {
        zeros[i] = '0';
    }
//    Serial.print("            ddd8ddd");
    sprintf(toSendString, "%s%s%d", toSendString, zeros, checksum);
//Serial.print("          9     tosendStriniiing     ");Serial.print(toSendString);
//    Serial.print("Sending: ");
//    Serial.print(toSendString);
//Serial.print("10");
//  char text[] = "aaa;sldkjfa;lsdfj";
////    text = (char *)malloc(32);
////    sprintf(text, "%f", sensors.getTempCByIndex(0));
//  radio.write(&text, sizeof(text));
  delay(1000);
 
}
