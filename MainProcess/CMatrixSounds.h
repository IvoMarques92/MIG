/**
 * Project Untitled
 */


#ifndef _CMATRIXSOUNDS_H
#define _CMATRIXSOUNDS_H

class CMatrixSounds {
public: 
    
    void CMatrixSounds();
protected: 
    
    /**
     * @param effect
     * @param column
     */
    string getEffects(char effect, vector char column);
private: 
    vector<vector<string>> pattern;
};

#endif //_CMATRIXSOUNDS_H