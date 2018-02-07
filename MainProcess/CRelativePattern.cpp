#include "CRelativePattern.h"
CRelativePattern::CRelativePattern()
{
    relativeMatrix.resize(4);
    for ( int i = 0 ; i < 4 ; i++ )
        relativeMatrix[i].resize(4);

    device = "/dev/spidev0.1";

    fd = open(device.c_str(), O_RDWR);
    if(fd < 0)
        printf("ERROR: Can not open the device0.1");

    initSPI();

    // Start Max7221 with LedMatrix
    matrixWrite(0x0C, 0x01); // Normal operation
    matrixWrite(0x0B, 0x07); // Scan Limit (all digits)
    matrixWrite(0x0A, 0x07); // Intensity
    matrixWrite(0x09, 0x00); // Decode mode (off)

    cleanMatrix();

    close(fd);
}

CRelativePattern::~CRelativePattern()
{
    /*deallocate the matrix */
    for ( int i = 0 ; i < 4 ; i++ )
        vector<char>().swap(relativeMatrix[i]);
    vector<vector<char>>().swap(relativeMatrix);
}

/*******************************************************************************
* Function Name  : writeRelativePattern
* Description    : Write Relative Pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CRelativePattern::writeRelativePattern() {
    uint8_t data;

    //Refresh AbsolutePattern

    fd = open(device.c_str(), O_RDWR);
    if(fd < 0)
        printf("ERROR: Can not open the device0.0");

    cleanMatrix();

    for(int col = 1; col <= 4; col++)
    {
        data=0x00;
        for(int lin = 0; lin <= 3; lin++)
            data = data | ((relativeMatrix[col-1][lin]&0x01) << lin);
        matrixWrite(col, data);
    }
    close(fd);

    return;
}

/*******************************************************************************
* Function Name  : setRelativePattern
* Description    : set the Relative Pattern
* Input          : vector<vector<int>> matrix
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CRelativePattern::setRelativePattern(vector<vector<char>> newMatrix) {
    relativeMatrix = newMatrix;
    return;
}


/*******************************************************************************
* Function Name  : initSPI
* Description    : Make the SPI initialization with the mode, bits per word and speed
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CRelativePattern::initSPI()
{
    static uint8_t mode;
    static uint8_t bits = 8;
    static uint32_t speed = 200000;	//Hz
    int aux = 0;

    //SPI mode
    aux = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (aux == -1)
        {printf("ERROR:can not define spi mode");}
    aux = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (aux == -1)
        {printf("ERROR:can not read spi mode");}
    //SPI - bit number
    aux = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (aux == -1)
        {printf("ERROR:can not define number of bits");}
    aux = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (aux == -1)
        {printf("ERROR:can not read number of bits");}
    //SPI - speed
    aux = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (aux == -1)
        {printf("ERROR:can not define speed");}
    aux = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (aux == -1)
        {printf("ERROR:can not read speed");}
    return;
}

/*******************************************************************************
* Function Name  : matrixWrite
* Description    : Write on Max7221 using SPI, don't forget open the device and close
* Input          : address (unsigned char) , data (unsigned char)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CRelativePattern::matrixWrite(unsigned char address, unsigned char data)
{
    uint8_t tx[] = {address, data, };
    write(fd, tx, 2);
    return;
}

/*******************************************************************************
* Function Name  : cleanMatrix
* Description    : turn off all leds on matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CRelativePattern::cleanMatrix()
{
    for (int col = 1; col <= 8; col++)
        {
            matrixWrite(col, 0x00);
        }
    return;
}
