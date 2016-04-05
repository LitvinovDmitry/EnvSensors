/* 
 * File:   main.c
 * Author: Dmitry M. Litvinov
 *
 * Created on April 4, 2016, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "dht11.h"

/*
 * 
 */
int main(int argc, char** argv) {
    float humidity;
    float temperature;
    int error;
    int i;
    
    wiringPiSetupPhys ();
    InitDht();
    
    for (i = 0; i < 500; i++){
        if (0 == (error = ReadDht(&humidity, &temperature)))
            printf("Humidity: %.1f     Temperature: %.1f\n", humidity, temperature);
        else
            printf("Error read from DHT11. Error code: %d\n", error);
        delay(300);
    }
    
    return (EXIT_SUCCESS);
}

