/* 
 * File:   dht11.h
 * Author: Dmitry M. Litvinov
 *
 * Created on April 5, 2016, 12:19 AM
 */

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DHT_PIN 7
    
/* 
 * Init DHT11 module
 * params: None
 * return: None
 */
void InitDht();    

/*
 * Read Data from DHT11
 * params:
 *      humidityPtr - pointer for humidity value
 *      temperaturePtr - pointer for temperature value
 * return:
 *      0 - Success / -1 - Error
 */
int ReadDht(float* humidityPtr, float* temperaturePtr);

#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */

