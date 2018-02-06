/******************************************************* MIG ********************************************************************************************************
 * by Cristiano Rodrigues and Ivo Marques
 *
 * Project features:
 *
 * - Produce sound based on patterns that are made in a touch matrix;
 * - React to some hands slide gestures;
 * - Show a pattern in a matrix of leds, created by the user in touch inputs;
 * - Detect pattern from touch matrix;
 * - Create a musical effect according with the matrix pattern;
 * - Produce melody.
 *
 *********************************************************************************************************************************************************************/

#include <iostream>
#include "CMig.h"


#include "CMatrixSounds.h"

#include "CGenerateSound.h"

using namespace std;

int main()
{
    CMig* Mig = CMig::getInstance();

    Mig->initMigAtuators();
    Mig->initMigSensors();
    Mig->initQueue();
    Mig->initSemaphores();
    Mig->run();

    /**+++++++++++++++++test of the CGenerateSound+++++++++++++++++*/
    CGenerateSound * sound = new CGenerateSound();

    vector<vector<char>> absoluteMatrix;

    absoluteMatrix.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        absoluteMatrix[i].resize(8);

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
    absoluteMatrix[i][j] = 1;


    sound->setAbsolutePattern(absoluteMatrix);

    sound->generateSound(0);
    /**+++++++++++++END of test of the CGenerateSound+++++++++++++++++*/
    cout << "Mig was initialize" << endl;
    return 0;
    //while(1);
}
