#include "CSensors.h"
#include "CLedMatrix.h"
#include "CHandSlideSensor.h"
#include <pthread.h>
#include <semaphore.h>

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
    capFile.open("/dev/MIGCapSensors", ios_base::in | ios_base::out);
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

/*******************************************************************************
* Function Name  : tSlideSensorFunction
* Description    : Function Associated to the Thread tSlideSensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None (void)
*******************************************************************************/
void *CHandSlideSensor::tSlideSensorFunction(void *ptr)
{
    CSensors *sensors = CSensors::getInstance();
    extern sem_t sTimerSlideSensor;

    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerSlideSensor);

        processingDataSlide(sensors->readHandSlideSensor());


    }
}

/*******************************************************************************
* Function Name  : processingDataSlide
* Description    : Processing the data of slide sensors.
* Input          : None (void)
* Output         : None (void)
* Return		 : None (void)
*******************************************************************************/
void CHandSlideSensor::processingDataSlide(char * slideSensors)
{
    static char * buffer = new char[4], cap1 = 0, cap2 = 0, cap3 = 0, cap4 = 0;
    static char old1 = 0, old2 = 0, old3 = 0, old4 = 0;
    static int count = 0;
    static int x = 0, y = 0;

    CLedMatrix *matrix = CLedMatrix::getInstance();

    buffer = slideSensors;

    cap1 = buffer[0];
    cap2 = buffer[1];
    cap3 = buffer[3];
    cap4 = buffer[2];

    if(cap1){ // slide right
        if(old2)
        {
            x = 1;
            matrix->setQuadr(x,y);
        }
        old1 = cap1;
    }
    else if(cap2){ // slide left
        if(old1)
        {
            x = 0;
            matrix->setQuadr(x,y);
        }
        old2 = cap2;
    }

    if(cap3){ // slide top
        if(old4)
        {
            y = 0;
            matrix->setQuadr(x,y);
        }
        old3 = cap3;
    }
    else if(cap4){ // slide low
        if(old3)
        {
            y = 1;
            matrix->setQuadr(x,y);
        }
        old4 = cap4;
    }

    if(count++ > 60) // if in one second the slide don't is complete, slide is ignore
    {
        count = 0;
        old1 = 0;
        old2 = 0;
        old3 = 0;
        old4 = 0;
    }
}

CHandSlideSensor* CHandSlideSensor::instance = 0;

CHandSlideSensor * CHandSlideSensor::getInstance()
{
    if (instance == 0)
            instance = new CHandSlideSensor;

    return instance;
}

