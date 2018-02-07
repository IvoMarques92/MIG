#ifndef _CSPEAKERDAEMON_H
#define _CSPEAKERDAEMON_H

class CSpeakerDaemon {
public: 
    
    static CSpeakerDaemon* getInstance();
    
    void initSpeaker();
    void closeSpeaker();
    int wrtieSpeaker(void* microData);

private: 
    static CSpeakerDaemon* instance;
    CSpeakerDaemon();
    ~CSpeakerDaemon();
};

#endif //_CSPEAKERDAEMON_H
