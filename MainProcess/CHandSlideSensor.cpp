#include "CHandSlideSensor.h"

CHandSlideSensor::CHandSlideSensor() {

}

CHandSlideSensor::~CHandSlideSensor()
{

}

/*******************************************************************************
* Function Name  : initCHandSlideSensor
* Description    : Initialize Hand Slide Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CHandSlideSensor::initCHandSlideSensor() {
    return;
}

/*******************************************************************************
* Function Name  : closeCHandSlideSensor
* Description    : Close Hand Slide Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CHandSlideSensor::closeCHandSlideSensor() {
    return;
}

/*******************************************************************************
* Function Name  : readCHandSlideSensor
* Description    : Read Hand Slide Sensor
* Input          : None (void)
* Output         : int
* Return		 : None
*******************************************************************************/
int CHandSlideSensor::readCHandSlideSensor() {
    return 0;
}

CHandSlideSensor* CHandSlideSensor::instance = 0;

CHandSlideSensor * CHandSlideSensor::getInstance()
{
    if (instance == 0)
            instance = new CHandSlideSensor;

    return instance;
}

