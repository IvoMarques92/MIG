#include "CMatrixSounds.h"

#define EFFECTS 4


CMatrixSounds::CMatrixSounds() {

    //  Allocate memory and Initialize the pattern of strings Matrix
    pattern.resize(EFFECTS);
    for ( int i = 0 ; i < EFFECTS ; i++ )
        pattern[i].resize(8);

    //Initialization of the matrix with the namo of the files of wav sound
    /*First Pattern*/
    pattern[0][0] = "/root/sounds/pentatonix/C#6.wav";
    pattern[0][1] = "/root/sounds/pentatonix/B5.wav";
    pattern[0][2] = "/root/sounds/pentatonix/G#5.wav";
    pattern[0][3] = "/root/sounds/pentatonix/F#5.wav";
    pattern[0][4] = "/root/sounds/pentatonix/E5.wav";
    pattern[0][5] = "/root/sounds/pentatonix/C#5.wav";
    pattern[0][6] = "/root/sounds/pentatonix/B4.wav";
    pattern[0][7] = "/root/sounds/pentatonix/G#4.wav";

    /*Second Pattern*/
    pattern[1][0] = "/root/sounds/pentatonix/F#4.wav";
    pattern[1][1] = "/root/sounds/pentatonix/E4.wav";
    pattern[1][2] = "/root/sounds/pentatonix/C#4.wav";
    pattern[1][3] = "/root/sounds/pentatonix/B3.wav";
    pattern[1][4] = "/root/sounds/pentatonix/G#3.wav";
    pattern[1][5] = "/root/sounds/pentatonix/F#3.wav";
    pattern[1][6] = "/root/sounds/pentatonix/E3.wav";
    pattern[1][7] = "/root/sounds/pentatonix/C#3.wav";

    /*Third Pattern*/
    pattern[2][0] = "/root/sounds/drums/clap.wav";
    pattern[2][1] = "/root/sounds/drums/bell.wav";
    pattern[2][2] = "/root/sounds/drums/tube.wav"; //snare
    pattern[2][3] = "/root/sounds/drums/kick.wav";
    pattern[2][4] = "/root/sounds/pentatonix/F#4.wav";
    pattern[2][5] = "/root/sounds/pentatonix/C#4.wav";
    pattern[2][6] = "/root/sounds/pentatonix/G#3.wav";
    pattern[2][7] = "/root/sounds/pentatonix/E3.wav";

    /*4º Pattern*/
    pattern[3][0] = "/root/sounds/drums/clap.wav";
    pattern[3][1] = "/root/sounds/drums/bell.wav";
    pattern[3][2] = "/root/sounds/drums/hihat.wav";
    pattern[3][3] = "/root/sounds/drums/hihat2.wav";
    pattern[3][4] = "/root/sounds/drums/hihatopen.wav";
    pattern[3][5] = "/root/sounds/drums/tube.wav";
    pattern[3][6] = "/root/sounds/drums/snare.wav";
    pattern[3][7] = "/root/sounds/drums/kick.wav";


}

CMatrixSounds::~CMatrixSounds()
{
    /*deallocate the matrix absolutePattern*/
    for ( int i = 0 ; i < EFFECTS ; i++ )
        vector<string>().swap(pattern[i]);
    vector<vector<string>>().swap(pattern);

}

/*******************************************************************************
* Function Name  : getEffects
* Description    : This function accordly with the column that is send, make a
*                : string with all the name of the .wav files that will be
*                : playback
* Input          : char effect: choose the effect (set of 8 sounds)
*                : vector<char> column: choose wich sound will be playbacked
* Output         : None (void)
* Return		 : string: string with all the name of the .wav files
*                ; "erro": if the vector column have not the right size
*******************************************************************************/
string CMatrixSounds::getEffects(unsigned char effect, vector<char> column)
{
    if(column.size() == 8)
    {
        string files;

        for(int i = 0; i < 8; i++)
        {
            if(column[i] == 1)
                files += " " + pattern[effect][i];
        }

        return files;
    }

    return "erro";
}
