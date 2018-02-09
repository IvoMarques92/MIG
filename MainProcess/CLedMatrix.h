#ifndef _CLEDMATRIX_H
#define _CLEDMATRIX_H

#include "CQuadrantRelativePattern.h"
#include "CRelativePattern.h"
#include <vector>

using namespace std;

class CLedMatrix: public CQuadrantRelativePattern, public CRelativePattern {
public: 
    static CLedMatrix* getInstance();
    void writeLedMatrix(void);
    void setLedMatrix(vector<vector<int>>);
    vector<vector<int>> getLedMatrix(void);
private: 
    vector<vector<int>> matrix;
    static CLedMatrix* instance;
    CLedMatrix();
    ~CLedMatrix();
};

#endif //_CLEDMATRIX_H
