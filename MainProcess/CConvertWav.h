#ifndef _CCONVERTWAV_H
#define _CCONVERTWAV_H

#include <string>

using namespace std;

class CConvertWav {
public: 
    
    CConvertWav();
    ~CConvertWav();
    
    void* getPCM();
    int getSubChunk();
    void convertWavFile(string);
private: 

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
    }headerWav;

    headerWav wav;
    void* wavPtr;
    void* wavData;
    void* absolutePatternSoundPCM;
};

#endif //_CCONVERTWAV_H
