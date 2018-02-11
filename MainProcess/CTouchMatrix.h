 #ifndef _CTOUCHMATRIX_H
#define _CTOUCHMATRIX_H

#include <vector>
#include <fstream>

using namespace std;

class CTouchMatrix {
public: 
    static CTouchMatrix* getInstance();
    int openTouchMatrix();
    void closeTouchMatrix();
    char *readTouchMatrix();
    
private: 
    vector<int> soundWave;
    fstream touchIn, touchOut;
    CTouchMatrix();
    ~CTouchMatrix();
    static CTouchMatrix* instance;
    char * buffer;
};

#endif //_CTOUCHMATRIX_H
