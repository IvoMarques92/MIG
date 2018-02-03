/**
 * Project Untitled
 */


#ifndef _CACTUATORS_H
#define _CACTUATORS_H

class CActuators {
public: 
    
    void initActuators();
    
    void closeActuators();
    
    /**
     * @param vector vector vector int
     */
    void setLedMatrix(void vector vector vector int);
    
    int getDataLedMatrix();
    
    /**
     * @param microData
     */
    int wrtieSpeaker(void microData);
    
    struct getAllData();
    
    CActuators static getInstance();
private: 
    struct dataSensors;
    CActuators static instance;
    
    void CActuators();
};

#endif //_CACTUATORS_H