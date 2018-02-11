#include "CLedMatrix.h"
#include <iostream>

using namespace std;

CLedMatrix::CLedMatrix()
    :CQuadrantRelativePattern(), CRelativePattern()
{
    matrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        matrix[i].resize(8);

    device = "/dev/spidev0.0";

    fd = open(device.c_str(), O_RDWR);
    if(fd < 0)
        perror("ERROR: Can not open the device0.0");

    initSPI();

    // Start Max7221 with LedMatrix
    matrixWrite(0x0C, 0x01); // Normal operation
    matrixWrite(0x0B, 0x07); // Scan Limit (all digits)
    matrixWrite(0x0A, 0x07); // Intensity
    matrixWrite(0x09, 0x00); // Decode mode (off)

    cleanMatrix();

    close(fd);
}

CLedMatrix::~CLedMatrix() {
    /*deallocate the matrix */
    for ( int i = 0 ; i < 8 ; i++ )
        vector<char>().swap(matrix[i]);
    vector<vector<char>>().swap(matrix);
}

/*******************************************************************************
* Function Name  : writeLedMatrix
* Description    : write the Led Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CLedMatrix::writeLedMatrix(void) {
    uint8_t data;

    //Refresh AbsolutePattern

    fd = open(device.c_str(), O_RDWR);
    if(fd < 0)
        printf("ERROR: Can not open the device0.0");

    cleanMatrix();

    for(int col = 1; col <= 8; col++)
    {
        data=0x00;
        for(int lin = 0; lin <= 7; lin++){
            data = data | ((matrix[col-1][lin]&0x01) << lin);
            cout << (int)data << " ";
        }
        matrixWrite(col, data);
        cout << endl;
    }
    close(fd);

    //Refresh RelativePattern
    this->writeRelativePattern();


    return;
}

/*******************************************************************************
* Function Name  : setLedMatrix
* Description    : set the Led Matrix
* Input          : vector<vector<int>> matrix
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CLedMatrix::setLedMatrix(vector<vector<char> > newMatrix) {
    int xQuadr, yQuadr;

    vector<vector<char>> Aux;

    Aux.resize(8);
    for(int i = 0; i < 8; i++)
            Aux[i].resize(8);

    Aux = newMatrix;

            for(int c = 0; c < 8; c++)
            {
                for(int l = 0; l < 8; l++)
                {matrix[c][7-l] = Aux[c][l];}
            }

    //Get Quadrant
    xQuadr = getQuadrant() & 0x01;
    yQuadr = ((getQuadrant() >> 1) & 0x01);

    //Set RelativePattern based on Quadrant
    for(int col=0; col < 4; col++)
    {
        for(int lin=0; lin < 4; lin++)
        {
            this->relativeMatrix[col][lin] = matrix[lin + yQuadr*4][col + 4 - xQuadr*4];
        }
    }

    return;
}

void CLedMatrix::setQuadr(int x, int y)
{
    setQuadrant(x,y);
    writeQuadrant();

    //Set RelativePattern based on Quadrant
    for(int col=0; col < 4; col++)
    {
        for(int lin=0; lin < 4; lin++)
        {
            this->relativeMatrix[col][lin] = matrix[lin + y*4][col + x*4];
        }
    }
    writeRelativePattern();


    return;
}

int CLedMatrix::getQuadr()
{
    return getQuadrant();
}

/*******************************************************************************
* Function Name  : getLedMatrix
* Description    : Get the Led Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : vector<vector<int>>
*******************************************************************************/
vector<vector<char>> CLedMatrix::getLedMatrix(void) {
    return matrix;
}

CLedMatrix* CLedMatrix::instance = 0;

CLedMatrix * CLedMatrix::getInstance()
{
    if (instance == 0)
            instance = new CLedMatrix;

    return instance;
}

/*******************************************************************************
* Function Name  : initSPI
* Description    : Make the SPI initialization with the mode, bits per word and speed
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CLedMatrix::initSPI()
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
void CLedMatrix::matrixWrite(unsigned char address, unsigned char data)
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
void CLedMatrix::cleanMatrix()
{
    for (int col = 1; col <= 8; col++)
        {
            matrixWrite(col, 0x00);
        }
    return;
}
