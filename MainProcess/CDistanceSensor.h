/**
 * Project Untitled
 */


#ifndef _CDISTANCESENSOR_H
#define _CDISTANCESENSOR_H

class CDistanceSensor {
public: 
    
    void initCDistanceSensor();
    
    void closeCDistanceSensor();
    
    uint16_t readCDistanceSensor();
    
    CDistanceSensor static getInstance();
private: 
    CDistanceSensor static instance;
    
    void CDistanceSensor();
};

#endif //_CDISTANCESENSOR_H