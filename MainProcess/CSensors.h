/**
 * Project Untitled
 */


#ifndef _CSENSORS_H
#define _CSENSORS_H

class CSensors {
public: 
    
    void CSensors();
    
    void initSensors();
    
    int readCHandSlideSensor();
    
    uint16_t readCDistanceSensor();
    
    int readCTouchMatrix();
    
    void closeSensors();
    
    CSensors static getInstance();
private: 
    struct dataSensors;
    CActuators static instance;
};

#endif //_CSENSORS_H