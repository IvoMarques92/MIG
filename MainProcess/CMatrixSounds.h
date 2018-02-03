#ifndef _CMATRIXSOUNDS_H
#define _CMATRIXSOUNDS_H

#include <string>
#include <vector>

using namespace std;

class CMatrixSounds {
public: 
    
    CMatrixSounds();
    ~CMatrixSounds();
protected: 
    
    string getEffects(char effect, vector<char> column);
private: 
    vector<vector<string>> pattern;
};

#endif //_CMATRIXSOUNDS_H
