/**
 * Project Untitled
 */


#ifndef _CGENERATESOUND_H
#define _CGENERATESOUND_H

#include "CMatrixSounds.h"


class CGenerateSound: public CMatrixSounds {
public: 
    
    void CGenerateSound();
    
    string getPathGeneratedSound();
    
    /**
     * @param vector vector char
     */
    void setAbsolutePattern(void vector vector char);
    
    string generateSound();
private: 
    string pathWavAbsolutePatternFIle;
    vector<vector<char>> absoluteMatrix;
};

#endif //_CGENERATESOUND_H