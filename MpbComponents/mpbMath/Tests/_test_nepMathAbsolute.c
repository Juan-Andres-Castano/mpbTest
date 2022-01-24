/**
* @file			test_nepMathAbsolute.c
* @brief
* @author		vincent
* @date			Created on 2019-10-23
* @note
* @copyright NEP, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2015 NEP, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of NEPTRONIC (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of NEPTRONIC.</center>
*
**/
/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include "nepMathAbsolute.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static eNepError_t eNepError;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void setUp()
{
    eNepError = eUnknownError;
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{

}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eNepMathAbsoluteSubstractionFloat                      
*******************************************************************************/

void test_eNepMathAbsoluteSubstractionFloat_InvalidParameter_Fail()
{
    float fMockValue1 = 10, fMockValue2 = 30;
    
    eNepError = eNepMathAbsoluteSubstractionFloat( fMockValue1, fMockValue2, NULL );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAbsoluteSubstractionFloat_Value1GreaterThenValue2_Success()
{
    float fMockValue1 = 50, fMockValue2 = 30, fDifference;
    
    eNepError = eNepMathAbsoluteSubstractionFloat( fMockValue1, fMockValue2, &fDifference );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_FLOAT( 20, fDifference );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAbsoluteSubstractionFloat_Value1EqualValue2_Success()
{
    float fMockValue1 = 30, fMockValue2 = 30, fDifference;
    
    eNepError = eNepMathAbsoluteSubstractionFloat( fMockValue1, fMockValue2, &fDifference );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_FLOAT( 0, fDifference );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAbsoluteSubstractionFloat_Value1LesserThenValue2_Success()
{
    float fMockValue1 = 10, fMockValue2 = 30, fDifference;
    
    eNepError = eNepMathAbsoluteSubstractionFloat( fMockValue1, fMockValue2, &fDifference );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_FLOAT( 20, fDifference );
}
/*----------------------------------------------------------------------------*/
