#include "CSoundDaemon.h"


CSoundDaemon::CSoundDaemon() {

}

CSoundDaemon::~CSoundDaemon()
{

}

/*******************************************************************************
* Function Name  : initSemaphores
* Description    : Initialize all semaphores
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSoundDaemon::initSemaphore() {
    return;
}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Initialize Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSoundDaemon::initSpeaker() {
    return;
}

CSoundDaemon* CSoundDaemon::instance = 0;

CSoundDaemon * CSoundDaemon::getInstance()
{
    if (instance == 0)
            instance = new CSoundDaemon;

    return instance;
}
