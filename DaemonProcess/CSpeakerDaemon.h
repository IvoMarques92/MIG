#ifndef _CSPEAKERDAEMON_H
#define _CSPEAKERDAEMON_H

#include <alsa/asoundlib.h>
#include <string>

using namespace std;

class CSpeakerDaemon {
public: 
    
    static CSpeakerDaemon* getInstance();
    
    void initSpeaker();
    void closeSpeaker();
    int wrtieSpeaker(void* microData, int size);

private: 
    static CSpeakerDaemon* instance;
    CSpeakerDaemon();
    ~CSpeakerDaemon();
    string device;                        /* playback device */
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
};

#endif //_CSPEAKERDAEMON_H
