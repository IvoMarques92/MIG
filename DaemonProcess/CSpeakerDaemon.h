#ifndef _CSPEAKERDAEMON_H
#define _CSPEAKERDAEMON_H

#include <alsa/asoundlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <string>

using namespace std;

class CSpeakerDaemon {
public: 
    
    static CSpeakerDaemon* getInstance();
    
    void initSpeaker();
    void closeSpeaker();
    int wrtieSpeaker();
    void sharedMemory();

private: 
    static CSpeakerDaemon* instance;
    CSpeakerDaemon();
    ~CSpeakerDaemon();
    string device;                        /* playback device */
    string shmFile;
    string semFile;
    char *wavData;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
    int sizeWav;
    int sharedMemorySize;
};

#endif //_CSPEAKERDAEMON_H
