/**
* @file			test_nepMathDivision.c
* @brief		Tests for the nepMathDivision library
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
#include "nepMathDivision.h"
#include "mock_nepMath.h"

/* Private define ------------------------------------------------------------*/

#define UNITY_DOUBLE_ERROR 0.0000001

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DIVISION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*------------------------------- Signed 32 bits -----------------------------*/
void test_eNepMathDivisionS32_DivideBy0_Fail()
{
    eNepError_t eResult;
    int32_t slResult;
    
	eResult = eNepMathDivisionS32( 54734576, 0, &slResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS32_NullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionS32( 54734576, 3634, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS32_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionS32( 54734576, 0, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS32_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    int32_t slResult;
    
	eResult = eNepMathDivisionS32( 666, 9, &slResult );
	TEST_ASSERT_EQUAL_INT32( 74, slResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS32( -666, 9, &slResult );
	TEST_ASSERT_EQUAL_INT32( -74, slResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS32( 666, -9, &slResult );
	TEST_ASSERT_EQUAL_INT32( -74, slResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS32( -666, -9, &slResult );
	TEST_ASSERT_EQUAL_INT32( 74, slResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/
/*---------------------------- Unsigned 32 bits ----------------------------- */
void test_eNepMathDivisionU32_DivideBy0_Fail()
{
    eNepError_t eResult;
    uint32_t ulResult;
    
	eResult = eNepMathDivisionU32( 834632, 0, &ulResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU32_NullPointer_Fail()
{
    eNepError_t eResult;
     
	eResult = eNepMathDivisionU32( 834632, 3456, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU32_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionU32( 54734576, 0, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU32_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    uint32_t ulResult;
    
	eResult = eNepMathDivisionU32( 351852, 6, &ulResult );
	TEST_ASSERT_EQUAL_UINT32( 58642, ulResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/
/* ---------------------------------- Float --------------------------------- */
void test_eNepMathDivisionFloat_InfinityDivision_Fail()
{
    eNepError_t eResult;
    float fResult;
    
    eNepMathFloatIsInfinity_ExpectAndReturn( INFINITY, eTrue );
    
	eResult = eNepMathDivisionFloat( 456735.23f, 0.0f, &fResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionFloat_NaNDivision_Fail()
{
    eNepError_t eResult;
    float fResult;
    
    eNepMathFloatIsInfinity_ExpectAndReturn( NAN, eFalse );
    eNepMathFloatIsNaN_ExpectAndReturn( NAN, eTrue );
    
	eResult = eNepMathDivisionFloat( 0.0f, 0.0f, &fResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionFloat_NullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionFloat( 2.0f, 1.0f, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionFloat_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionFloat( 2.0f, 0.0f, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionFloat_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    float fResult;
    
	eNepMathFloatIsInfinity_ExpectAndReturn( 6.9f, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( 6.9f, eFalse );
	eResult = eNepMathDivisionFloat( 30.36f, 4.4f, &fResult );
	TEST_ASSERT_EQUAL_FLOAT( 6.9f, fResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathFloatIsInfinity_ExpectAndReturn( -6.9f, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( -6.9f, eFalse );
	eResult = eNepMathDivisionFloat( -30.36f, 4.4f, &fResult );
	TEST_ASSERT_EQUAL_FLOAT( -6.9f, fResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathFloatIsInfinity_ExpectAndReturn( -6.9f, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( -6.9f, eFalse );
	eResult = eNepMathDivisionFloat( 30.36f, -4.4f, &fResult );
	TEST_ASSERT_EQUAL_FLOAT( -6.9f, fResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathFloatIsInfinity_ExpectAndReturn( 6.9f, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( 6.9f, eFalse );
	eResult = eNepMathDivisionFloat( -30.36f, -4.4f, &fResult );
	TEST_ASSERT_EQUAL_FLOAT( 6.9f, fResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/
/* ---------------------------------- Double -------------------------------- */
void test_eNepMathDivisionDouble_InfinityDivision_Fail()
{
    eNepError_t eResult;
    double fdResult;
    
    eNepMathDoubleIsInfinity_ExpectAndReturn( INFINITY, eTrue );
    
	eResult = eNepMathDivisionDouble( 456735.23, 0.0, &fdResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionDouble_NaNDivision_Fail()
{
    eNepError_t eResult;
    double fdResult;
    
    eNepMathDoubleIsInfinity_ExpectAndReturn( NAN, eFalse );
	eNepMathDoubleIsNaN_ExpectAndReturn( NAN, eTrue );
    
	eResult = eNepMathDivisionDouble( 0.0, 0.0, &fdResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionDouble_NullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionDouble( 2.0, 1.0, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionDouble_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
    eResult = eNepMathDivisionDouble( 2.0, 0.0, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionDouble_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    double fdResult;
    
	eNepMathDoubleIsInfinity_ExpectAndReturn( 6.9, eFalse );
	eNepMathDoubleIsNaN_ExpectAndReturn( 6.9, eFalse );
	eResult = eNepMathDivisionDouble( 30.36, 4.4, &fdResult );
	TEST_ASSERT_DOUBLE_WITHIN( UNITY_DOUBLE_ERROR, 6.9, fdResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDoubleIsInfinity_ExpectAndReturn( -6.9, eFalse );
	eNepMathDoubleIsNaN_ExpectAndReturn( -6.9, eFalse );
	eResult = eNepMathDivisionDouble( -30.36, 4.4, &fdResult );
	TEST_ASSERT_DOUBLE_WITHIN( UNITY_DOUBLE_ERROR, -6.9, fdResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDoubleIsInfinity_ExpectAndReturn( -6.9, eFalse );
	eNepMathDoubleIsNaN_ExpectAndReturn( -6.9, eFalse );
	eResult = eNepMathDivisionDouble( 30.36, -4.4, &fdResult );
    TEST_ASSERT_DOUBLE_WITHIN( UNITY_DOUBLE_ERROR, -6.9, fdResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDoubleIsInfinity_ExpectAndReturn( 6.9, eFalse );
	eNepMathDoubleIsNaN_ExpectAndReturn( 6.9, eFalse );
	eResult = eNepMathDivisionDouble( -30.36, -4.4, &fdResult );
    TEST_ASSERT_DOUBLE_WITHIN( UNITY_DOUBLE_ERROR, 6.9, fdResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/
/* ---------------------------- Unsigned 64 bits ---------------------------- */
void test_eNepMathDivisionU64_DivideBy0_Fail()
{
    eNepError_t eResult;
    uint64_t ullResult;
    
	eResult = eNepMathDivisionU64( 857329245475, 0, &ullResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU64_NullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionU64( 834632, 457484, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU64_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionU64( 857329245475, 0, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionU64_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    uint64_t ullResult;
    
	eResult = eNepMathDivisionU64( 35194204, 548, &ullResult );
	TEST_ASSERT_EQUAL_UINT64( 64223, ullResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/
/* ---------------------------- Signed 64 bits ------------------------------ */
void test_eNepMathDivisionS64_DivideBy0_Fail()
{
    eNepError_t eResult;
    int64_t sllResult;
    
	eResult = eNepMathDivisionS64( -35754746467, 0, &sllResult );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS64_NullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionS64( 834632, 95768, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS64_DivideBy0AndNullPointer_Fail()
{
    eNepError_t eResult;
    
	eResult = eNepMathDivisionS64( -35754746467, 0, NULL);
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathDivisionS64_DivisionAndReturn_Success()
{
    eNepError_t eResult;
    int64_t sllResult; 
    
	eResult = eNepMathDivisionS64( 234821510, 35878, &sllResult );
	TEST_ASSERT_EQUAL_INT64( 6545, sllResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS64( -234821510, 35878, &sllResult );
	TEST_ASSERT_EQUAL_INT64( -6545, sllResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS64( 234821510, -35878, &sllResult);
	TEST_ASSERT_EQUAL_INT64( -6545, sllResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathDivisionS64( -234821510, -35878, &sllResult );
	TEST_ASSERT_EQUAL_INT64( 6545, sllResult );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/