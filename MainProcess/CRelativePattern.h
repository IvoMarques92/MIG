#ifndef _CRELATIVEPATTERN_H
#define _CRELATIVEPATTERN_H

#include <vector>
#include <stdint.h>
#include <unistd.h>			//write()
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>			//O_RDWR
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string>

using namespace std;

class CRelativePattern {
public: 
    CRelativePattern();
    ~CRelativePattern();

protected: 
    void writeRelativePattern();
    void setRelativePattern(vector<vector<char> >);
    vector<vector<char>> relativeMatrix;

private: 

    void cleanMatrix();
    void matrixWrite(unsigned char address, unsigned char data);
    void initSPI();

    int fd;
    string device;
};

#endif //_CRELATIVEPATTERN_H
