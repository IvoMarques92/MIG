#ifndef _CLEDMATRIX_H
#define _CLEDMATRIX_H

#include "CQuadrantRelativePattern.h"
#include "CRelativePattern.h"
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

class CLedMatrix: public CQuadrantRelativePattern, public CRelativePattern {
public: 
    static CLedMatrix* getInstance();
    void writeLedMatrix(void);
    void setLedMatrix(vector<vector<char>>);
    void setQuadr(int x, int y);
    int getQuadr();
    vector<vector<char>> getLedMatrix(void);
private: 
    vector<vector<char>> matrix;
    static CLedMatrix* instance;
    CLedMatrix();
    ~CLedMatrix();

    void initSPI();
    void matrixWrite(unsigned char address, unsigned char data);

    void cleanMatrix();

    int fd;
    string device;
};

#endif //_CLEDMATRIX_H
