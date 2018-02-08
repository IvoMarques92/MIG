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
    capFile.open("/dev/touchIN", ios_base::in | ios_base::out);
    if(!capFile.is_open())
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
    capFile.close();
    return;
}

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : Read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : char * :vector of 4 positions each position represent one
*                : column of the touch Matrix
*******************************************************************************/
char * CTouchMatrix::readTouchMatrix() {

    capFile.read(buffer, 4);

    return buffer;
}

CTouchMatrix* CTouchMatrix::instance = 0;

CTouchMatrix * CTouchMatrix::getInstance()
{
    if (instance == 0)
            instance = new CTouchMatrix;

    return instance;
}

