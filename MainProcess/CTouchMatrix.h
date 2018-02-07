#ifndef _CTOUCHMATRIX_H
#define _CTOUCHMATRIX_H

#include <vector>

using namespace std;

class CTouchMatrix {
public: 
    static CTouchMatrix* getInstance();
    void initTouchMatrix();
    void closeTouchMatrix();
    int readTouchMatrix();
    
private: 
    vector<int> soundWave;
    static CTouchMatrix* instance;
    CTouchMatrix();
    ~CTouchMatrix();
};

#endif //_CTOUCHMATRIX_H
