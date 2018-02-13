#ifndef _CGENERATESOUND_H
#define _CGENERATESOUND_H

#include "CMatrixSounds.h"

#include <string>
#include <vector>
#include <iostream>

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
    // create a function in C because it's need have one physical address (in C++ in the classes we have a virtual address)
    //in order to atribute this function to the respetively thread
    static void *tSoundGeneraterFunction( void *ptr );

private: 
    string pathTempoEffect;
    string pathSpeedEffect;
    string pathWavAbsolutePatternFIle;
    vector<vector<char>> absoluteMatrix;
};

#endif //_CGENERATESOUND_H
