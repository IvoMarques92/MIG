#include "CSpeakerDaemon.h"


CSpeakerDaemon::CSpeakerDaemon()
    :device("default")
{

}

CSpeakerDaemon::~CSpeakerDaemon()
{

}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Initialize Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSpeakerDaemon::initSpeaker() {

    if ((snd_pcm_open(&handle, device.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
            perror("Playback open error");
            exit(EXIT_FAILURE);
    }
    if ((snd_pcm_set_params(handle,SND_PCM_FORMAT_S16_LE,SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000)) < 0) {   /* 0.5sec */
            perror("Playback open error");
            exit(EXIT_FAILURE);
    }

    return;
}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Close Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSpeakerDaemon::closeSpeaker() {

    snd_pcm_close(handle);

    return;
}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Write a PCM wave in the Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CSpeakerDaemon::wrtieSpeaker(void* microData, int size) {

    frames = snd_pcm_writei(handle, microData,  size);

//   if (frames < 0)
//           frames = snd_pcm_recover(handle, frames, 0);
//   if (frames < 0)
//           printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
//   if (frames > 0 && frames < ((long)(wav.subchunk2_size)/4))
//           printf("Short write (expected %li, wrote %li)\n", ((long)(wav.subchunk2_size)/4), frames);

    return 0;
}

CSpeakerDaemon* CSpeakerDaemon::instance = 0;

CSpeakerDaemon * CSpeakerDaemon::getInstance()
{
    if (instance == 0)
            instance = new CSpeakerDaemon;

    return instance;
}
