#ifndef _CSENSORS_H
#define _CSENSORS_H

typedef unsigned short int uint16_t;

class CSensors {
public: 
    
    static CSensors* getInstance();
    void initSensors();
    int readHandSlideSensor();
    uint16_t readDistanceSensor();
    int readTouchMatrix();
    void closeSensors();
        
private: 
    struct dataSensors{
        int i;
    };
    CSensors();
    ~CSensors();
    static CSensors* instance;
};

#endif //_CSENSORS_H
