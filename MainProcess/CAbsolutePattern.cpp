#include "CAbsolutePattern.h"

CAbsolutePattern::CAbsolutePattern() {

}

CAbsolutePattern::~CAbsolutePattern()
{

}

/*******************************************************************************
* Function Name  : setAbsolutePattern
* Description    : set the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CAbsolutePattern::setAbsolutePattern(vector<vector<int>> absolutePattern) {
    return;
}

/*******************************************************************************
* Function Name  : getAbsolutePattern
* Description    : Get the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
vector<vector<int>> CAbsolutePattern::getAbsolutePattern() {
    vector<vector<int>> a;
    return a;
}

/*******************************************************************************
* Function Name  : clearAbsolutePattern
* Description    : Clear all the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CAbsolutePattern::clearAbsolutePattern() {
    return;
}

CAbsolutePattern* CAbsolutePattern::instance = 0;

CAbsolutePattern * CAbsolutePattern::getInstance()
{
    if (instance == 0)
            instance = new CAbsolutePattern;

    return instance;
}

