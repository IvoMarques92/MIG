/**
 * Project Untitled
 */


#ifndef _CSOUNDDAEMON_H
#define _CSOUNDDAEMON_H

class CSoundDaemon {
public: 
    
    CSoundDaemon static getInstance();
    
    void initSemaphore();
    
    void initSpeaker();
private: 
    CSoundDaemon static instance;
    
    void CSoundDaemon();
};

#endif //_CSOUNDDAEMON_H