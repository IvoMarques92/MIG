#ifndef _CMIG_H
#define _CMIG_H

#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/time.h>

class CMig {
public: 
    static CMig* getInstance();
    void initMigAtuators();
    void initMigSensors();
    void initSemaphores();
    void initSignal();
    void initQueue();
    int run();

private:
    static CMig* instance;
    CMig();
    ~CMig();
    int initThreads();
    void setupThread(int, pthread_attr_t *, struct sched_param *);
    static void ISR(int); //static because signal(SIGALRM,ISR);
};

#endif //_CMIG_H
