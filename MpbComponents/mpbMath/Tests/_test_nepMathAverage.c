/**
* @file         test_nepMathAverage.c
* @brief        Tests for the nepMathAverage library
* @author       Mikael Plouffe
* @date         Created on 2019-04-25
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
#include "nepMathAverage.h"

#include "mock_nepMathDivision.h"
#include "mock_nepMath.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static eNepError_t eResult;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void setUp()
{
    eResult = eUnknownError;
}
/*----------------------------------------------------------------------------*/

void tearDown()
{
	
}
/*----------------------------------------------------------------------------*/
/******************************************************************************
eNepMathAverageS32                      
*******************************************************************************/

void test_eNepMathAverageS32_InvalidParameter_Fail()
{
    int32_t slMockArray[ 5 ] = { 0 };
    uint16_t usMockLength = 5;
    int32_t slResult;
    
    /* pslArray */
    eResult = eNepMathAverageS32( NULL, usMockLength, &slResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pslArray & usLength */
    eResult = eNepMathAverageS32( NULL, 0, &slResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pslArray & usLength & pslResult */
    eResult = eNepMathAverageS32( NULL, 0, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* usLength */
    eResult = eNepMathAverageS32( &slMockArray[ 0 ], 0, &slResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* usLength & pslResult */
    eResult = eNepMathAverageS32( &slMockArray[ 0 ], 0, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pslResult */
    eResult = eNepMathAverageS32( &slMockArray[ 0 ], usMockLength, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAverageS32_eNepMathDivisionS64_Fail()
{
    int32_t slMockArray[ 5 ] = { -15, -10, 0, 20, 30 };
    uint16_t usMockLength = 5;
    int32_t slResult;
    
    eNepMathDivisionS64_ExpectAndReturn( 25, usMockLength, NULL, eUnknownError );
    eNepMathDivisionS64_IgnoreArg_psllResult();
    
    eResult = eNepMathAverageS32( &slMockArray[ 0 ], usMockLength, &slResult );
    TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAverageS32_Success()
{
    int32_t slMockArray[ 5 ] = { -15, -10, 0, 20, 30 };
    uint16_t usMockLength = 5;
    int32_t slResult;
    int64_t sllMockResult = 5;
    
    eNepMathDivisionS64_ExpectAndReturn( 25, usMockLength, NULL, eSuccess );
    eNepMathDivisionS64_IgnoreArg_psllResult();
    eNepMathDivisionS64_ReturnThruPtr_psllResult( &sllMockResult );
    
    eResult = eNepMathAverageS32( &slMockArray[ 0 ], usMockLength, &slResult );
    TEST_ASSERT_EQUAL( eSuccess, eResult );
    TEST_ASSERT_EQUAL_INT64( sllMockResult, slResult );
}

/******************************************************************************
eNepMathAverageFloat                      
*******************************************************************************/
void test_eNepMathAverageFloat_InvalidParam_Fail()
{
    float xMockArray[ 5 ] = { 0 };
    uint16_t usMockLength = 5;
    float xResult;
    
    /* pxArray */
    eResult = eNepMathAverageFloat( NULL, usMockLength, &xResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pxArray & usLength */
    eResult = eNepMathAverageFloat( NULL, 0, &xResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pxArray & usLength & pxResult */
    eResult = eNepMathAverageFloat( NULL, 0, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* usLength */
    eResult = eNepMathAverageFloat( &xMockArray[ 0 ], 0, &xResult );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* usLength & pxResult */
    eResult = eNepMathAverageFloat( &xMockArray[ 0 ], 0, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
    
    /* pxResult */
    eResult = eNepMathAverageFloat( &xMockArray[ 0 ], usMockLength, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAverageFloat_eNepMathDivisionFloat_Fail()
{
    float xMockArray[ 5 ] = { -15.54, -10.10f, 0.6f, 20.71f, 30.35f };
    uint16_t usMockLength = 5;
    float xResult;
    
    eNepMathDivisionDouble_ExpectAndReturn( 26.02f, usMockLength, NULL, eUnknownError );
    eNepMathDivisionDouble_IgnoreArg_pfdResult();
    
    eResult = eNepMathAverageFloat( xMockArray, usMockLength, &xResult );
    TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathAverageFloat_Success()
{
    float xMockArray[ 5 ] = { -15.54, -10.10f, 0.6f, 20.71f, 30.35f };
    uint16_t usMockLength = 5;
    float xResult;
    double xMockResult = 5.21f;
    
    eNepMathDivisionDouble_ExpectAndReturn( 26.02f, usMockLength, NULL, eSuccess );
    eNepMathDivisionDouble_IgnoreArg_pfdResult();
    eNepMathDivisionDouble_ReturnThruPtr_pfdResult( &xMockResult );
    
    eResult = eNepMathAverageFloat( xMockArray, usMockLength, &xResult );
    TEST_ASSERT_EQUAL( eSuccess, eResult );
    TEST_ASSERT_EQUAL_FLOAT( xMockResult, xResult );
}
/*----------------------------------------------------------------------------*/
