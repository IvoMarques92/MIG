#include "CSpeakerDaemon.h"


CSpeakerDaemon::CSpeakerDaemon()
    :device("default"), shmFile("shmDaemon"), semFile("semaphoreDaemon")
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
int CSpeakerDaemon::wrtieSpeaker() {

    frames = snd_pcm_writei(handle, wavData,  sizeWav);

//   if (frames < 0)
//           frames = snd_pcm_recover(handle, frames, 0);
//   if (frames < 0)
//           printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
//   if (frames > 0 && frames < ((long)(wav.subchunk2_size)/4))
//           printf("Short write (expected %li, wrote %li)\n", ((long)(wav.subchunk2_size)/4), frames);

    return 0;
}

/*******************************************************************************
* Function Name  : initSemaphores
* Description    : Initialize all semaphores
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSpeakerDaemon::sharedMemory()
{
    char* shmptr, *ptr;
    unsigned int shmdes, index;
    sem_t *sDaemon;

    /* Open the shared memory object */
    if ( (shmdes = shm_open(shmFile.c_str(), O_RDWR, 0)) == -1 ) {
        perror("shm_open failure");
        exit(-1);
    }
    sharedMemorySize = 4096 * sysconf(_SC_PAGE_SIZE);
    if((shmptr = (char *) mmap(0, sharedMemorySize, PROT_WRITE|PROT_READ, MAP_SHARED,shmdes,0)) == (caddr_t) -1){
        perror("mmap failure");
        exit(-1);
    }

    /* Open the Semaphore */
    sDaemon = sem_open(semFile.c_str(), 0, 0644, 0);
    if(sDaemon == (void*) -1) {
       perror("sem_open failure");
       exit(-1);
    }

    /* Lock the semaphore */
    if(!sem_wait(sDaemon)){
       /* Access to the shared memory area */
        ptr = (char *)&sizeWav;
       *ptr++ = shmptr[0];
       *ptr++ = shmptr[1];
       *ptr++ = shmptr[2];
       *ptr =   shmptr[3];

       delete wavData; // delete the last PCM data
       wavData = new short[sizeWav];

       for(index = 4; index < sizeWav + 4; index++)
           wavData[index - 4] = shmptr[index];

       /* Release the semaphore lock */
       sem_post(sDaemon);
    }

    munmap(shmptr, sharedMemorySize);
    /* Close the shared memory object */
    close(shmdes);
    /* Close the Semaphore */
    sem_close(sDaemon);
    sem_unlink(semFile.c_str());
}


CSpeakerDaemon* CSpeakerDaemon::instance = 0;

CSpeakerDaemon * CSpeakerDaemon::getInstance()
{
    if (instance == 0)
            instance = new CSpeakerDaemon;

    return instance;
}
