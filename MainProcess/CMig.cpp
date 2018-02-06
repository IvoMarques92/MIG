#include "CMig.h"
#include "CSensors.h"
#include "CActuators.h"

#include <iostream>

using namespace std;

CMig::CMig() {

    cout << "constr MIG" << endl;

}

CMig::~CMig()
{

}

/*******************************************************************************
* Function Name  : initMigAtuators
* Description    : Initialize Atuators
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initMigAtuators() {

    CActuators* actuators = CActuators::getInstance();
    actuators->initActuators();

    return;
}

/*******************************************************************************
* Function Name  : initMigSensors
* Description    : Initialize Mig Sensors
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initMigSensors() {

    CSensors* sensors = CSensors::getInstance();
    sensors->initSensors();

    return;
}

/*******************************************************************************
* Function Name  : initSemaphores
* Description    : Initialize Semaphores
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initSemaphores() {
    return;
}

/*******************************************************************************
* Function Name  : initQueue
* Description    : Initialize Queue
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::initQueue() {
    return;
}

/*******************************************************************************
* Function Name  : run
* Description    : Run  the projects
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CMig::run() {
    return;
}

/*******************************************************************************
* Function Name  : initThreads
* Description    : Create All the threads
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CMig::initThreads() {
    return 0;
}

CMig* CMig::instance = 0;

CMig * CMig::getInstance()
{
    if (instance == 0)
            instance = new CMig;

    return instance;
}
