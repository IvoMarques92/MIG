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
    // create a function in C because it's need have one physical address (in C++ in the classes we have a virtual address)
    //in order to atribute this function to the respetively thread
    static void *tTouchInFunction( void *ptr );
private: 
    vector<int> soundWave;
    fstream touchIn, touchOut;
    CTouchMatrix();
    ~CTouchMatrix();
    static CTouchMatrix* instance;
    char * buffer;
};

#endif //_CTOUCHMATRIX_H
