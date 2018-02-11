#include "CSensors.h"
#include "CTouchMatrix.h"
#include "CDistanceSensor.h"
#include "CHandSlideSensor.h"

#include <iostream>

using namespace std;

CSensors::CSensors()
{
    buffer = new char [4];
}

CSensors::~CSensors()
{
    delete buffer;
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
* Return		 : char * buffer -> buffer with data from slide sensors
*******************************************************************************/
char * CSensors::readHandSlideSensor() {

    CHandSlideSensor *caps = CHandSlideSensor::getInstance();

    if(caps->openHandSlideSensor() < 0)
        perror("Error Open Capacitive Sensors");

    buffer = caps->readHandSlideSensor();

    caps->closeHandSlideSensor();

    return buffer;
}

/*******************************************************************************
* Function Name  : readDistanceSensor
* Description    : Read the Distance Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : float -> speed
*******************************************************************************/
float CSensors::readDistanceSensor() {
    CDistanceSensor *distanceIR = CDistanceSensor::getInstance();
    return distanceIR->getDistanceSensor();
}

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
char * CSensors::readTouchMatrix() {

    CTouchMatrix *touch =  CTouchMatrix::getInstance();

    if(touch->openTouchMatrix() < 0)
        perror("erro open the matrix");

    buffer = touch->readTouchMatrix();

    touch->closeTouchMatrix();

    return buffer;
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
