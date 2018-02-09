#include "CHandSlideSensor.h"

CHandSlideSensor::CHandSlideSensor()
{
    buffer = new char [4];
}

CHandSlideSensor::~CHandSlideSensor()
{
    delete buffer;
}

/*******************************************************************************
* Function Name  : initCHandSlideSensor
* Description    : Initialize Hand Slide Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CHandSlideSensor::openHandSlideSensor()
{
    capFile.open("/dev/capSensors", ios_base::in | ios_base::out);
    if(!capFile.is_open())
    {
        perror("Error open the device driver with file /dev/capSensors!");
     return -1;
    }
    return 0;
}

/*******************************************************************************
* Function Name  : closeCHandSlideSensor
* Description    : Close Hand Slide Sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CHandSlideSensor::closeHandSlideSensor() {
    capFile.close();
    return;
}

/*******************************************************************************
* Function Name  : readCHandSlideSensor
* Description    : Read Hand Slide Sensor
* Input          : None (void)
* Output         : int
* Return		 : None
*******************************************************************************/
char * CHandSlideSensor::readHandSlideSensor() {

    capFile.read(buffer, 4);

    return buffer;
}

CHandSlideSensor* CHandSlideSensor::instance = 0;

CHandSlideSensor * CHandSlideSensor::getInstance()
{
    if (instance == 0)
            instance = new CHandSlideSensor;

    return instance;
}

