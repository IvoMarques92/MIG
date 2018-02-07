#ifndef _CACTUATORS_H
#define _CACTUATORS_H

#include <vector>

using namespace std;

class CActuators {
public: 
    
    void initActuators();
    void closeActuators();
    void setLedMatrix( vector<vector<int>> );
    int getDataLedMatrix();
    int wrtieSpeaker(void* microData);   
    static CActuators* getInstance();
private: 
    CActuators();
    ~CActuators();
    struct dataSensors{
        int i;
    };
    static CActuators* instance;
};

#endif //_CACTUATORS_H
