#include "CTouchMatrix.h"

CTouchMatrix::CTouchMatrix()
{
    buffer = new char [4];
}

CTouchMatrix::~CTouchMatrix()
{
    delete buffer;
}

/*******************************************************************************
* Function Name  : initTouchMatrix
* Description    : Initialize the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CTouchMatrix::openTouchMatrix() {
    touchIn.open("/dev/MIGTouchIN", ios_base::in | ios_base::out);
    touchOut.open("/dev/MIGTouchOUT",ios_base::in | ios_base::out);
    if(!touchIn.is_open())
    {
        perror("Error open the device driver with file /dev/touchIN ! ");
     return -1;
    }
    if(!touchOut.is_open())
    {
        perror("Error open the device driver with file /dev/touchIN ! ");
     return -1;
    }
    return 0;
}

/*******************************************************************************
* Function Name  : closeTouchMatrix
* Description    : Close the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CTouchMatrix::closeTouchMatrix() {
    touchIn.close();
    touchOut.close();
    return;
}

#include <stdio.h>
#include <iostream>

using namespace std;

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : Read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : char * :vector of 4 positions each position represent one
*                : column of the touch Matrix
*******************************************************************************/
char * CTouchMatrix::readTouchMatrix() {

    static char count = 0;
    static string line = "0";

    touchOut.write(line.c_str(), 1);
    line = to_string((count++) & 0x03);

    touchIn.read(buffer, 4);

    for(int i = 0; i < 4; i++)
        buffer[i] ^= 0x01;

    return buffer;
}


CTouchMatrix* CTouchMatrix::instance = 0;

CTouchMatrix * CTouchMatrix::getInstance()
{
    if (instance == 0)
            instance = new CTouchMatrix;

    return instance;
}

