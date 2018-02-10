#include "CMig.h"
#include "CSensors.h"
#include "CActuators.h"

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

    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 250000;//it_interval -> recarga
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 250000; //only for the first timer expires

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
        pthread_join( tTouchIn, NULL);
        pthread_join( tIRSensor, NULL);
        pthread_join( tSlideSensor, NULL);
        pthread_join( tDataAnalysis, NULL);
        pthread_join( tSoundGenerater, NULL);
        pthread_join( tAbsolutePattern, NULL);
        return 0;
    }
    else
        return - 1;
}

void *tTouchInFunction( void *ptr )
{
    cout << "Hello tTouchInFunction" << endl;
    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerTouchIn);

        pthread_mutex_lock(&mTouchInDataAnalysis);

        pthread_cond_signal(&conTouchInDataAnalysis);

        pthread_mutex_unlock(&mTouchInDataAnalysis);


    }
}

void *tIRSensorFunction( void *ptr )
{
    cout << "Hello tIRSensorFunction" << endl;
    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerIRSensor);

        pthread_mutex_lock(&mIRDataAnalysis);

        pthread_cond_signal(&conIRDataAnalysis);

        pthread_mutex_unlock(&mIRDataAnalysis);
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
    pthread_mutex_lock(&mDataAnalysisAbsolutePattern);

    pthread_cond_signal(&conDataAnalysisAbsolutePattern);

    pthread_mutex_unlock(&mDataAnalysisAbsolutePattern);
}

void *tDataAnalysisFunction( void *ptr )
{
    int timeout1, timeout2, timeout3;
    timespec timeout;
    cout << "Hello tDataAnalysisPatternFunction" << endl;
    while (1) {

        /*------------------- SlideSensor-----------------------------------*/

        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 25000000;

        pthread_mutex_lock(&mSlideDataAnalysis);

        timeout3 = pthread_cond_timedwait(&conSlideDataAnalysis, &mSlideDataAnalysis, &timeout );

        if(!timeout3)
        {
            //do something
            processingDataSlide();
            cout << "3" << endl;
        }

        pthread_mutex_unlock(&mSlideDataAnalysis);

        /*------------------- TouchIN ------------------------------------*/
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 25000000;

        pthread_mutex_lock(&mTouchInDataAnalysis);

        timeout1 = pthread_cond_timedwait(&conTouchInDataAnalysis, &mTouchInDataAnalysis, &timeout );

        if(!timeout1)
        {
            //do something
             cout << "1" << endl;
            updateSound();

        }

        pthread_mutex_unlock(&mTouchInDataAnalysis);

        /*------------------- IRSensor ------------------------------------*/

        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_nsec += 25000000;

        pthread_mutex_lock(&mIRDataAnalysis);

        timeout2 = pthread_cond_timedwait(&conIRDataAnalysis, &mIRDataAnalysis, &timeout );

        if(!timeout2)
        {
            //do something
             cout << "2" << endl;
            updateSound();

        }

        pthread_mutex_unlock(&mIRDataAnalysis);

    }
}


void *tSoundGeneraterFunction( void *ptr )
{
    cout << "Hello tSoundGeneraterFunction" << endl;
    while (1) {

        pthread_mutex_lock(&mDataAnalysisSoundGenerator);

        pthread_cond_wait(&conDataAnalysisSoundGenerator, &mDataAnalysisSoundGenerator );

        //do something
        cout << "sound " << endl;

        pthread_mutex_unlock(&mDataAnalysisSoundGenerator);
    }
}

void *tAbsolutePatternFunction( void *ptr )
{
    cout << "Hello tAbsolutePatternFunction" << endl;
    while (1) {

        pthread_mutex_lock(&mDataAnalysisAbsolutePattern);

        pthread_cond_wait(&conDataAnalysisAbsolutePattern, &mDataAnalysisAbsolutePattern );

        //do something
        cout << "absolute " << endl;

        pthread_mutex_unlock(&mDataAnalysisAbsolutePattern);
    }
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
    errortTouchIn = pthread_create(&tTouchIn,&threadAttr,tTouchInFunction,NULL);

    /* define prioratie tIRSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortIRSensor = pthread_create(&tIRSensor,&threadAttr,tIRSensorFunction,NULL);

    /* define prioratie tSlideSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortSlideSensor = pthread_create(&tSlideSensor,&threadAttr,tSlideSensorFunction,NULL);

    /* define prioratie tAbsolutePattern */
    setupThread(4, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortAbsolutePattern = pthread_create(&tAbsolutePattern,&threadAttr,tAbsolutePatternFunction,NULL);

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

