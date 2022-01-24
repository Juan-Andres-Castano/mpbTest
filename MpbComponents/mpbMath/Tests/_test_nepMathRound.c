/**
* @file			test_nepMathRound.c
* @brief		Tests for the nepMathRound library
* @author		Mikael Plouffe
* @date			Created on 2019-04-25
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
#include "nepMathRound.h"
#include "mock_nepMathDivision.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void setUp()
{
    
}

void tearDown()
{
	
}
/*----------------------------------------------------------------------------*/
/*------------------------------- Signed 32 bits -----------------------------*/
void test_eNepMathRoundToPrecisionS32_InvalidParameter_Fail()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockPrecision = 10;
	
	eResult = eNepMathRoundToPrecisionS32( NULL, ulMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS32_eNepMathDivisionS32_Fail()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockPrecision = 10;
	int32_t slMockValue      = 26;
	
    eNepMathDivisionS32_ExpectAnyArgsAndReturn(eInvalidParameter);
	
	eResult = eNepMathRoundToPrecisionS32( &slMockValue, ulMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS32_Positive_Success()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockPrecision = 10;
	int32_t slMockValue      = 26; 
    int32_t slMockResult     = 3;
	
	eNepMathDivisionS32_ExpectAndReturn( slMockValue, ulMockPrecision, NULL, eSuccess );
	eNepMathDivisionS32_IgnoreArg_pslResult();
	eNepMathDivisionS32_ReturnThruPtr_pslResult( &slMockResult );
	
	eResult = eNepMathRoundToPrecisionS32( &slMockValue, ulMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_INT32( 30, slMockValue );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS32_Negative_Success()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockPresicion = 10;
	int32_t slMockValue      = -260; 
    int32_t slMockResult     = -20;
	
	eNepMathDivisionS32_ExpectAndReturn( slMockValue, ulMockPresicion, NULL, eSuccess );
	eNepMathDivisionS32_IgnoreArg_pslResult();
	eNepMathDivisionS32_ReturnThruPtr_pslResult( &slMockResult );
	
	eResult = eNepMathRoundToPrecisionS32( &slMockValue, ulMockPresicion );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_INT32( -200, slMockValue );
}
/*----------------------------------------------------------------------------*/
/*----------------------------- Unsigned 32 bits -----------------------------*/

void test_eNepMathRoundToPrecisionU32_InvalidParameter_Fail()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockPrecision = 10;
	
	eResult = eNepMathRoundToPrecisionU32( NULL, ulMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionU32_eNepMathDivisionU32_Fail()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockValue     = 26;
    uint32_t ulMockPrecision = 10;
	
    eNepMathDivisionU32_ExpectAnyArgsAndReturn(eInvalidParameter);
	
	eResult = eNepMathRoundToPrecisionU32( &ulMockValue, ulMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionU32_Success()
{
    eNepError_t eResult      = eUnknownError;
	uint32_t ulMockValue     = 264586;
    uint32_t ulMockPrecision = 10000; 
    uint32_t ulMockResult    = 26;
	
	eNepMathDivisionU32_ExpectAndReturn( ulMockValue, ulMockPrecision, NULL, eSuccess );
	eNepMathDivisionU32_IgnoreArg_pulResult();
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockResult );
	
	eResult = eNepMathRoundToPrecisionU32( &ulMockValue, ulMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( 260000, ulMockValue );
}

/*----------------------------------------------------------------------------*/
/*------------------------------- Signed 64 bits -----------------------------*/

void test_eNepMathRoundToPrecisionS64_InvalidParameter_Fail()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 10;
	
	eResult = eNepMathRoundToPrecisionS64( NULL, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS32_eNepMathDivisionS64_Fail()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 1000000;
	int64_t sllMockValue      = 987654321;
	
    eNepMathDivisionS64_ExpectAnyArgsAndReturn(eInvalidParameter);
	
	eResult = eNepMathRoundToPrecisionS64( &sllMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS64_Positive_Success()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 1000000;
	int64_t sllMockValue      = 987654321; 
    int64_t sllMockResult     = 988;
	
	eNepMathDivisionS64_ExpectAndReturn( sllMockValue, ullMockPrecision, NULL, eSuccess );
	eNepMathDivisionS64_IgnoreArg_psllResult();
	eNepMathDivisionS64_ReturnThruPtr_psllResult( &sllMockResult );
	
	eResult = eNepMathRoundToPrecisionS64( &sllMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_INT64( 988000000, sllMockValue );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionS64_Negative_Success()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 1000000;
	int64_t sllMockValue      = -123456789;
    int64_t sllMockResult     = -123;
	
	eNepMathDivisionS64_ExpectAndReturn( sllMockValue, ullMockPrecision, NULL, eSuccess );
	eNepMathDivisionS64_IgnoreArg_psllResult();
	eNepMathDivisionS64_ReturnThruPtr_psllResult( &sllMockResult );
	
	eResult = eNepMathRoundToPrecisionS64( &sllMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_INT64( -123000000, sllMockValue );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eNepMathRoundToPrecisionU64                      
*******************************************************************************/
void test_eNepMathRoundToPrecisionU64_InvalidParameter_Fail()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 10;
	
	eResult = eNepMathRoundToPrecisionU64( NULL, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionU64_eNepMathDivisionU64_Fail()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockValue     = 9876543210;
    uint64_t ullMockPrecision = 10000;
	
    eNepMathDivisionU64_ExpectAnyArgsAndReturn(eInvalidParameter);
	
	eResult = eNepMathRoundToPrecisionU64( &ullMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionU64_Success()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockValue     = 9876543210; 
    uint64_t ullMockPrecision = 100000; 
    uint64_t ullMockResult    = 98765;
	
	eNepMathDivisionU64_ExpectAndReturn( ullMockValue, ullMockPrecision, NULL, eSuccess );
	eNepMathDivisionU64_IgnoreArg_pullResult();
	eNepMathDivisionU64_ReturnThruPtr_pullResult( &ullMockResult );
	
	eResult = eNepMathRoundToPrecisionU64( &ullMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT64( 9876500000, ullMockValue );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
eNepMathRoundToPrecisionFloat                      
*******************************************************************************/

void test_eNepMathRoundToPrecisionFloat_InvalidParameter_Fail()
{
    eNepError_t eResult       = eUnknownError;
	uint64_t ullMockPrecision = 10;
	
	eResult = eNepMathRoundToPrecisionFloat( NULL, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionUFloat_eNepMathDivisionFloat_Fail()
{
    eNepError_t eResult       = eUnknownError;
	float fMockValue          = 9876543210.0;
    uint64_t ullMockPrecision = 10000;
	
    eNepMathDivisionFloat_ExpectAnyArgsAndReturn(eInvalidParameter);
	
	eResult = eNepMathRoundToPrecisionFloat( &fMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathRoundToPrecisionFloat_Success()
{
    eNepError_t eResult       = eUnknownError;
	float fMockValue          = 9876543210; 
    uint64_t ullMockPrecision = 100000; 
    float fMockResult         = 98765;
	
	eNepMathDivisionFloat_ExpectAndReturn( fMockValue, ullMockPrecision, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &fMockResult );
	
	eResult = eNepMathRoundToPrecisionFloat( &fMockValue, ullMockPrecision );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( 9876500000, fMockValue );
}
/*----------------------------------------------------------------------------*/