/**
 * Project Untitled
 */


#ifndef _CTOUCHMATRIX_H
#define _CTOUCHMATRIX_H

class CTouchMatrix {
public: 
    
    void initCTouchMatrix();
    
    void closeCTouchMatrix();
    
    int readCTouchMatrix();
    
    CTouchMatrix static getInstance();
private: 
    vector<int> soundWave;
    CTouchMatrix static instance;
    
    void CTouchMatrix();
};

#endif //_CTOUCHMATRIX_H