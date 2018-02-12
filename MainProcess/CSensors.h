#ifndef _CSENSORS_H
#define _CSENSORS_H

typedef unsigned short int uint16_t;

class CSensors {
public: 
    
    static CSensors* getInstance();
    void initSensors();
    char * readHandSlideSensor();
    char *readTouchMatrix();
    float readDistanceSensor();
    float getSpeed(){return speed;}
    void setSpeed(float speed1){speed = speed1;}
    void closeSensors();

private:
    float speed;
    char * buffer;
    CSensors();
    ~CSensors();
    static CSensors* instance;
};

#endif //_CSENSORS_H
