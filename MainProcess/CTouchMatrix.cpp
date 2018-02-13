#include <pthread.h>
#include <semaphore.h>
#include "CSensors.h"
#include "CLedMatrix.h"
#include "CTouchMatrix.h"
#include "CAbsolutePattern.h"


CTouchMatrix::CTouchMatrix()
{
    buffer = new char [4];
}

CTouchMatrix::~CTouchMatrix()
{
    delete buffer;
}

/*******************************************************************************
* Function Name  : initTouchMatrix
* Description    : Initialize the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CTouchMatrix::openTouchMatrix() {
    touchIn.open("/dev/MIGTouchIN", ios_base::in | ios_base::out);
    touchOut.open("/dev/MIGTouchOUT",ios_base::in | ios_base::out);
    if(!touchIn.is_open())
    {
        perror("Error open the device driver with file /dev/touchIN ! ");
     return -1;
    }
    if(!touchOut.is_open())
    {
        perror("Error open the device driver with file /dev/touchIN ! ");
     return -1;
    }
    return 0;
}

/*******************************************************************************
* Function Name  : closeTouchMatrix
* Description    : Close the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CTouchMatrix::closeTouchMatrix() {
    touchIn.close();
    touchOut.close();
    return;
}

/*******************************************************************************
* Function Name  : readTouchMatrix
* Description    : Read the Touch Matrix
* Input          : None (void)
* Output         : None (void)
* Return		 : char * :vector of 4 positions each position represent one
*                : column of the touch Matrix
*******************************************************************************/
char * CTouchMatrix::readTouchMatrix() {

    static char count = 0;
    static string line = "0";

    touchOut.write(line.c_str(), 1);
    line = to_string((count++) & 0x03);

    touchIn.read(buffer, 4);

    for(int i = 0; i < 4; i++)
        buffer[i] ^= 0x01;

    return buffer;
}

/*******************************************************************************
* Function Name  : tTouchInFunction
* Description    : Function Associated to the Thread tTouchIn
* Input          : None (void)
* Output         : None (void)
* Return		 : None (void)
*******************************************************************************/
void *CTouchMatrix::tTouchInFunction(void *ptr)
{
    char * buffer = new char [4];
    char count = 0, matrix[4][4];
    int xQuadr, yQuadr;
    extern pthread_mutex_t mAbsolutePattern;
    extern sem_t sTimerTouchIn, sUpdateSound;

    vector<vector<char>> absolutePattern, auxMatrix, oldMatrix;

    CSensors *sensors = CSensors::getInstance();
    CLedMatrix *ledMatrix = CLedMatrix::getInstance();
    CAbsolutePattern *absolute = CAbsolutePattern::getInstance();

    absolutePattern.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        absolutePattern[i].resize(8);

    auxMatrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        auxMatrix[i].resize(8);

    oldMatrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        oldMatrix[i].resize(8);

    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerTouchIn);

        buffer = sensors->readTouchMatrix();

        for(int i = 0; i < 4; i++){
            matrix[count][i] = buffer[i];
        }
        count++;
        if(count == 4)
        {
            count = 0;
            //Get Quadrant
            xQuadr = ledMatrix->getQuadr() & 0x01;
            yQuadr = ((ledMatrix->getQuadr() >> 1) & 0x01);

            pthread_mutex_lock(&mAbsolutePattern);

            absolutePattern = absolute->getAbsolutePattern();

            pthread_mutex_unlock(&mAbsolutePattern);

            //Set RelativePattern based on Quadrant
            for(int lin=0; lin < 4; lin++)
            {
                for(int col=0; col < 4; col++)
                {
                    auxMatrix[lin + yQuadr*4 ][col + xQuadr*4] = matrix[lin][col];
                }
            }

            //verifie if the new matrix is different, if is different change the matrix
            for(int col=0; col < 4; col++)
            {
                for(int lin=0; lin < 4; lin++)
                {
                    if(auxMatrix[lin + yQuadr*4][col + xQuadr*4] != oldMatrix[lin + yQuadr*4][col + xQuadr*4]) // new data on the matrix if the condition is true
                    {
                        lin = 4; //leave the for
                        col = 4; //leave the for

                        for(int i = 0; i < 4; i++)
                            for(int j = 0; j < 4; j++)
                            {absolutePattern[i + yQuadr*4][j + xQuadr*4] = absolutePattern[i + yQuadr*4][j + xQuadr*4] ^ auxMatrix[i + yQuadr*4][j + xQuadr*4];}

                        pthread_mutex_lock(&mAbsolutePattern);

                        absolute->setAbsolutePattern(absolutePattern);
                        ledMatrix->setLedMatrix(absolutePattern);
                        ledMatrix->writeLedMatrix();

                        pthread_mutex_unlock(&mAbsolutePattern);

                        //semaphore to tsoundgenerat
                        sem_post(&sUpdateSound);
                    }
                }

            }
            oldMatrix = auxMatrix;

         }

    }
}


CTouchMatrix* CTouchMatrix::instance = 0;

CTouchMatrix * CTouchMatrix::getInstance()
{
    if (instance == 0)
            instance = new CTouchMatrix;

    return instance;
}

