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
    int checksum;

};

void setup(struct DataToSendToRaspberry * data);
int howManyDigits (int number);
int calculateChecksum(char * array);

void printData(struct DataToSendToRaspberry * data){
    printf("*******************************\n");
    printf("Id: %d\n", data->id);
    printf("Key: %d\n", data->key);
    printf("Temperature: %f\n", data->temperature);
    printf("Checksum: %d\n", data->checksum);
    printf("*******************************\n");
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

int calculateChecksum(char * array){
    //array contains 16 characters, other are ignored
    int result = 0;

    for (int i = 0; i < 4; ++i) {
        result += (((array[4 * i + 0] * (4 * i + 1) ) +
                        (array[4 * i + 1] * (4 * i + 2) )) * (
                            (array[4 * i + 2] * (4 * i + 3) ) +
                                     (array[4 * i + 3] * (4 * i + 4) )));
    }

    //printf("%d\n", result);
    return result;
}

int howManyDigits (int number){
    int result = 0;
    while (number > 0){
        number = number / 10;
        result++;
    }
    return result;
}
#endif //CSERIALIZER_MAIN_H
