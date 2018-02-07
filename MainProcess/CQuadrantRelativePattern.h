#ifndef _CQUADRANTRELATIVEPATTERN_H
#define _CQUADRANTRELATIVEPATTERN_H

#include <string>              //C++ String Management//
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>             //C++ I/O Terminal//

#include <sys/mount.h>          //mount() and umount() Functions//
#include <unistd.h>             //System Calls//
#include <mqueue.h>             //Message Queues APIs//


using namespace std;

class CQuadrantRelativePattern {
public: 

    CQuadrantRelativePattern();
    ~CQuadrantRelativePattern();
    int getQuadrant();

protected: 
    void writeQuadrant();
    void setQuadrant(int x, int y);

private: 
    int layer;

    int fd;
    string device;
};

#endif //_CQUADRANTRELATIVEPATTERN_H
