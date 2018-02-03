#include "CTouchMatrix.h"

CTouchMatrix::CTouchMatrix() {

}

CTouchMatrix::~CTouchMatrix()
{

}

/*******************************************************************************
* Function Name  : initTouchMatrix
* Description    : Initialize the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CTouchMatrix::initTouchMatrix() {
    return;
}

/*******************************************************************************
* Function Name  : closeTouchMatrix
* Description    : Close the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CTouchMatrix::closeTouchMatrix() {
    return;
}

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : Read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CTouchMatrix::readTouchMatrix() {
    return 0;
}

CTouchMatrix* CTouchMatrix::instance = 0;

CTouchMatrix * CTouchMatrix::getInstance()
{
    if (instance == 0)
            instance = new CTouchMatrix;

    return instance;
}

