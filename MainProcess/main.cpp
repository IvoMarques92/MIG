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

#include "CDistanceSensor.h"
#include "vector"
#include "time.h"

using namespace std;

int main()
{
    CMig* Mig = CMig::getInstance();

    Mig->initMigAtuators();
    Mig->initMigSensors();
    Mig->initQueue();
    Mig->initSemaphores();
    Mig->run();

    /**+++++++++++++++++test I2C +++++++++++++++++++++++++++++++++++++*/
    CDistanceSensor * distancia = CDistanceSensor::getInstance();
    float aux;
    while(1) {

    distancia->startReadCDistanceSensor();
    //1.25ms de delay
    usleep(1250);
    aux = distancia->readCDistanceSensor();
    cout << "distance: " << aux << "Volts" << endl;

    sleep(2);
    }
    /**++++++++++++++++++++++++END of test+++++++++++++++++++++++++++++*/



    cout << "Mig was initialize" << endl;
    return 0;
    //while(1);
}
