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

#include "CLedMatrix.h"
#include "vector"

using namespace std;

int main()
{
    CMig* Mig = CMig::getInstance();

    Mig->initMigAtuators();
    Mig->initMigSensors();
    Mig->initQueue();
    Mig->initSemaphores();
    Mig->run();

    /**+++++++++++++++++test CLedMatrix+++++++++++++++++++++++++++++++*/
    CLedMatrix * matrix = CLedMatrix::getInstance();

    vector<vector<char>> ma;

    ma.resize(8);
    for(int c = 0; c < 8; c++)
    {
        ma[c].resize(8);
        for(int i = 0; i < 4; i++)
        {
            ma[c][i] = c+i;
        }
    }

    matrix->setLedMatrix(ma);

    matrix->writeLedMatrix();

    /**+++++++++++++END of test of the CGenerateSound+++++++++++++++++*/



    cout << "Mig was initialize" << endl;
    return 0;
    //while(1);
}
