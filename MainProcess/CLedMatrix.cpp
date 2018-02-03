#include "CLedMatrix.h"

CLedMatrix::CLedMatrix() {

}

CLedMatrix::~CLedMatrix()
{

}

/*******************************************************************************
* Function Name  : writeLedMatrix
* Description    : write the Led Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CLedMatrix::writeLedMatrix(void) {
    return;
}

/*******************************************************************************
* Function Name  : setLedMatrix
* Description    : set the Led Matrix
* Input          : vector<vector<int>> matrix
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CLedMatrix::setLedMatrix(vector<vector<int>> matrix) {
    return;
}

/*******************************************************************************
* Function Name  : getLedMatrix
* Description    : Get the Led Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : vector<vector<int>>
*******************************************************************************/
vector<vector<int>> CLedMatrix::getLedMatrix(void) {
    vector<vector<int>> a;
    return a;
}

CLedMatrix* CLedMatrix::instance = 0;

CLedMatrix * CLedMatrix::getInstance()
{
    if (instance == 0)
            instance = new CLedMatrix;

    return instance;
}
