/**
 * Project Untitled
 */


#ifndef _CMIG_H
#define _CMIG_H

class CMig {
public: 
    
    void initMigAtuators();
    
    void initMigSensors();
    
    void initSemaphores();
    
    void initQueue();
    
    void run();
    
    CMig static getInstance();
private: 
    CMig static instance;
    
    void CLecs();
    
    int initTasks();
};

#endif //_CMIG_H