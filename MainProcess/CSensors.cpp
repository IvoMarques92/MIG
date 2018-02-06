#include "CSensors.h"

#include <iostream>

using namespace std;

CSensors::CSensors() {
cout << "constr CSensors" << endl;
}

CSensors::~CSensors()
{

}

/*******************************************************************************
* Function Name  : initSensors
* Description    : Initialize Sensors
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSensors::initSensors() {
    return;
}

/*******************************************************************************
* Function Name  : readHandSlideSensor
* Description    : Read all the Hand Slide Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CSensors::readHandSlideSensor() {
    return 0;
}

/*******************************************************************************
* Function Name  : readDistanceSensor
* Description    : Read the Distance Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
uint16_t CSensors::readDistanceSensor() {
    return 0;
}

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CSensors::readTouchMatrix() {
    return 0;
}

/*******************************************************************************
* Function Name  : closeSensors
* Description    : close all the Sensors
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSensors::closeSensors() {
    return;
}


CSensors* CSensors::instance = 0;

CSensors * CSensors::getInstance()
{
    if (instance == 0)
            instance = new CSensors;

    return instance;
}
