#ifndef _CDISTANCESENSOR_H
#define _CDISTANCESENSOR_H

#include <string>              //C++ String Management//
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>      //I2C bus Definitions//
#include <iostream>             //C++ I/O Terminal//

#include <sys/mount.h>          //mount() and umount() Functions//
#include <unistd.h>             //System Calls//
#include <mqueue.h>             //Message Queues APIs//

using namespace std;

typedef unsigned short int uint16_t;

class CDistanceSensor {
public: 
   float getDistanceSensor();
   static CDistanceSensor* getInstance();
   static void *tIRSensorFunction( void *ptr );

private:
    static CDistanceSensor* instance;
    CDistanceSensor();
    ~CDistanceSensor();

    void startReadCDistanceSensor();
    float readCDistanceSensor();

    uint8_t readBuffer[2];
    int fd;
    string device;
    int addrI2C;
    unsigned short int distance;
    float value;


};

#endif //_CDISTANCESENSOR_H
