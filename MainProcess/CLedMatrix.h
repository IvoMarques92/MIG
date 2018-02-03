/**
 * Project Untitled
 */


#ifndef _CLEDMATRIX_H
#define _CLEDMATRIX_H

#include "CQuadrantRelativePattern.h"
#include "CRelativePattern.h"


class CLedMatrix: public CQuadrantRelativePattern, public CRelativePattern {
public: 
    
    /**
     * @param void
     */
    void writeLedMatrix(void void);
    
    /**
     * @param vector vector vector int
     */
    void setLedMatrix(void vector vector vector int);
    
    /**
     * @param void
     */
    vector<vector<vector<int>>> getLedMatrix(void void);
private: 
    vector<vector<int>> Matrix;
    CLedMatrix static instance;
    
    void CLedMatrix();
};

#endif //_CLEDMATRIX_H