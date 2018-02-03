#ifndef _CRELATIVEPATTERN_H
#define _CRELATIVEPATTERN_H

#include <vector>

using namespace std;

class CRelativePattern {
public: 
    CRelativePattern();
    ~CRelativePattern();

protected: 
    void writeRelativePattern();
    void setRelativePattern(vector<vector<int>>);

private: 
    vector<vector<int>> matrix;
};

#endif //_CRELATIVEPATTERN_H
