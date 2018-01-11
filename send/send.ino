#include <EEPROM.h>



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

int addr = 0;

int bytesIdToIntId(char arr[4]);


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

int toConfigureId;
int toConfigurePipe;
int incomingByte = 97;
int i = 0;
int   pipeLenCounter = 5;
char idBytes[4];
char pipeBytes[5];
char devnull[100];
char value;

void setup(void){
  
  //dataToSendToRaspberry = (struct DataToSendToRaspberry *)malloc(sizeof(struct DataToSendToRaspberry));

  dataToSendToRaspberry = {1120,9000,0.0,0};
  
  // radio initialization
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x76);
  radio.setDataRate(RF24_1MBPS);
  radio.setRetries(2,5);
  
  
  radio.enableDynamicPayloads();
  radio.powerUp();
  //  radio.startListening();
  

  // temperature sensor initialization
  sensors.begin(); 
  pinMode(2, INPUT_PULLUP);

//  EEPROM.write(addr,66);

  Serial.begin(9600);

  char value;
  for (int a = 0; a < 15; a++){
      value = EEPROM.read(a);
      Serial.println(value);
    }
  //value = EEPROM.read(addr);
  //Serial.print("Value after: ");Serial.print(value);Serial.print("\n");

  byte hasBeenConfigured = EEPROM.read(0);
  if (hasBeenConfigured != 49){
    toConfigureId = 1;
    toConfigurePipe = 1;
    Serial.print("Needs configuration");
  } else{
    Serial.print("No need for configuration");
    toConfigureId = 0;
    toConfigurePipe = 0;
    for (int i = 1; i <=4; i++){
      idBytes[i-1] = EEPROM.read(i);
    }
    for (int i = 0; i < 5; i++){
      pipeBytes[i] = EEPROM.read(i + 5);
    }
  }
 
}

//void loopFunction();
int bytesIdToIntId(char arr[4]){
  int intBytes[4];
  for (int i = 0; i < 4; i++){
    intBytes[i] = arr[i] - 48;
  }
  int result = 0;
  int power = 1;
  for (int i = 0; i < 4; i++){
    result += power * intBytes[4 - i - 1];
    power *= 10;
  }
  return result;
}


void loop(void){

  if (toConfigureId == 1){
    if (Serial.available() > 0){
      Serial.readBytes(idBytes,4); 
      Serial.print("Id: ");
        for (int x = 0; x < 4; x++){
          EEPROM.write(x+1,idBytes[x]);
          Serial.print(idBytes[x],DEC);
        }
        Serial.readBytes(devnull,1000); 
      toConfigureId = 0;
    }
  } else{
    if (toConfigurePipe == 1){
      if (Serial.available() > 0){
        Serial.readBytes(pipeBytes,pipeLenCounter);
      Serial.print("Pipe: ");
        for (int x = 0; x < pipeLenCounter; x++){
          EEPROM.write(x+5,pipeBytes[x]);
          Serial.print(pipeBytes[x],DEC);Serial.print(" ");
        }
        Serial.readBytes(devnull,1000); 
      toConfigurePipe = 0;
      }
    } else{
      uint64_t idBytesLong = (uint64_t) idBytes;
      //Serial.print(idBytesLong);
      Serial.print("Configuration completed");
      EEPROM.write(0,49);

      int id = bytesIdToIntId(idBytes);
      dataToSendToRaspberry.id = id;

      Serial.print("Device id is: ");Serial.println(id);
      
      loopFunction();
    }
    
  }
}
 
void loopFunction(void){
  radio.openReadingPipe(0,0xE8E8F0F0E1LL);
  radio.startListening();
  //int messageRead = 0;
  Serial.print("Before start listening");
  
  if (!radio.available()){
    Serial.print("RADIO NOT AVAILABLE");
  }
  Serial.print("Will be waiting on radio not available\n");
  while (!radio.available());
  Serial.print("Radio is now available. Will be reading\n");

  uint8_t len = radio.getDynamicPayloadSize();
    char text[32] = "";
    radio.read( text, len);
    radio.stopListening();
    delay(100);
    Serial.print("Received message");
    
    //radio.read(&text, sizeof(text));
    
    //messageRead = 1;
  

  
  Serial.println(text);
    //delay(dataToSendToRaspberry.id - 1000);
      
    sensors.requestTemperatures();
//Serial.print("test\n");
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
//Serial.print("To send string: ");Serial.print(toSendString);
    long checksum;
    checksum = calculateChecksum(toSendString);
    int digits = howManyDigits(checksum);
    char tmp [60];sprintf(tmp,"Checksum %ld with %d digits.\n",checksum, digits); Serial.print(tmp);
    if (digits > 8){
        checksum = checksum % 100000000;
        digits = 8;
    }

    dataToSendToRaspberry.checksum = checksum;
    
//Serial.print("Digits: ");Serial.print(digits);
    for (int i = 0; i < 8 - digits; ++i) {
        sprintf(toSendString, "%s%c", toSendString, '0');
    }
    sprintf(toSendString, "%s%ld", toSendString, checksum);
    Serial.println("Sending: ");printData(dataToSendToRaspberry);Serial.println(" in string: ");Serial.println(toSendString);


  //delay(1000);
  radio.openWritingPipe(0xF0F0F0F0E1);
    radio.write(&toSendString, sizeof(toSendString));
   
}
