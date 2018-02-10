#include "CMig.h"
#include "CSensors.h"
#include "CActuators.h"

#include <iostream>

using namespace std;

extern pthread_cond_t mcDataAnalysisAbsolutePattern;
extern sem_t sTimerTouchIn, sTimerIRSensor, sTimerSlideSensor;
extern pthread_mutex_t mDataAnalysis4Leds, mDataAnalusisTouchOut, mDataAnalysis2DLedMatrix;
extern pthread_t tTouchIn, tIRSensor, tSlideSensor, tSoundGenerater, tAbsolutePattern, tDataAnalysis;
extern mqd_t qTouchInDataAnalysis, qIRSensorDataAnalysis, qSlideSensorDataAnalysis, qDataAnalysisSoundGenerator;


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

void CMig::ISR(int sign)
{
    if(sign == SIGALRM)
    {
         /* Post to the semaphore to sample the sensors.*/
         sem_post (&sTimerSlideSensor);
         sem_post (&sTimerIRSensor);
         sem_post (&sTimerSlideSensor);

    }
}

/*******************************************************************************
* Function Name  : initQueue
* Description    : Initialize Queue
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initQueue() {
    return;
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

#include <unistd.h>

void *tTouchInFunction( void *ptr )
{
    cout << "Hello tTouchInFunction" << endl;
    while (1) {
        /* Wait for sTimerSlideSensor semaphore. If its value is positive,
        decrement the count and execute the code. If zero, block until a
        new semaphore post. */
        sem_wait (&sTimerSlideSensor);
        printf("*\n");
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
        printf("**\n");
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
        printf("***\n");
    }
}

void *tDataAnalysisFunction( void *ptr )
{
    cout << "Hello tDataAnalysisPatternFunction" << endl;
    while (1) {

    }
}
void *tSoundGeneraterFunction( void *ptr )
{
    cout << "Hello tSoundGeneraterFunction" << endl;
    while (1) {

    }
}

void *tAbsolutePatternFunction( void *ptr )
{
    cout << "Hello tAbsolutePatternFunction" << endl;
    while (1) {

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
