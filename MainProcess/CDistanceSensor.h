#ifndef _CDISTANCESENSOR_H
#define _CDISTANCESENSOR_H

typedef unsigned short int uint16_t;

class CDistanceSensor {
public: 
    
   void initCDistanceSensor();
   void closeCDistanceSensor();
   uint16_t readCDistanceSensor();
   static CDistanceSensor* getInstance();

private: 
    static CDistanceSensor* instance;
    CDistanceSensor();
    ~CDistanceSensor();

};

#endif //_CDISTANCESENSOR_H
