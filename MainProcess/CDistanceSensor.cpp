#include "CDistanceSensor.h"

CDistanceSensor::CDistanceSensor() {

}

CDistanceSensor::~CDistanceSensor()
{

}

/*******************************************************************************
* Function Name  : initCDistanceSensor
* Description    : Initialize distance sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CDistanceSensor::initCDistanceSensor() {
    return;
}

/*******************************************************************************
* Function Name  : closeCDistanceSensor
* Description    : Close distance sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CDistanceSensor::closeCDistanceSensor() {
    return;
}

/*******************************************************************************
* Function Name  : readCDistanceSensor
* Description    : Read distance sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
uint16_t CDistanceSensor::readCDistanceSensor() {
    return 0;
}

CDistanceSensor* CDistanceSensor::instance = 0;

CDistanceSensor * CDistanceSensor::getInstance()
{
    if (instance == 0)
            instance = new CDistanceSensor;

    return instance;
}

