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

   void startReadCDistanceSensor();
   float readCDistanceSensor();
   static CDistanceSensor* getInstance();

private:
    static CDistanceSensor* instance;
    CDistanceSensor();
    ~CDistanceSensor();

    float voltsPerBit;

    uint8_t readBuffer[2];
    int fd;
    string device;
    int addrI2C;
    float distance;


};

#endif //_CDISTANCESENSOR_H
