/* 
 * File:   dht11.c
 * Author: Dmitry M. Litvinov
 *
 * Created on April 4, 2016, 10:47 PM
 */

#include <wiringPi.h>
#include "dht11.h"

/* 
 * Init DHT11 module
 * params: None
 * return: None
 */
void InitDht(){
    pinMode (DHT_PIN, INPUT);
    pullUpDnControl(DHT_PIN, PUD_UP);
}

/*
 * Read Data from DHT11
 * params:
 *      humidityPtr - pointer for humidity value
 *      temperaturePtr - pointer for temperature value
 * return:
 *      0 - Success / -1 - Error
 */
int ReadDht(float* humidityPtr, float* temperaturePtr){
    unsigned char data[5];
    unsigned int time;
    unsigned int i, j;

    /* Start signal */
    pinMode (DHT_PIN, OUTPUT);
    digitalWrite(DHT_PIN, LOW);
    delay(25);
    pinMode (DHT_PIN, INPUT);

    /* Wait for replay */
    delayMicroseconds(40);
    time = 0;
    while(LOW == digitalRead(DHT_PIN)){
        delayMicroseconds(5);
        if (time++ > 80 / 5) return -1;
    }
    time = 0;
    while(HIGH == digitalRead(DHT_PIN)){
        delayMicroseconds(5);
        if (time++ > 100 / 5) return -2;
    }

    /* Read data */
    for (i = 0; i < sizeof(data); i++){
        data[i] = 0;
        for (j = 0; j < 8; j++){
            /* Wait for bit start */
            time = 0;
            while(LOW == digitalRead(DHT_PIN)){
                delayMicroseconds(5);
                if (time++ > 100 / 5) return -3;
            }
            /* Measure bit length */
            time = 0;
            while(HIGH == digitalRead(DHT_PIN)){
                delayMicroseconds(10);
                if (time++ > 120 / 10) return -4;
            }
            if (time > 50 / 10) data[i] |= 1 << (7 - j);
        }
    }

    /* Check control sum */
    for (i = 0; i < sizeof(data) - 1; i++)
        data[sizeof(data) - 1] -= data[i];
    if (0 != data[sizeof(data) - 1])
        return -5;
    
    *humidityPtr = data[0] + (float)data[1] / 256;
    *temperaturePtr = data[2] + (float)data[3] / 256;
    
    return 0;
}
