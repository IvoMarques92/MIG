#ifndef _CMIG_H
#define _CMIG_H

class CMig {
public: 
    static CMig* getInstance();
    void initMigAtuators();
    void initMigSensors();
    void initSemaphores();
    void initQueue();
    void run();
    
private: 
    static CMig* instance;
    CMig();
    ~CMig();
    int initThreads();
};

#endif //_CMIG_H
