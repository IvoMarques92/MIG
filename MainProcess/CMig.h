#ifndef _CMIG_H
#define _CMIG_H

#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>

class CMig {
public: 
    static CMig* getInstance();
    void initMigAtuators();
    void initMigSensors();
    void initSemaphores();
    void initQueue();
    int run();

private:
    static CMig* instance;
    CMig();
    ~CMig();
    int initThreads();
    void setupThread(int prio, pthread_attr_t *pthread_attr, struct sched_param *pthread_param);
};

#endif //_CMIG_H
