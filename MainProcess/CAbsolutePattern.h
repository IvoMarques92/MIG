/**
 * Project Untitled
 */


#ifndef _CABSOLUTEPATTERN_H
#define _CABSOLUTEPATTERN_H

class CAbsolutePattern {
public: 
    CAbsolutePattern static instance;
    
    /**
     * @param absolutePattern
     */
    void setAbsolutePattern(vector<vector<vector<int>>> absolutePattern);
    
    vector<vector<vector<int>>> getAbsolutePattern();
    
    /**
     * @param absolutePattern
     */
    void clearAbsolutePattern(vector<vector<vector<int>>> absolutePattern);
    
    CAbsolutePattern static getInstance();
private: 
    vector<vector<vector<int>>> absolutePattern;
    
    void CAbsolutePattern();
};

#endif //_CABSOLUTEPATTERN_H