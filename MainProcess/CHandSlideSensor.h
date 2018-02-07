#ifndef _CHANDSLIDESENSOR_H
#define _CHANDSLIDESENSOR_H

class CHandSlideSensor {
public: 
    static CHandSlideSensor*  getInstance();
    void initCHandSlideSensor();
    void closeCHandSlideSensor();
    int readCHandSlideSensor();

private: 
    static CHandSlideSensor* instance;
    CHandSlideSensor();
    ~CHandSlideSensor();
};

#endif //_CHANDSLIDESENSOR_H
