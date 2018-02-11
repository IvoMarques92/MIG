#include "CMig.h"
#include "CSensors.h"
#include "CLedMatrix.h"
#include "CActuators.h"
#include "CConvertWav.h"
#include "CTouchMatrix.h"
#include "CGenerateSound.h"
//#include "CDistanceSensor.h"
//#include "CHandSlideSensor.h"
#include "CAbsolutePattern.h"

#include <iostream>

using namespace std;

extern pthread_cond_t mcDataAnalysisAbsolutePattern;
extern sem_t sTimerTouchIn, sTimerIRSensor, sTimerSlideSensor;
extern pthread_mutex_t mDataAnalysis4Leds, mDataAnalusisTouchOut, mDataAnalysis2DLedMatrix;
extern pthread_t tTouchIn, tIRSensor, tSlideSensor, tSoundGenerater, tAbsolutePattern, tDataAnalysis;

extern pthread_cond_t conIRDataAnalysis;
extern pthread_cond_t conSlideDataAnalysis;
extern pthread_cond_t conTouchInDataAnalysis;
extern pthread_cond_t conDataAnalysisSoundGenerator;
extern pthread_cond_t conDataAnalysisAbsolutePattern;

extern pthread_mutex_t mIRDataAnalysis;
extern pthread_mutex_t mSlideDataAnalysis;
extern pthread_mutex_t mTouchInDataAnalysis;
extern pthread_mutex_t mDataAnalysisSoundGenerator;
extern pthread_mutex_t mDataAnalysisAbsolutePattern;

CMig::CMig() {

    cout << "constr MIG" << endl;

}

CMig::~CMig()
{

}

/*******************************************************************************
* Function Name  : initMigAtuators
* Description    : Initialize Atuators
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initMigAtuators() {

    CActuators* actuators = CActuators::getInstance();
    actuators->initActuators();

    return;
}

/*******************************************************************************
* Function Name  : initMigSensors
* Description    : Initialize Mig Sensors
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initMigSensors() {

    CSensors* sensors = CSensors::getInstance();
    sensors->initSensors();

    return;
}

/*******************************************************************************
* Function Name  : initSemaphores
* Description    : Initialize Semaphores
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initSemaphores() {

    extern sem_t sTimerTouchIn;
    extern sem_t sTimerIRSensor;
    extern sem_t sTimerSlideSensor;
    //extern sem_t *sSoundGeneratorDaemon;

    sem_init (&sTimerTouchIn, 0, 0); //second 0 -> the semaphore is shared between threads of the process
    sem_init (&sTimerIRSensor, 0, 0); //second 0 -> the semaphore is shared between threads of the process
    sem_init (&sTimerSlideSensor, 0, 0); //second 0 -> the semaphore is shared between threads of the process

    //*sSoundGeneratorDaemon;

    return;
}

/*******************************************************************************
* Function Name  : initMutexs
* Description    : Initialize Mutexs
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initMutexs()
{
    extern pthread_mutex_t mIRDataAnalysis;
    extern pthread_mutex_t mSlideDataAnalysis;
    extern pthread_mutex_t mTouchInDataAnalysis;
    extern pthread_mutex_t mDataAnalysisSoundGenerator;
    extern pthread_mutex_t mDataAnalysisAbsolutePattern;

    mIRDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
    mSlideDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
    mTouchInDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
    mDataAnalysisSoundGenerator = PTHREAD_MUTEX_INITIALIZER;
    mDataAnalysisAbsolutePattern = PTHREAD_MUTEX_INITIALIZER;

}

/*******************************************************************************
* Function Name  : initConditionVariables
* Description    : Initialize Condition Variables
* Input          : None (void)
* Output         : None (void)
* Return		 : None
********************************************************************************/
void CMig::initConditionVariables()
{

    extern pthread_cond_t conIRDataAnalysis;
    extern pthread_cond_t conSlideDataAnalysis;
    extern pthread_cond_t conTouchInDataAnalysis;
    extern pthread_cond_t conDataAnalysisSoundGenerator;
    extern pthread_cond_t conDataAnalysisAbsolutePattern;

    conIRDataAnalysis = PTHREAD_COND_INITIALIZER;
    conSlideDataAnalysis = PTHREAD_COND_INITIALIZER;
    conTouchInDataAnalysis = PTHREAD_COND_INITIALIZER;
    conDataAnalysisSoundGenerator = PTHREAD_COND_INITIALIZER;
    conDataAnalysisAbsolutePattern = PTHREAD_COND_INITIALIZER;
}

/*******************************************************************************
* Function Name  : initSignal
* Description    : Set time for the interrupts.
* Input          : int sign
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initSignal()
{
    struct itimerval itv;

    signal(SIGALRM,ISR);

    // 50ms interrupt
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 50000;//it_interval -> recarga
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 50000; //only for the first timer expires

    setitimer(ITIMER_REAL, &itv, NULL);	//ITIMER_REAL is for a SIGALRM
    return;
}

/*******************************************************************************
* Function Name  : ISR
* Description    : Interrupt of the timer iverload
* Input          : int sign
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::ISR(int sign)
{
    if(sign == SIGALRM)
    {
         /* Post to the semaphore to sample the sensors.*/
         sem_post (&sTimerTouchIn);
         sem_post (&sTimerIRSensor);
         sem_post (&sTimerSlideSensor);

    }
}



void *tTouchInFunction( void *ptr )
{
    char * buffer = new char [4];
    char count = 0, matrix[4][4];
    int xQuadr, yQuadr;

    vector<vector<char>> absolutePattern, auxMatrix;

    CTouchMatrix *touch =  CTouchMatrix::getInstance();
    CLedMatrix *ledMatrix = CLedMatrix::getInstance();
    CAbsolutePattern *absolute = CAbsolutePattern::getInstance();

    absolutePattern.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        absolutePattern[i].resize(8);

    auxMatrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        auxMatrix[i].resize(8);

    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerTouchIn);

        if(touch->openTouchMatrix() < 0)
            perror("erro open the matrix");

        buffer = touch->readTouchMatrix();

        touch->closeTouchMatrix();

        for(int i = 0; i < 4; i++)
            matrix[count][i] = buffer[i];

        count++;

        pthread_mutex_lock(&mTouchInDataAnalysis);

        if(count == 4)
        {
            count = 0;

            //Get Quadrant
            xQuadr = ledMatrix->getQuadr() & 0x01;
            yQuadr = ((ledMatrix->getQuadr() >> 1) & 0x01);

            absolutePattern = absolute->getAbsolutePattern();
            auxMatrix = absolutePattern;

            //Set RelativePattern based on Quadrant
            for(int col=0; col < 4; col++)
            {
                for(int lin=0; lin < 4; lin++)
                {
                    absolutePattern[col + xQuadr*4][lin + yQuadr*4] = matrix[col][lin];
                }
            }

            //verifie if the new matrix is different, if is different change the matrix
            for(int col=0; col < 8; col++)
            {
                for(int lin=0; lin < 8; lin++)
                {
                    if(auxMatrix[lin][col] != absolutePattern[lin][col]) // new data on the matrix if the condition is true
                    {
                        lin = 8; //leave the for
                        col = 8; //leave the for
                        pthread_cond_signal(&conTouchInDataAnalysis);
                        absolute->setAbsolutePattern(absolutePattern);
                    }
                }
            }

         }

        pthread_mutex_unlock(&mTouchInDataAnalysis);


    }
}

void *tIRSensorFunction( void *ptr )
{
    CSensors *sensors = CSensors::getInstance();
    float oldSpeed = 0, speed = 0;
    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerIRSensor);

        pthread_mutex_lock(&mIRDataAnalysis);

        speed = sensors->readDistanceSensor();
        sensors->setSpeed(speed);

        if(oldSpeed != speed) // new data
            pthread_cond_signal(&conIRDataAnalysis);

        pthread_mutex_unlock(&mIRDataAnalysis);

        oldSpeed = speed;
    }
}

void *tSlideSensorFunction( void *ptr )
{
    cout << "Hello tSlideSensorFunction" << endl;
    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerSlideSensor);

        pthread_mutex_lock(&mSlideDataAnalysis);

        pthread_cond_signal(&conSlideDataAnalysis);

        pthread_mutex_unlock(&mSlideDataAnalysis);
    }
}

void updateSound()
{
    pthread_mutex_lock(&mDataAnalysisSoundGenerator);

    pthread_cond_signal(&conDataAnalysisSoundGenerator);

    pthread_mutex_unlock(&mDataAnalysisSoundGenerator);
}

void processingDataSlide()
{
    static char old1 = 0, old2 = 0, old3 = 0, old4 = 0;
    static int count = 0;
    int x = 0, y = 0;
    char * buffer = new char [4], cap1, cap2, cap3, cap4;

    CSensors *sensors = CSensors::getInstance();
//    CHandSlideSensor *caps = CHandSlideSensor::getInstance();
    CLedMatrix *matrix = CLedMatrix::getInstance();

    buffer = sensors->readHandSlideSensor();

//    if(caps->openHandSlideSensor() < 0)
//        perror("Error Open Capacitive Sensors");

//    buffer = caps->readHandSlideSensor();

//    caps->closeHandSlideSensor();

    cap1 = buffer[0];
    cap2 = buffer[1];
    cap3 = buffer[2];
    cap4 = buffer[3];

    if(cap1){ // slide right
        if(old1)
            x = 1;
        old1 = cap1;
    }

    if(cap2){ // slide left
        if(old2)
            x = 0;
        old2 = cap2;
    }

    if(cap3){ // slide top
        if(old3)
            y = 0;
        old3 = cap3;
    }

    if(cap4){ // slide low
        if(old4)
            y = 1;
        old4 = cap4;
    }

    if(count++ == 20) // if in one second the slide don't is complete, slide is ignore
    {
        old1 = 0;
        old2 = 0;
        old3 = 0;
        old4 = 0;
    }

    pthread_mutex_lock(&mDataAnalysisAbsolutePattern);

    matrix->setQuadr(x,y);

    pthread_cond_signal(&conDataAnalysisAbsolutePattern);

    pthread_mutex_unlock(&mDataAnalysisAbsolutePattern);

    delete buffer;
}

void *tDataAnalysisFunction( void *ptr )
{
    int timeout1, timeout2, timeout3;
    timespec timeout;
    cout << "Hello tDataAnalysisPatternFunction" << endl;
    while (1) {

        /*------------------- SlideSensor-----------------------------------*/

        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 10000000; //timeout of 10 ms

        pthread_mutex_lock(&mSlideDataAnalysis);

        timeout3 = pthread_cond_timedwait(&conSlideDataAnalysis, &mSlideDataAnalysis, &timeout );

        if(!timeout3)
        {
            processingDataSlide();
        }

        pthread_mutex_unlock(&mSlideDataAnalysis);

        /*------------------- TouchIN ------------------------------------*/
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 10000000; //timeout of 10 ms

        pthread_mutex_lock(&mTouchInDataAnalysis);

        timeout1 = pthread_cond_timedwait(&conTouchInDataAnalysis, &mTouchInDataAnalysis, &timeout );

        if(!timeout1)
        {

            updateSound();

        }

        pthread_mutex_unlock(&mTouchInDataAnalysis);

        /*------------------- IRSensor ------------------------------------*/

        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 10000000; //timeout of 10 ms

        pthread_mutex_lock(&mIRDataAnalysis);

        timeout2 = pthread_cond_timedwait(&conIRDataAnalysis, &mIRDataAnalysis, &timeout );

        if(!timeout2)
        {

            updateSound();

        }

        pthread_mutex_unlock(&mIRDataAnalysis);

    }
}


void *tSoundGeneraterFunction( void *ptr )
{
    extern sem_t *sSoundGeneratorDaemon;
    cout << "Hello tSoundGeneraterFunction" << endl;
    while (1) {

        pthread_mutex_lock(&mDataAnalysisSoundGenerator);

        pthread_cond_wait(&conDataAnalysisSoundGenerator, &mDataAnalysisSoundGenerator );

        pthread_mutex_unlock(&mDataAnalysisSoundGenerator);

        /**+++++++++++++++++++++CGenerateSound+++++++++++++++++++*/

        char shm_fn[] = "shmDaemon";
        char sem_fn[] = "semaphoreDaemon";

        CGenerateSound * sound = new CGenerateSound();
        CAbsolutePattern *absolute = CAbsolutePattern::getInstance();

        sound->setAbsolutePattern(absolute->getAbsolutePattern());

        sound->generateSound(1);

        /**+++++++++++++END of the CGenerateSound+++++++++++++++++*/
        /**+++++++++++++++++++Shared Memory+++++++++++++++++++++++*/
        CSensors *sensors = CSensors::getInstance();
        CConvertWav wav;

        wav.convertWavFile( sound->changeSpeed(sensors->getSpeed()));

        int size, sharedMemorySize, index;
        unsigned int shmdes, mode;
        char* shmptr;
        char *pt;

        size = wav.getSubChunk();
        pt = (char *) &size;
        mode = S_IRWXU|S_IRWXG;
        /* Open the shared memory object */
        if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) {
             perror("shm_open failure");
             exit(-1);
        }
        /* Preallocate a shared memory area by determine the current
        value of a configurable system limit for pagesize*/
        sharedMemorySize = 4096 * sysconf(_SC_PAGE_SIZE);
        if(ftruncate(shmdes, sharedMemorySize) == -1){
            perror("ftruncate failure");
            exit(-1);
        }
        if((shmptr =(char *)mmap(0, sharedMemorySize, PROT_WRITE|PROT_READ, MAP_SHARED,shmdes,0)) == (caddr_t) -1) {
            perror("mmap failure");
            exit(-1);
        }
        /* Create a semaphore in locked state */
        sSoundGeneratorDaemon = sem_open(sem_fn, O_CREAT, 0644, 0);
        if(sSoundGeneratorDaemon == (void*)-1) {
          perror("sem_open failure");
          exit(-1);
        }

        shmptr[0] = *pt++;
        shmptr[1] = *pt++;
        shmptr[2] = *pt++;
        shmptr[3] = *pt;

        char *bufferOut = (char *) wav.getPCM();

        /* Access to the shared memory area */
        for(index = 4; index < size + 4; index++) {
            shmptr[index]=bufferOut[index - 4];
        }

        /* Release the semaphore lock */
        sem_post(sSoundGeneratorDaemon);
        munmap(shmptr, sharedMemorySize);
        /* Close the shared memory object */
        close(shmdes);
        /* Close the Semaphore */
        sem_close(sSoundGeneratorDaemon);
        /* Delete the shared memory object */
        //shm_unlink(shm_fn);

        /**+++++++++++++END of test of the Shared Memory++++++++++++++++++*/


    }
}

void *tAbsolutePatternFunction( void *ptr )
{
    CLedMatrix *matrix = CLedMatrix::getInstance();
    CAbsolutePattern *absolute = CAbsolutePattern::getInstance();

    while (1) {

        pthread_mutex_lock(&mDataAnalysisAbsolutePattern);

        pthread_cond_wait(&conDataAnalysisAbsolutePattern, &mDataAnalysisAbsolutePattern );

        matrix->setLedMatrix(absolute->getAbsolutePattern());

        matrix->writeLedMatrix();

        pthread_mutex_unlock(&mDataAnalysisAbsolutePattern);
    }
}

/*******************************************************************************
* Function Name  : run
* Description    : Run  the projects
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CMig::run() {
    if(!initThreads())
    {
        pthread_join( tSoundGenerater, NULL);
        pthread_join( tDataAnalysis, NULL);
        pthread_join( tTouchIn, NULL);
        pthread_join( tIRSensor, NULL);
        pthread_join( tSlideSensor, NULL);
        pthread_join( tAbsolutePattern, NULL);
        return 0;
    }
    else
        return - 1;
}

/*******************************************************************************
* Function Name  : initThreads
* Description    : Create All the threads
* Input          : None (void)
* Output         : None (void)
* Return		 :  0 if sucess
*                : -1 if fail
*******************************************************************************/
int CMig::initThreads() {

    int errortTouchIn, errortIRSensor, errortSlideSensor, errortSoundGenerater, errortAbsolutePattern, errortDataAnalysis;
    int threadPolicy;
    pthread_attr_t threadAttr;
    struct sched_param threadParam;

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    /* define prioratie tSoundGenerater */
    setupThread(1, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortSoundGenerater = pthread_create(&tSoundGenerater,&threadAttr,tSoundGeneraterFunction,NULL);

    /* define prioratie tDataAnalysis */
    setupThread(2, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortDataAnalysis = pthread_create(&tDataAnalysis,&threadAttr,tDataAnalysisFunction,NULL);

    /* define prioratie tTouchIn */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    //errortTouchIn = pthread_create(&tTouchIn,&threadAttr,tTouchInFunction,NULL);

    /* define prioratie tIRSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortIRSensor = pthread_create(&tIRSensor,&threadAttr,tIRSensorFunction,NULL);

    /* define prioratie tSlideSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    //errortSlideSensor = pthread_create(&tSlideSensor,&threadAttr,tSlideSensorFunction,NULL);

    /* define prioratie tAbsolutePattern */
    setupThread(4, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    //errortAbsolutePattern = pthread_create(&tAbsolutePattern,&threadAttr,tAbsolutePatternFunction,NULL);

    if((errortDataAnalysis != 0)&&(errortTouchIn != 0)&&(errortIRSensor != 0)&&(errortSlideSensor != 0)&&(errortSoundGenerater != 0)&&(errortAbsolutePattern != 0))
    {
        perror("Creation Threads failed.");
        return -1;
    }

    return 0;
}




/*******************************************************************************
* Function Name  : setupThread
* Description    : Define the prioratie of the thread.
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::setupThread(int prio, pthread_attr_t *pthread_attr, sched_param *pthread_param)
{
    pthread_attr_setschedpolicy (pthread_attr, SCHED_RR);
    pthread_param->sched_priority = prio;
    pthread_attr_setschedparam (pthread_attr, pthread_param);
}

CMig* CMig::instance = 0;

CMig * CMig::getInstance()
{
    if (instance == 0)
            instance = new CMig;

    return instance;
}

