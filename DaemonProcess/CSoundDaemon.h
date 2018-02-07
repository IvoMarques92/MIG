#ifndef _CSOUNDDAEMON_H
#define _CSOUNDDAEMON_H

class CSoundDaemon {
public: 
    
    static CSoundDaemon* getInstance();
    void initSemaphore();
    void initSpeaker();

private: 
    static CSoundDaemon* instance;
    CSoundDaemon();
    ~CSoundDaemon();

};

#endif //_CSOUNDDAEMON_H
