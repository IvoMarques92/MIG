#include "CConvertWav.h"
#include <alsa/asoundlib.h>
#include <stdlib.h>

CConvertWav::CConvertWav() {

    wavData = malloc(1); //just to initialize
}

CConvertWav::~CConvertWav()
{
    free(wavData);
}


void* CConvertWav::getPCM() {
    return wavData;
}

int CConvertWav::getSubChunk()
{
    return wav.subchunk2_size;
}

/*******************************************************************************
* Function Name  : convertWavFile
* Description    : Convert a sound in one wav file to PCM
* Input          : string pathNameFile
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CConvertWav::convertWavFile(string pathNameFile) {

    FILE * wav_in;
    wav_in = fopen(pathNameFile.c_str(),"rb");     // Open wave file in read mode
    wavPtr=&wav;
    if (wav_in)
    {
        fread(wavPtr, 1, sizeof(wav), wav_in);
        wavData=realloc(wavData, wav.subchunk2_size);
        fread(wavData,wav.bits_per_sample/8,wav.subchunk2_size,wav_in);
    }
    else
        perror("Error Open convertWavFile");

    return;
}
