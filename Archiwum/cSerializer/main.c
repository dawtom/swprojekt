#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "main.h"



int main() {
    struct DataToSendToRaspberry * dataToSendToRaspberry =
            (struct DataToSendToRaspberry *)malloc(sizeof(struct DataToSendToRaspberry));


    setup(dataToSendToRaspberry);
    //printData(dataToSendToRaspberry);

    dataToSendToRaspberry->temperature = 85.187856789;

    int temperatureLength = setTemperatureLength(dataToSendToRaspberry->temperature);
    int temperaturePrecision = setTemperaturePrecision(dataToSendToRaspberry->temperature);

    char temperatureString[8];
    char toSendString[24];

    dtostrf(dataToSendToRaspberry->temperature,temperatureLength,temperaturePrecision,temperatureString);

    sprintf(toSendString, "%d%d%s",
            dataToSendToRaspberry->id,
            dataToSendToRaspberry->key,
            temperatureString);

    int checksum = calculateChecksum(toSendString);
    int digits = howManyDigits(checksum);

    if (digits > 8){
        checksum = checksum % 100000000;
        digits = 8;
    }

    char * zeros;
    zeros = (char *) malloc((8 - digits) * sizeof(char));
    for (int i = 0; i < 8 - digits; ++i) {
        zeros[i] = '0';
    }
    printf("Zeros: %s\n", zeros);

    printf("Before %s\n",toSendString);
    sprintf(toSendString, "%s%s%d", toSendString, zeros, checksum);
    printf("After %s\n",toSendString);
    /*for (int i = 0; i < 24; ++i) {
        printf("\n%c", toSendString[i]);
    }*/

    //printData(dataToSendToRaspberry);

    return 0;
}


void setup(struct DataToSendToRaspberry * data){
    data->id = 5432;
    data->key=9876;
}
