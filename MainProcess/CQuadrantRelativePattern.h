#ifndef _CQUADRANTRELATIVEPATTERN_H
#define _CQUADRANTRELATIVEPATTERN_H
#include <string>

using namespace std;

class CQuadrantRelativePattern {
public: 

    CQuadrantRelativePattern();
    ~CQuadrantRelativePattern();
    int getQuadrant();

protected: 
    void writeQuadrant();
    void setQuadrant(int x, int y);

private: 
    int layer;

    int fd;
    string device;
};

#endif //_CQUADRANTRELATIVEPATTERN_H
