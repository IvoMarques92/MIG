#include "CDistanceSensor.h"
#include <pthread.h>
#include <semaphore.h>

#include "CSensors.h"

CDistanceSensor::CDistanceSensor() {
    device = "/dev/i2c-1";
    addrI2C = 0x48;
    distance = 0;
    value = 1;
}

CDistanceSensor::~CDistanceSensor()
{

}

/*******************************************************************************
* Function Name  : startReadCDistanceSensor
* Description    : Start the read from the Distance Sensor. To read the value, first
*                   give 1.25ms to make the acquisition, after call the function
*                   readCDistanceSensor().
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CDistanceSensor::startReadCDistanceSensor()
{
    uint8_t writeBuffer[] = {1,                     //config register -> from pag.28 Datasheet ADS1115
                             0b11000011,            //Single Conversion, AIN0, 4.096V, Single Shoot mode
                             0b11100111};           //860SPS, Disable comparator

    if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
        perror("ERROR:Can not open device!");
    }

    if (ioctl(fd, I2C_SLAVE, addrI2C) < 0) {
        perror("ERROR: Can not find the address!");
    }

    if (write(fd, writeBuffer, 3) != 3) {
        perror("ERROR: Can not write on device");
    }
    writeBuffer[0] = 0;
    if (write(fd,writeBuffer, 1) != 1) {
        perror("ERROR: Write register select");
    }

    close(fd);

}

/*******************************************************************************
* Function Name  : readCDistanceSensor
* Description    : Read distance sensor, the function startReadCDistanceSensor()
*                   needs to be called before this function, and between the function
*                   startReadCDistanceSensor() and readCDistanceSensor() needs 1.25ms,
*                   because the ADC needs time to make the acquisition
* Input          : None (void)
* Output         : None (void)
* Return		 : distance (float)
*******************************************************************************/
float CDistanceSensor::readCDistanceSensor() {

    readBuffer[0] = 0;
    readBuffer[1] = 0;

    if ((fd = open("/dev/i2c-1", O_RDONLY)) < 0) {
        perror("ERROR:Can not open device!");
    }

    if (ioctl(fd, I2C_SLAVE, addrI2C) < 0) {
        perror("ERROR: Can not find the address!");
    }

    if (read(fd, readBuffer, 2) != 2) {
        perror("ERROR: Can not read on device");
    }

    close(fd);

    distance =(readBuffer[0]<<8 | readBuffer[1]);

    if(distance < 6000)
        value = 1;
    else if(distance < 7500)
        value = 1.5;
    else if(distance < 9500)
        value = 2;
    else if(distance < 11000)
        value = 2.5;
    else if(distance < 13000)
        value = 3;
    else if(distance < 16000)
        value = 3.5;
    else
        value = 4;

    return value;
}

CDistanceSensor* CDistanceSensor::instance = 0;

/*******************************************************************************
* Function Name  : getDistanceCDistanceSensor()
* Description    : Read distance sensor, this function already make the delay
*                   between the function startReadCDistanceSensor() and the function
*                   readCDistanceSensor().
* Input          : None (void)
* Output         : None (void)
* Return		 : distance (float)
*******************************************************************************/
float CDistanceSensor::getDistanceSensor()
{
    float aux;
    startReadCDistanceSensor();
    //1.25ms delay to make the conversion and send from adc to uC
    usleep(1250);
    aux = readCDistanceSensor();
    return aux;
}

/*******************************************************************************
* Function Name  : tIRSensorFunction
* Description    : Function Associated to the Thread tIRSensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None (void)
*******************************************************************************/
void *CDistanceSensor::tIRSensorFunction(void *ptr)
{
    CSensors *sensors = CSensors::getInstance();
    float oldSpeed = 0, speed = 0;
    extern sem_t sTimerIRSensor, sUpdateSound;
    extern pthread_mutex_t mIRDataAnalysis;

    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerIRSensor);

        pthread_mutex_lock(&mIRDataAnalysis);

        speed = sensors->readDistanceSensor();
        sensors->setSpeed(speed);

        if(oldSpeed != speed) // new data
             sem_post(&sUpdateSound);


        pthread_mutex_unlock(&mIRDataAnalysis);

        oldSpeed = speed;
    }
}

CDistanceSensor * CDistanceSensor::getInstance()
{
    if (instance == 0)
            instance = new CDistanceSensor;

    return instance;
}


