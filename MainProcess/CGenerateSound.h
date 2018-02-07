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
    void setAbsolutePattern(vector<vector<char>>);
    void changeSpeed(int);
    void changeTempo(int);
    string generateSound(unsigned char);

private: 
    string pathWavAbsolutePatternFIle;
    vector<vector<char>> absoluteMatrix;
};

#endif //_CGENERATESOUND_H
