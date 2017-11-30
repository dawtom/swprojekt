//
// Created by lenovo on 24.11.17.
//

#ifndef CSERIALIZER_MAIN_H
#define CSERIALIZER_MAIN_H

struct DataToSendToRaspberry{

    // 4 characters, statically assigned to each Arduino device in database
    int id;

    // 4 characters, statically inserted into RaspberryPi database
    int key;

    // 8 characters, actual temperature
    float temperature;

    // 8 characters checking if everything has been sent correctly
    long checksum;

};

void setup(struct DataToSendToRaspberry * data);
int howManyDigits (int number);
long  calculateChecksum(char * array);

void printData(struct DataToSendToRaspberry  data){
    Serial.println("*******************************");
    Serial.print("Id: ");Serial.print(data.id);
    Serial.print("\nKey: ");Serial.print(data.key);
    Serial.print("\nTemperature: ");Serial.print(data.temperature);
    Serial.print("\nChecksum: ");Serial.print( data.checksum);
    Serial.print("\n*******************************\n");
}

//char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
//    asm(".global _printf_float");
//
//    char fmt[20];
//    sprintf(fmt, "%%%d.%df", width, prec);
//    sprintf(sout, fmt, val);
//    return sout;
//}
float absval(float f){
    if (f>=0){
        return f;
    } else {
        return (-1) * f;
    }
}

int setTemperatureLength(float f){
    int result = 8;
    if (f < 0.0) {
        result--;
    }
    return result;
}

int setTemperaturePrecision(float f){
    int result = 5;
    if (f >= 100.0){
        result--;
    }
    if (f < 0.0) {
        result--;
    }
    if (absval(f) < 10.0){
        result++;
    }
    return result;
}

long calculateChecksum(char array[16]){
    //array contains 16 characters, other are ignored
    long result = 0;
//
//    Serial.print("\nIN CHECKSUM");
//    Serial.print(array);
//    Serial.print("\n");
    for (int i = 0; i < 4; ++i) {
//        Serial.print("Partial result\n");
//
//        Serial.print( (long) ((array[4*i+0]  * (4 * i + 1)) + (array[4*i+1] * (4 * i + 2))) * ((array[4*i+2] * (4 * i + 3)) + (array[4*i+3] * (4 * i + 4))));
//        Serial.print("\n");

      
        
        result = result +  ((long)((array[4 * i + 0] * (4 * i + 1) ) +
                        (array[4 * i + 1] * (4 * i + 2) )) * (
                            (array[4 * i + 2] * (4 * i + 3) ) +
                                     (array[4 * i + 3] * (4 * i + 4) )));
//        Serial.print("\nResult after");Serial.print(4*(i+1));Serial.print("\n");Serial.print(result);Serial.print("\n");
    }

    //printf("%d\n", result);
    return result;
}

int howManyDigits (long number){
    int result = 0;
    while (number > 0){
        number = number / 10;
        result++;
    }
    return result;
}
#endif //CSERIALIZER_MAIN_H
