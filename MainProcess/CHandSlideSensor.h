#ifndef _CHANDSLIDESENSOR_H
#define _CHANDSLIDESENSOR_H

#include <fstream>

using namespace std;

class CHandSlideSensor {
public: 
    static CHandSlideSensor*  getInstance();
    int openHandSlideSensor();
    void closeHandSlideSensor();
    char * readHandSlideSensor();

private: 
    static CHandSlideSensor* instance;
    CHandSlideSensor();
    ~CHandSlideSensor();
    fstream capFile;
    char * buffer;
};

#endif //_CHANDSLIDESENSOR_H
