#include "CAbsolutePattern.h"

using namespace std;

CAbsolutePattern::CAbsolutePattern() {

    /*  Allocate memory and Initialize the absolutePattern Matrix
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
                { 0, 0, 0, 0, 0, 0, 0, 0}
    */

    absolutePattern.resize(8);
    for ( int i = 0 ; i < 8 ; i++ )
        absolutePattern[i].resize(8);
}

CAbsolutePattern::~CAbsolutePattern()
{

    /*deallocate the matrix absolutePattern*/
    for ( int i = 0 ; i < 8 ; i++ )
        vector<char>().swap(absolutePattern[i]);
    vector<vector<char>>().swap(absolutePattern);

}

/*******************************************************************************
* Function Name  : setAbsolutePattern
* Description    : set the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CAbsolutePattern::setAbsolutePattern(vector<vector<char>> absolutePatternIN) {

    absolutePattern = absolutePatternIN;
    return;
}

/*******************************************************************************
* Function Name  : getAbsolutePattern
* Description    : Get the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
vector<vector<char>> CAbsolutePattern::getAbsolutePattern() {
    return absolutePattern;
}

/*******************************************************************************
* Function Name  : clearAbsolutePattern
* Description    : Clear all the absolute pattern
* Input          : None (void)
* Output         : None (void)
* Return		 : None
*******************************************************************************/
void CAbsolutePattern::clearAbsolutePattern() {

    for ( int i = 0 ; i < 8 ; i++ )
        for ( int j = 0 ; j < 8 ; j++ )
            absolutePattern[i][j] = 0;
    return;
}

CAbsolutePattern* CAbsolutePattern::instance = 0;

CAbsolutePattern * CAbsolutePattern::getInstance()
{
    if (instance == 0)
            instance = new CAbsolutePattern;

    return instance;
}

