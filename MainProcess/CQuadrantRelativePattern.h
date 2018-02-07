#ifndef _CQUADRANTRELATIVEPATTERN_H
#define _CQUADRANTRELATIVEPATTERN_H

class CQuadrantRelativePattern {
public: 

    CQuadrantRelativePattern();
    ~CQuadrantRelativePattern();

protected: 
    void writeQuadrant();
    void setQuadrant(int);

private: 
    int layer;
};

#endif //_CQUADRANTRELATIVEPATTERN_H
