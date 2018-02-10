#ifndef _CMIG_H
#define _CMIG_H


#include <pthread.h>
#include <semaphore.h>
#include <signal.h>


#include <unistd.h> //sleep
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>



class CMig {
public: 
    static CMig* getInstance();
    void initConditionVariables();
    void initMigAtuators();
    void initMigSensors();
    void initSemaphores();
    void initMutexs();
    void initSignal();
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
