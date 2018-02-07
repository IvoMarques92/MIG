#include "CDistanceSensor.h"

CDistanceSensor::CDistanceSensor() {
    device = "/dev/i2c-1";
    addrI2C = 0x48;
    distance = 0;
    voltsPerBit = 3.3 / 32768.0;
}

CDistanceSensor::~CDistanceSensor()
{

}
void CDistanceSensor::startReadCDistanceSensor()
{
    uint8_t writeBuffer[] = {1,                     //config register -> from pag.28 Datasheet ADS1115
                             0b11000011,            //Single Conversion, AIN0, 4.096V, Single Shoot mode
                             0b11100111};           //860SPS, Disable comparator

    if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
        printf("ERROR:Can not open device!");
    }

    if (ioctl(fd, I2C_SLAVE, addrI2C) < 0) {
        printf("ERROR: Can not find the address!");
    }

    if (write(fd, writeBuffer, 3) != 3) {
        printf("ERROR: Can not write on device");
    }
    writeBuffer[0] = 0;
    if (write(fd,writeBuffer, 1) != 1) {
        perror("Write register select");
        exit(-1);
    }

    close(fd);

}

/*******************************************************************************
* Function Name  : readCDistanceSensor
* Description    : Read distance sensor
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
float CDistanceSensor::readCDistanceSensor() {
    readBuffer[0] = 0;
    readBuffer[1] = 0;

    if ((fd = open("/dev/i2c-1", O_RDONLY)) < 0) {
        printf("ERROR:Can not open device!");
    }

    if (ioctl(fd, I2C_SLAVE, addrI2C) < 0) {
        printf("ERROR: Can not find the address!");
    }

    if (read(fd, readBuffer, 2) != 2) {
        printf("ERROR: Can not read on device");
    }

    close(fd);

    distance = voltsPerBit * (readBuffer[0]<<8 | readBuffer[1]);

    return distance;
}

CDistanceSensor* CDistanceSensor::instance = 0;

CDistanceSensor * CDistanceSensor::getInstance()
{
    if (instance == 0)
            instance = new CDistanceSensor;

    return instance;
}

