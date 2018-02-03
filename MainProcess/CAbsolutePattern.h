#ifndef _CABSOLUTEPATTERN_H
#define _CABSOLUTEPATTERN_H

#include <vector>

using namespace std;

class CAbsolutePattern {
public: 
    static CAbsolutePattern* getInstance();
    void setAbsolutePattern(vector<vector<int>> absolutePattern);
    vector<vector<int>> getAbsolutePattern();
    void clearAbsolutePattern();

private: 
    static CAbsolutePattern* instance;
    vector<vector<int>> absolutePattern;
    CAbsolutePattern();
    ~CAbsolutePattern();
};

#endif //_CABSOLUTEPATTERN_H
