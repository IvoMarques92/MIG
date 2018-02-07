#ifndef _CCONVERTWAV_H
#define _CCONVERTWAV_H

#include <string>

using namespace std;

class CConvertWav {
public: 
    
    CConvertWav();
    ~CConvertWav();
    
    void* getPCM();
    
    void convertWavFile(string);
private: 
    struct headerWav;
    void* absolutePatternSoundPCM;
    string pathWavFile;
};

#endif //_CCONVERTWAV_H
