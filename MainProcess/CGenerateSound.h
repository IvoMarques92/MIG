#ifndef _CGENERATESOUND_H
#define _CGENERATESOUND_H

#include "CMatrixSounds.h"

#include <string>
#include <vector>

using namespace std;

class CGenerateSound: public CMatrixSounds {
public: 
    
    CGenerateSound();
    ~CGenerateSound();
    string getPathGeneratedSound();
    string getPathTempoEffect();
    string getPathSpeedEffect();
    void setAbsolutePattern(vector<vector<char>>);
    string changeSpeed(float);
    string changeTempo(float);
    string generateSound(unsigned char);

private: 
    string pathTempoEffect;
    string pathSpeedEffect;
    string pathWavAbsolutePatternFIle;
    vector<vector<char>> absoluteMatrix;
};

#endif //_CGENERATESOUND_H
