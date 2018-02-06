#include <iostream>

using namespace std;

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

#include "CSpeakerDaemon.h"

typedef struct file_header
{
    char chunk_id[4];
    unsigned int chunk_size;
    char format[4];
    char subchunk1_id[4];
    unsigned int subchunk1_size;
    unsigned short int audio_format;
    unsigned short int num_channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short int block_align;
    unsigned short int bits_per_sample;
    char subchunk2_id[4];
    unsigned int subchunk2_size;
}wav_header;
wav_header wav;
void* wav_ptr;
void* wav_data1;

int main()
{
    pid_t pid, sid;
    time_t timebuf;
    int fd, len;

    /* create new process */
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* exit on parent process */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* create a new session */
    sid = setsid();
    if (sid < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    /* chanhe the root directory */
    if (chdir("/") < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    /* reset umask */
    umask(0);

    /* close file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* service implementation */

    FILE * wav_in;
    wav_in = fopen("root/sounds/absoluteMatrixSounds/soundEffect0.wav","rb");     // Open wave file in read mode
    wav_ptr=&wav;

    if (wav_in)
    {
        fread(wav_ptr, 1, sizeof(wav), wav_in);
        wav_data1=malloc(wav.subchunk2_size);
        fread(wav_data1,wav.bits_per_sample/8,wav.subchunk2_size,wav_in);
    }

    CSpeakerDaemon * speaker = CSpeakerDaemon::getInstance();

    speaker->initSpeaker();

    while (1) {


    speaker->wrtieSpeaker(wav_data1, (wav.subchunk2_size)/4 );



    /*+++++++++++tetstes++++++++++++++++*/
        if ((fd = open("/var/log/example1.log",
                O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        write(fd, "buf\n", 4);
        close(fd);
    /*+++++++++++tetstes++++++++++++++++*/
       // sleep(5);
    }
    speaker->closeSpeaker();
    exit(EXIT_SUCCESS);
}
