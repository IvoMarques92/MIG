#ifndef _CSENSORS_H
#define _CSENSORS_H

typedef unsigned short int uint16_t;

class CSensors {
public: 
    
    static CSensors* getInstance();
    void initSensors();
    char * readHandSlideSensor();
    float readDistanceSensor();
    int readTouchMatrix();
    void closeSensors();
    void setSpeed(float speed1){speed = speed1;}
    float getSpeed(){return speed;}
private: 
    float speed;
    char * buffer;
    CSensors();
    ~CSensors();
    static CSensors* instance;
};

#endif //_CSENSORS_H
