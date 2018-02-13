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
    // create a function in C because it's need have one physical address (in C++ in the classes we have a virtual address)
    //in order to atribute this function to the respetively thread
    static void *tSlideSensorFunction( void *ptr );

private: 
    static CHandSlideSensor* instance;
    CHandSlideSensor();
    ~CHandSlideSensor();
    // create a function in C to be used by the tSlideSensorFunction
    static void processingDataSlide(char *);
    fstream capFile;
    char * buffer;
};

#endif //_CHANDSLIDESENSOR_H
