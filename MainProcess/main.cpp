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
#include "main.h"

int main()
{

    CMig* Mig = CMig::getInstance();

    Mig->initMigAtuators();
    Mig->initMigSensors();
    Mig->initSemaphores();
    Mig->initMutexs();
    Mig->initConditionVariables();
    Mig->initSignal();
    Mig->run();

    pthread_exit(NULL);
}
