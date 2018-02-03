/**
 * Project Untitled
 */


#ifndef _CHANDSLIDESENSOR_H
#define _CHANDSLIDESENSOR_H

class CHandSlideSensor {
public: 
    
    void initCHandSlideSensor();
    
    void closeCHandSlideSensor();
    
    int readCHandSlideSensor();
    
    CHandSlideSensor static getInstance();
private: 
    CHandSlideSensor static instance;
    
    void CHandSlideSensor();
};

#endif //_CHANDSLIDESENSOR_H