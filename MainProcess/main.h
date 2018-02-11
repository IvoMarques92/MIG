/******************************************************* MIG ********************************************************************************************************
 * by Cristiano Rodrigues and Ivo Marques
 *
 * Project features:
 *
 * - Produce sound based on patterns that are made in a touch matrix;
 * - React to some hands slide gestures;
 * - Show a pattern in a matrix of leds, created by the user in touch inputs;
 * - Detect pattern from touch matrix;
 * - Create a musical effect according with the matrix pattern;
 * - Produce melody.
 *
 *********************************************************************************************************************************************************************/

#ifndef MAIN_H
#define MAIN_H

#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>


/****************************Thread identifier*****************************/

pthread_t tTouchIn;
pthread_t tIRSensor;
pthread_t tSlideSensor;
pthread_t tDataAnalysis;
pthread_t tSoundGenerater;
pthread_t tAbsolutePattern;

/****************************Semaphore identifier**************************/

sem_t sTimerTouchIn;
sem_t sTimerIRSensor;
sem_t sTimerSlideSensor;
sem_t sTeste;
sem_t *sSoundGeneratorDaemon;

/****************************Mutex identifier******************************/

pthread_mutex_t mIRDataAnalysis;
pthread_mutex_t mAbsolutePattern;
pthread_mutex_t mSlideDataAnalysis;
pthread_mutex_t mTouchInDataAnalysis;
pthread_mutex_t mDataAnalysisAbsolutePattern;

/****************************Condition Variable identifier*****************/

pthread_cond_t conIRDataAnalysis;
pthread_cond_t conSlideDataAnalysis;
pthread_cond_t conTouchInDataAnalysis;
pthread_cond_t conDataAnalysisSoundGenerator;
pthread_cond_t conDataAnalysisAbsolutePattern;

#endif // MAIN_H
