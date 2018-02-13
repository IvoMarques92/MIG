#include "CMig.h"
#include "CSensors.h"
#include "CLedMatrix.h"
#include "CActuators.h"
#include "CConvertWav.h"
#include "CTouchMatrix.h"
#include "CGenerateSound.h"
#include "CDistanceSensor.h"
#include "CHandSlideSensor.h"
#include "CAbsolutePattern.h"

CMig::CMig() {

    extern sem_t *sSoundGeneratorDaemon;

    char shm_fn[] = "shmDaemon";
    char sem_fn[] = "semaphoreDaemon";

    shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG);
    sSoundGeneratorDaemon = sem_open(sem_fn, O_CREAT, 0644, 0);
    sem_close(sSoundGeneratorDaemon);

    system("/root/DaemonProcess");

    CAbsolutePattern *absolute = CAbsolutePattern::getInstance();
    absolute->clearAbsolutePattern();

    CLedMatrix *matrix = CLedMatrix::getInstance();
    matrix->setQuadr(0,0);
    matrix->setLedMatrix(absolute->getAbsolutePattern());

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
    extern sem_t sUpdateSound;

    sem_init (&sTimerTouchIn, 0, 0); //second 0 -> the semaphore is shared between threads of the process
    sem_init (&sTimerIRSensor, 0, 0); //second 0 -> the semaphore is shared between threads of the process
    sem_init (&sTimerSlideSensor, 0, 0); //second 0 -> the semaphore is shared between threads of the process
    sem_init (&sUpdateSound, 0 , 0);

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
    extern pthread_mutex_t mAbsolutePattern;
    extern pthread_mutex_t mSlideDataAnalysis;
    extern pthread_mutex_t mTouchInDataAnalysis;
    extern pthread_mutex_t mDataAnalysisAbsolutePattern;

    mIRDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
    mAbsolutePattern = PTHREAD_MUTEX_INITIALIZER;
    mSlideDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
    mTouchInDataAnalysis = PTHREAD_MUTEX_INITIALIZER;
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

    // 8ms interrupt
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 8000;//it_interval -> recarga
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 8000; //only for the first timer expires

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
    extern sem_t sTimerTouchIn, sTimerIRSensor, sTimerSlideSensor;
    static int count = 0;
    if(sign == SIGALRM)
    {

         /* Post to the semaphore to sample the sensors.*/
        switch (++count) {
        case 1:
            sem_post (&sTimerTouchIn);
            break;
        case 2:
            sem_post (&sTimerSlideSensor);
            break;
        case 3:
            sem_post (&sTimerIRSensor);
            break;
        default:
            count = 0;
            break;
        }

    }
}

void *tAbsolutePatternFunction( void *ptr )
{
    extern pthread_cond_t conDataAnalysisAbsolutePattern;
    extern pthread_mutex_t mAbsolutePattern;
    CLedMatrix *matrix = CLedMatrix::getInstance();
    CAbsolutePattern *absolute = CAbsolutePattern::getInstance();

    while (1) {

        pthread_mutex_lock(&mAbsolutePattern);

        pthread_cond_wait(&conDataAnalysisAbsolutePattern, &mAbsolutePattern );

        matrix->setLedMatrix(absolute->getAbsolutePattern());

        pthread_mutex_unlock(&mAbsolutePattern);

        matrix->writeLedMatrix();
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
    extern pthread_t tTouchIn, tIRSensor, tSlideSensor, tSoundGenerater;
    if(!initThreads())
    {
        pthread_join( tSoundGenerater, NULL);
  //      pthread_join( tDataAnalysis, NULL);
        pthread_join( tTouchIn, NULL);
        pthread_join( tIRSensor, NULL);
        pthread_join( tSlideSensor, NULL);
//        pthread_join( tAbsolutePattern, NULL);
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
    extern pthread_t tTouchIn, tIRSensor, tSlideSensor, tSoundGenerater;

    CTouchMatrix *touch = CTouchMatrix::getInstance();
    CHandSlideSensor *slideSensor = CHandSlideSensor::getInstance();
    CDistanceSensor *distanceSensor =  CDistanceSensor::getInstance();
    CGenerateSound generateSoundc;

    int threadPolicy;
    pthread_attr_t threadAttr;
    struct sched_param threadParam;

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    /* define prioratie tSoundGenerater */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortSoundGenerater = pthread_create(&tSoundGenerater,&threadAttr,generateSoundc.tSoundGeneraterFunction,NULL);

    /* define prioratie tDataAnalysis */
    setupThread(2, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    //errortDataAnalysis = pthread_create(&tDataAnalysis,&threadAttr,tDataAnalysisFunction,NULL);

    /* define prioratie tTouchIn */
    setupThread(1, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortTouchIn = pthread_create(&tTouchIn,&threadAttr,touch->tTouchInFunction,NULL);

    /* define prioratie tIRSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortIRSensor = pthread_create(&tIRSensor,&threadAttr,distanceSensor->tIRSensorFunction,NULL);

    /* define prioratie tSlideSensor */
    setupThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    errortSlideSensor = pthread_create(&tSlideSensor,&threadAttr,slideSensor->tSlideSensorFunction,NULL);

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

