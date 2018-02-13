#ifndef _CABSOLUTEPATTERN_H
#define _CABSOLUTEPATTERN_H

#include <vector>

using namespace std;

class CAbsolutePattern {
public: 
    static CAbsolutePattern* getInstance();
    void setAbsolutePattern(vector<vector<char>>);
    void clearAbsolutePattern();
    vector<vector<char>> getAbsolutePattern();

private: 
    static CAbsolutePattern* instance;
    vector<vector<char>> absolutePattern;
    CAbsolutePattern();
    ~CAbsolutePattern();
};

#endif //_CABSOLUTEPATTERN_H
