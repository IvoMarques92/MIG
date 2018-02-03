/**
 * Project Untitled
 */


#ifndef _CSPEAKERDAEMON_H
#define _CSPEAKERDAEMON_H

class CSpeakerDaemon {
public: 
    
    CSpeakerDaemon static getInstance();
    
    void initSpeaker();
    
    void closeSpeaker();
    
    /**
     * @param microData
     */
    int wrtieSpeaker(void microData);
private: 
    CSpeakerDaemon static instance;
    
    void CSpeakerDaemon();
};

#endif //_CSPEAKERDAEMON_H