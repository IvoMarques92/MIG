#include "CGenerateSound.h"

const string empty    =   " /root/sounds/empty_sound.wav";
const string column0  =   " /root/sounds/columns/column0.wav";
const string column1  =   " /root/sounds/columns/column1.wav";
const string column2  =   " /root/sounds/columns/column2.wav";
const string column3  =   " /root/sounds/columns/column3.wav";
const string column4  =   " /root/sounds/columns/column4.wav";
const string column5  =   " /root/sounds/columns/column5.wav";
const string column6  =   " /root/sounds/columns/column6.wav";
const string column7  =   " /root/sounds/columns/column7.wav";

CGenerateSound::CGenerateSound()
    :CMatrixSounds()
{
    /*  Allocate memory and Initialize at zero the absolutePattern Matrix */
    absoluteMatrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        absoluteMatrix[i].resize(8);
}

CGenerateSound::~CGenerateSound()
{
    /*deallocate the matrix absolutePattern*/
    for ( int i = 0 ; i < 8 ; i++ )
        vector<char>().swap(absoluteMatrix[i]);
    vector<vector<char>>().swap(absoluteMatrix);
}


string CGenerateSound::getPathGeneratedSound() {

    return pathWavAbsolutePatternFIle;

}


void CGenerateSound::setAbsolutePattern(vector<vector<char>> absolutePattern) {
    absoluteMatrix = absolutePattern;
    return;
}

/*******************************************************************************
* Function Name  : generateSound
* Description    : This function accordly with the effect, add and concatenate
*                : the sounds of the pattern in touchMatrix
* Input          : char effect: choose the effect (set of 8 sounds)
* Output         : None (void)
* Return		 : string: string with the name of the sound file .wav
*                ; "erro": if generateSount failed
*******************************************************************************/
string CGenerateSound::generateSound(unsigned char effect) {

    /*Add sound of each element of each column*/
    for(int i = 0; i < 8; i++)
    {
        string columnSound, soxAdd;
        columnSound = this->getEffects(effect, absoluteMatrix[i]);
        if(columnSound == "erro")
            return "erro";
        soxAdd = "sox -m " + empty + empty + columnSound + " /root/sounds/columns/column" + to_string(i) + ".wav";
        system(soxAdd.c_str());
    }

     /*Add all columns -> Add each sound of each column*/
    string soxConc, columns = column0 + column1 + column2 + column3 + column4 + column5 + column6 + column7;
    soxConc = "sox " + columns + " /root/sounds/absoluteMatrixSounds/soundEffect" + to_string(effect) + ".wav";
    system(soxConc.c_str());

    pathWavAbsolutePatternFIle = " /root/sounds/absoluteMatrixSounds/soundEffect" + to_string(effect) + ".wav";

    return pathWavAbsolutePatternFIle;
}
