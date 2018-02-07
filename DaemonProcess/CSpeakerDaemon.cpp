#include "CSpeakerDaemon.h"


CSpeakerDaemon::CSpeakerDaemon() {

}

CSpeakerDaemon::~CSpeakerDaemon()
{

}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Initialize Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSpeakerDaemon::initSpeaker() {
    return;
}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Close Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CSpeakerDaemon::closeSpeaker() {
    return;
}

/*******************************************************************************
* Function Name  : initSpeaker
* Description    : Write a PCM wave in the Speaker
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
int CSpeakerDaemon::wrtieSpeaker(void* microData) {
    return 0;
}

CSpeakerDaemon* CSpeakerDaemon::instance = 0;

CSpeakerDaemon * CSpeakerDaemon::getInstance()
{
    if (instance == 0)
            instance = new CSpeakerDaemon;

    return instance;
}
