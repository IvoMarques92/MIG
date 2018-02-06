#include "CActuators.h"

#include <iostream>

using namespace std;

CActuators::CActuators() {
cout << "constr CActuators" << endl;
}

CActuators::~CActuators()
{

}

/*******************************************************************************
* Function Name  : initActuators
* Description    : Initialize Actuators
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CActuators::initActuators() {
    return;
}

/*******************************************************************************
* Function Name  : closeActuators
* Description    : Close Actuators
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CActuators::closeActuators() {
    return;
}

/*******************************************************************************
* Function Name  : setLedMatrix
* Description    : Set LedMatrix
* Input          : vector<vector<int>> matrix
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CActuators::setLedMatrix(vector<vector<int>> matrix) {
    return;
}

/*******************************************************************************
* Function Name  : getDataLedMatrix
* Description    : Get data of LedMatrix
* Input          : None (void)
* Output         : None (void)
* Return		 : int
*******************************************************************************/
int CActuators::getDataLedMatrix() {
    return 0;
}

/*******************************************************************************
* Function Name  : wrtieSpeaker
* Description    : wrtie wave in the Speaker
* Input          : void* microData
* Output         : None (void)
* Return		 : int
*******************************************************************************/
int CActuators::wrtieSpeaker(void* microData) {
    return 0;
}


CActuators* CActuators::instance = 0;

CActuators * CActuators::getInstance()
{
    if (instance == 0)
            instance = new CActuators;

    return instance;
}

