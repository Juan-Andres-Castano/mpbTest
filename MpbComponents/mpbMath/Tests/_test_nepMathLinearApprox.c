/**
* @file			test_nepMathLinearApprox.c
* @brief		Tests for the nepMathLinearApprox library
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
#include "nepMathLinearApprox.h"
#include "nepMathDivision.h"
#include "mock_nepMath.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int32_t slResult;
static float xResultFloat;
static int64_t sllResult;
static eNepError_t eResult;
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ LINEAR APPROXIMATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*------------------------------ Signed 64 bits ------------------------------*/
void test_eNepMathLinearApproxS64_SlopeOf0_Success()
{
	eResult = eNepMathLinearApproxS64( 2, 10, 8, 10, 5, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 10, sllResult, "Test S64 Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerce Slope Of 0, Return Fail" );
	
	eResult = eNepMathLinearApproxS64( 2, 10, 8, 10, 5, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 10, sllResult, "Test S64 NO Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 No Coerce Slope Of 0, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_UndefinedSlope_Fail()
{
	eResult = eNepMathLinearApproxS64( 4, 2, 4, 8, 5, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S64 Coerce Undefined Slope, Return Fail" );
	
	eResult = eNepMathLinearApproxS64( 4, 2, 4, 8, 5, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S64 No Coerce Undefined Slope, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_NullPointer_Fail()
{
	eResult = eNepMathLinearApproxS64( 2, 10, 8, 10, 5, eNepMathCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S64 Coerce Null Pointer, Return Fail" );
	
	eResult = eNepMathLinearApproxS64( 2, 10, 8, 10, 5, eNepMathNoCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S64 No Coerce Null Pointer, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_CoercedValues_Success()
{
	/* Positive slope, first quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS64( 50, 400, 200, 1000, 250, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 1000, sllResult,"Test S64 Coerced Value, Positive slope, first quadrant, 1X < 2X & over Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Coerced Value, Positive slope, first quadrant, 1X < 2X & over Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS64( 200, 1000, 50, 400, 250, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 1000, sllResult, "Test S64 Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, first quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS64( 50, 400, 200, 1000, 5, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 400, sllResult, "Test S64 Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS64( 200, 1000, 50, 400, 5, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 400, sllResult, "Test S64 Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS64( -56789, 500, -45678, 5000, -5000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 5000, sllResult, "Test S64 Coerced Value,Positive slope, second quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X < 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS64( -45678, 5000, -56789, 500, -5000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 5000, sllResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS64( -56789, 500, -45678, 5000, -100000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 500, sllResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS64( -45678, 5000, -56789, 500, -100000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 500, sllResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Positive slope, second quadrant, 1X > 2X & under, Return Fail" );
	
	/* Negative slope, third quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS64( -98223, -50, -45678, -87654, 0, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -87654, sllResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS64( -45678, -87654, -98223, -50, 0, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -87654, sllResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS64( -106854, -785, -26734, -408456, -267865, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -785, sllResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS64( -26734, -408456, -106854, -785, -267865, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -785, sllResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS64( 5, -150, 8900, -6788, 9999, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -6788, sllResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS64( 8900, -6788, 5, -150, 9999, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -6788, sllResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS64( 56, -543, 7655, -37654, -378, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -543, sllResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS64( 7655, -37654, 56, -543, -378, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -543, sllResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_PositiveSlopeCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 50, 400, 200, 1000, 126, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 704, sllResult, "Test S64 Positive Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 200, 1000, 50, 400, 126, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 704, sllResult, "Test S64 Positive Slope Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -56789, 500, -45678, 5000, -48569, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 3829, sllResult, "Test S64 Positive Slope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -45678, 5000, -56789, 500, -48569, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 3829, sllResult, "Test S64 Positive Slope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -56789, -98765, -45678, -87654, -50000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -91976, sllResult, "Test S64 Positive Slope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -45678, -87654, -56789, -98765, -50000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -91976, sllResult, "Test S64 Positive Slope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 600, -98765, 4000, -46789, 2678, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -66998, sllResult, "Test S64 Positive Slope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 4000, -46789, 600, -98765, 2678, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -66998, sllResult, "Test S64 Positive Slope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -200, 50, 200, 4000, 50, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2519, sllResult, "Test S64 Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 200, 4000, -200, 50, 50, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2519, sllResult, "Test S64 Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -6077, -400, -60, 2950, -3605, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 976, sllResult, "Test S64 Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -60, 2950, -6077, -400, -3605, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 976, sllResult, "Test S64 Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -380, -8000, 500, -1200, 278, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2915, sllResult, "Test S64 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 500, -1200, -380, -8000, 278, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2915, sllResult, "Test S64 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 60, -1260, 1200, 8000, 780, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 4588, sllResult, "Test S64 Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 1200, 8000, 60, -1260, 780, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 4588, sllResult, "Test S64 Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -300, -4000, 1500, 6000, 46, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2078, sllResult, "Test S64 Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -300, -4000, 1500, 6000, 46, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2078, sllResult, "Test S64 Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_NegativeSlopeCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 30, 1000, 300, 50, 159, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 546, sllResult, "Test S64 Negative Slpope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 300, 50, 30, 1000, 159, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 546, sllResult, "Test S64 Negative Slpope Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -25000, 50000, -50, 1600, -6784, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 14663, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -50, 1600, -25000, 50000, -6784, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 14663, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -199999, -8000, -19999, -80000, -100000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -48000, sllResult, "Test S64 Negative Slpope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -19999, -80000, -199999, -8000, -100000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -48000, sllResult, "Test S64 Negative Slpope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 1, -1, 99999, -66667, 50000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -33334, sllResult, "Test S64 Negative Slpope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 99999, -66667, 1, -1, 50000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -33334, sllResult, "Test S64 Negative Slpope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -600, 10000, 150, 20, 0, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2016, sllResult, "Test S64 Negative Slpope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 150, 20, -600, 10000, 0, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2016, sllResult, "Test S64 Negative Slpope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -10000, 5000, -50, -10000, -5000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2538, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -50, -10000, -10000, 5000, -5000, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -2538, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -5333, -3555, 3555, -5333, 20, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -4626, sllResult, "Test S64 Negative Slpope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -5333, -3555, 3555, -5333, 20, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -4626, sllResult, "Test S64 Negative Slpope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 10, 100, 500, -5000, 178, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -1649, sllResult, "Test S64 Negative Slpope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 500, -5000, 10, 100, 178, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -1649, sllResult, "Test S64 Negative Slpope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -1000, 25, 750, -250, -40, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -126, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 750, -250, -1000, 25, -40, eNepMathCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -126, sllResult, "Test S64 Negative Slpope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slpope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_PositiveSlopeNotCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 50, 400, 200, 1000, 300, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 1400, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 200, 1000, 50, 400, 300, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 1400, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -56789, 500, -45678, 5000, -5000, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 21475, sllResult, "Test S64 Positive Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -45678, 5000, -56789, 500, -5000, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 21475, sllResult, "Test S64 Positive Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -56789, -98765, -45678, -87654, -6666, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -48642, sllResult, "Test S64 Positive Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -45678, -87654, -56789, -98765, -6666, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -48642, sllResult, "Test S64 Positive Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 600, -98765, 4000, -46789, 56, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -107081, sllResult, "Test S64 Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 4000, -46789, 600, -98765, 56, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -107081, sllResult, "Test S64 Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -200, 50, 200, 4000, 560, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 7555, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 200, 4000, -200, 50, 560, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 7555, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -6077, -400, -60, 2950, 24, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2997, sllResult, "Test S64 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -60, 2950, -6077, -400, 24, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 2997, sllResult, "Test S64 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -380, -8000, 500, -1200, -500, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -8927, sllResult, "Test S64 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 500, -1200, -380, -8000, -500, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -8927, sllResult, "Test S64 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 60, -1260, 1200, 8000, 1678, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 11883, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 1200, 8000, 60, -1260, 1678, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 11883, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -300, -4000, 1500, 6000, -600, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -5667, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -300, -4000, 1500, 6000, -600, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -5667, sllResult, "Test S64 Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS64_NegativeSlopeNotCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 30, 1000, 300, 50, 437, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -432, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 300, 50, 30, 1000, 437, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -432, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -25000, 50000, -50, 1600, -30000, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 59699, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -50, 1600, -25000, 50000, -30000, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 59699, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -199999, -8000, -19999, -80000, 0, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -88000, sllResult, "Test S64 Negative Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -19999, -80000, -199999, -8000, 0, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -88000, sllResult, "Test S64 Negative Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 1, -1, 99999, -66667, 123456, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -82305, sllResult, "Test S64 Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 99999, -66667, 1, -1, 123456, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -82305, sllResult, "Test S64 Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -600, 10000, 150, 20, 246, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -1257, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 150, 20, -600, 10000, 246, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -1257, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -10000, 5000, -50, -10000, -22004, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 23096, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -50, -10000, -10000, 5000, -22004, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 23096, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -5333, -3555, 3555, -5333, 4503, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -5523, sllResult, "Test S64 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( -5333, -3555, 3555, -5333, 4503, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -5523, sllResult, "Test S64 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( 10, 100, 500, -5000, 1899, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -19561, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 500, -5000, 10, 100, 1899, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( -19561, sllResult, "Test S64 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS64( -1000, 25, 750, -250, -3401, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 402, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS64( 750, -250, -1000, 25, -3401, eNepMathNoCoerce, &sllResult );
	TEST_ASSERT_EQUAL_INT64_MESSAGE( 402, sllResult, "Test S64 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S64 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

/*------------------------------ Signed 32 bits ------------------------------*/
void test_eNepMathLinearApproxS32_SlopeOf0_Success()
{
	eResult = eNepMathLinearApproxS32( 2, 10, 8, 10, 5, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 10, slResult, "Test S32 Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerce Slope Of 0, Return Fail" );
	
	eResult = eNepMathLinearApproxS32( 2, 10, 8, 10, 5, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 10, slResult, "Test S32 No Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 No Coerce Slope Of 0, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_UndefinedSlope_Fail()
{
	eResult = eNepMathLinearApproxS32( 4, 2, 4, 8, 5, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S32 Coerce Undefined Slope, Return Fail" );
	
	eResult = eNepMathLinearApproxS32( 4, 2, 4, 8, 5, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S32 No Coerce Undefined Slope, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_NullPointer_Fail()
{
	eResult = eNepMathLinearApproxS32( 2, 10, 8, 10, 5, eNepMathCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S32 Coerce Null Pointer, Return Fail" );
	
	eResult = eNepMathLinearApproxS32( 2, 10, 8, 10, 5, eNepMathNoCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test S32 No Coerce Null Pointer, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_CoercedValues_Success()
{
	/* Positive slope, first quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS32( 50, 400, 200, 1000, 250, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 1000, slResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X < 2X & over, Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS32( 200, 1000, 50, 400, 250, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 1000, slResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, first quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS32( 50, 400, 200, 1000, 5, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 400, slResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS32( 200, 1000, 50, 400, 5, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 400, slResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS32( -56789, 500, -45678, 5000, -5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 5000, slResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X < 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS32( -45678, 5000, -56789, 500, -5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 5000, slResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS32( -56789, 500, -45678, 5000, -100000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 500, slResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS32( -45678, 5000, -56789, 500, -100000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 500, slResult, "Test S32 Coerced Value, Positive slope, second quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult , "Test S32 Coerced Value, Positive slope, second quadrant, 1X > 2X & under, Return Fail");
	
	/* Negative slope, third quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS32( -98223, -50, -45678, -87654, 0, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -87654, slResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS32( -45678, -87654, -98223, -50, 0, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -87654, slResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS32( -106854, -785, -26734, -408456, -267865, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -785, slResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS32( -26734, -408456, -106854, -785, -267865, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -785, slResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxS32( 5, -150, 8900, -6788, 9999, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -6788, slResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxS32( 8900, -6788, 5, -150, 9999, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -6788, slResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxS32( 56, -543, 7655, -37654, -378, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -543, slResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxS32( 7655, -37654, 56, -543, -378, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -543, slResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_PositiveSlopeCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 50, 400, 200, 1000, 126, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 704, slResult, "Test S32 Positive Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 200, 1000, 50, 400, 126, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 704, slResult, "Test S32 Positive Slope Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -56789, 500, -45678, 5000, -48569, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 3829, slResult, "Test S32 Positive Slope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -45678, 5000, -56789, 500, -48569, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 3829, slResult, "Test S32 Positive Slope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -56789, -98765, -45678, -87654, -50000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -91976, slResult, "Test S32 Positive Slope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -45678, -87654, -56789, -98765, -50000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -91976, slResult, "Test S32 Positive Slope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 600, -98765, 4000, -46789, 2678, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -66998, slResult, "Test S32 Positive Slope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 4000, -46789, 600, -98765, 2678, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -66998, slResult, "Test S32 Positive Slope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -200, 50, 200, 4000, 50, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2519, slResult, "Test S32 Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 200, 4000, -200, 50, 50, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2519, slResult, "Test S32 Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -6077, -400, -60, 2950, -3605, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 976, slResult, "Test S32 Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -60, 2950, -6077, -400, -3605, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 976, slResult, "Test S32 Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -380, -8000, 500, -1200, 278, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2915, slResult, "Test S32 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 500, -1200, -380, -8000, 278, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2915, slResult, "Test S32 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 60, -1260, 1200, 8000, 780, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 4588, slResult, "Test S32 Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 1200, 8000, 60, -1260, 780, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 4588, slResult, "Test S32 Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -300, -4000, 1500, 6000, 46, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2078, slResult, "Test S32 Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -300, -4000, 1500, 6000, 46, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2078, slResult, "Test S32 Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_NegativeSlopeCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 30, 1000, 300, 50, 159, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 546, slResult, "Test S32 Negative Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 300, 50, 30, 1000, 159, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 546, slResult, "Test S32 Negative Slope Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -25000, 50000, -50, 1600, -6784, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 14663, slResult, "Test S32 Negative Slope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -50, 1600, -25000, 50000, -6784, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 14663, slResult, "Test S32 Negative Slope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -19999, -800, -1999, -8000, -10000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -4800, slResult, "Test S32 Negative Slope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -1999, -8000, -19999, -800, -10000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -4800, slResult, "Test S32 Negative Slope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 1, -1, 9999, -66667, 5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -33334, slResult, "Test S32 Negative Slope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 9999, -66667, 1, -1, 5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -33334, slResult, "Test S32 Negative Slope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -600, 10000, 150, 20, 0, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2016, slResult, "Test S32 Negative Slope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 150, 20, -600, 10000, 0, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2016, slResult, "Test S32 Negative Slope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -10000, 5000, -50, -10000, -5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2538, slResult, "Test S32 Negative Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -50, -10000, -10000, 5000, -5000, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -2538, slResult, "Test S32 Negative Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -5333, -3555, 3555, -5333, 20, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -4626, slResult, "Test S32 Negative Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -5333, -3555, 3555, -5333, 20, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -4626, slResult, "Test S32 Negative Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 10, 100, 500, -5000, 178, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -1649, slResult, "Test S32 Negative Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 500, -5000, 10, 100, 178, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -1649, slResult, "Test S32 Negative Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -1000, 25, 750, -250, -40, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -126, slResult, "Test S32 Negative Slope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 750, -250, -1000, 25, -40, eNepMathCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -126, slResult, "Test S32 Negative Slope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_PositiveSlopeNotCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 50, 400, 200, 1000, 300, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 1400, slResult, "Test S32 Positive Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 200, 1000, 50, 400, 300, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 1400, slResult, "Test S32 Positive Slope Not Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -56789, 500, -45678, 5000, -5000, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 21475, slResult, "Test S32 Positive Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -45678, 5000, -56789, 500, -5000, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 21475, slResult, "Test S32 Positive Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -56789, -98765, -45678, -87654, -6666, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -48642, slResult, "Test S32 Positive Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -45678, -87654, -56789, -98765, -6666, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -48642, slResult, "Test S32 Positive Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 600, -98765, 4000, -46789, 56, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -107081, slResult, "Test S32 Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 4000, -46789, 600, -98765, 56, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -107081, slResult, "Test S32 Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -200, 50, 200, 4000, 560, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 7555, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 200, 4000, -200, 50, 560, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 7555, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -6077, -400, -60, 2950, 24, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2997, slResult, "Test S32 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -60, 2950, -6077, -400, 24, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 2997, slResult, "Test S32 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -380, -8000, 500, -1200, -500, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -8927, slResult, "Test S32 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 500, -1200, -380, -8000, -500, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -8927, slResult, "Test S32 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 60, -1260, 1200, 8000, 1678, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 11883, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 1200, 8000, 60, -1260, 1678, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 11883, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -300, -4000, 1500, 6000, -600, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -5667, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -300, -4000, 1500, 6000, -600, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -5667, slResult, "Test S32 Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxS32_NegativeSlopeNotCoerced_Success()
{
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 30, 1000, 300, 50, 437, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -432, slResult, "Test S32 Negative Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 300, 50, 30, 1000, 437, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -432, slResult, "Test S32 Negative Slope Not Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -25000, 50000, -50, 1600, -30000, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 59699, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -50, 1600, -25000, 50000, -30000, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 59699, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -19999, -800, -1999, -8000, 0, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -8800, slResult, "Test S32 Negative Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -1999, -8000, -19999, -800, 0, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -8800, slResult, "Test S32 Negative Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 1, -1, 9999, -66667, 12345, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -82310, slResult, "Test S32 Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 9999, -66667, 1, -1, 12345, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -82310, slResult, "Test S32 Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -600, 10000, 150, 20, 246, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -1257, slResult, "Test S32 Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 150, 20, -600, 10000, 246, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -1257, slResult, "Test S32 Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -10000, 5000, -50, -10000, -22004, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 23096, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -50, -10000, -10000, 5000, -22004, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 23096, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -5333, -3555, 3555, -5333, 4503, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -5523, slResult, "Test S32 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( -5333, -3555, 3555, -5333, 4503, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -5523, slResult, "Test S32 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( 10, 100, 500, -5000, 1899, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -19561, slResult, "Test S32 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 500, -5000, 10, 100, 1899, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( -19561, slResult, "Test S32 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxS32( -1000, 25, 750, -250, -3401, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 402, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxS32( 750, -250, -1000, 25, -3401, eNepMathNoCoerce, &slResult );
	TEST_ASSERT_EQUAL_INT32_MESSAGE( 402, slResult, "Test S32 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test S32 Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------- Float ----------------------------------*/
void test_eNepMathLinearApproxFloat_SlopeOf0_Success()
{
	eNepMathFloatIsInfinity_ExpectAndReturn( 0, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( 0, eFalse );
	eResult = eNepMathLinearApproxFloat( 16.43f, 78.87f, 12674.75f, 78.87f, 43.65f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 78.87f, xResultFloat, "Test Float Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerce Slope Of 0, Return Fail" );
	
	eNepMathFloatIsInfinity_ExpectAndReturn( 0, eFalse );
	eNepMathFloatIsNaN_ExpectAndReturn( 0, eFalse );
	eResult = eNepMathLinearApproxFloat( 16.43f, 78.87f, 12674.75f, 78.87f, 43.65f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 78.87f, xResultFloat, "Test Float No Coerce Slope Of 0, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float No Coerce Slope Of 0, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_UndefinedSlope_Fail()
{
	eResult = eNepMathLinearApproxFloat( 33.99f, 567.45f, 33.99f, 1067.67f, 34.56f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test Float Coerce Undefined Slope, Return Fail" );
	
	eResult = eNepMathLinearApproxFloat( 33.99f, 567.45f, 33.99f, 1067.67f, 34.56f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test Float No Coerce Undefined Slope, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_NullPointer_Fail()
{
	eResult = eNepMathLinearApproxFloat( 16.43f, 78.87f, 12674.75f, 78.87f, 43.65f, eNepMathCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test Float Coerce Null Pointer, Return Fail" );
	
	eResult = eNepMathLinearApproxFloat( 216.43f, 78.87f, 12674.75f, 78.87f, 43.65f, eNepMathNoCoerce, NULL );
	TEST_ASSERT_EQUAL_MESSAGE( eInvalidParameter, eResult, "Test Float No Coerce Null Pointer, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_CoercedValues_Success()
{
	/* Positive slope, first quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxFloat( 26.78f, 456.94f, 236.19f, 1007.1f, 348.58f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 1007.10f, xResultFloat, "Test Float Coerced Value, Positive slope, first quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, first quadrant, 1X < 2X & over, Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxFloat( 236.19f, 1007.1f, 26.78f, 456.94f, 348.58f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 1007.10f, xResultFloat, "Test Float Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, first quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, first quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxFloat( 89.96f, 270.98f, 400.65f, 894.54f, 43.87f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 270.98f, xResultFloat, "Test Float Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, first quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, first quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxFloat( 400.65f, 894.54f, 89.96f, 270.98f, 43.87f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 270.98f, xResultFloat, "Test Float Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, first quadrant, 1X > 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxFloat( -48765.67f, 487.98f, -39543.45f, 5103.45f, -45.67f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 5103.45f, xResultFloat, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxFloat( -39543.45f, 5103.45f, -48765.67f, 487.98f, -45.67f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 5103.45f, xResultFloat, "Test Float Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, second quadrant, 1X > 2X & over, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxFloat( -47684.23, 492.33f, -36987.22f, 5502.45f, -123456.78f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 492.33f, xResultFloat, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Return Fail" );
	
	/* Positive slope, second quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxFloat( -36987.22f, 5502.45f, -47684.23, 492.33f, -123456.78f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 492.33f, xResultFloat, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Positive slope, second quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, third quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxFloat( -90564.20f, -120.67f, -60234.12f, -25364.54f, 0.74f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -25364.54f, xResultFloat, "Test Float Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, third quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxFloat( -60234.12f, -25364.54f, -90564.20f, -120.67f, 0.74f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -25364.54f, xResultFloat, "Test Float Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, third quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, third quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxFloat( -94556.09f, -57.98f, -41288.23f, -72834.88f, -99999.99f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -57.98f, xResultFloat, "Test Float Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, third quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, third quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxFloat( -41288.23f, -72834.88f, -94556.09f, -57.98f, -99999.99f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -57.98f, xResultFloat, "Test Float Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, third quadrant, 1X > 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & over */
	eResult = eNepMathLinearApproxFloat( 5093.45f, -25.80f, 256944.76f, -409543.45f, 555555.55f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -409543.45f, xResultFloat, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X < 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & over */
	eResult = eNepMathLinearApproxFloat( 256944.76f, -409543.45f, 5093.45f, -25.80f, 555555.55f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -409543.45f, xResultFloat, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X > 2X & over, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X < 2X & under */
	eResult = eNepMathLinearApproxFloat( 2222.22f, -90.30f, 343583.44f, -802345.86f, 0.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -90.30f, xResultFloat, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X < 2X & under, Return Fail" );
	
	/* Negative slope, fourth quadrant, 1X > 2X & under */
	eResult = eNepMathLinearApproxFloat( 343583.44f, -802345.86f, 2222.22f, -90.30f, 0.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -90.30f, xResultFloat, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Coerced Value, Negative slope, fourth quadrant, 1X > 2X & under, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_PositiveSlopeCoerced_Success()
{
	/* At this point, the division function is validated and the mocked */
	/* functions are both used once per call so, we just ignore that and */
	/* return false (no infinity or NaN division here). */
	eNepMathFloatIsInfinity_IgnoreAndReturn( eFalse );
	eNepMathFloatIsNaN_IgnoreAndReturn( eFalse );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 40.87f, 387.94f, 207.12f, 1032.65f, 102.46f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 626.78f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 207.12f, 1032.65f, 40.87f, 387.94f, 102.46f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 626.78f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -56789.65f, 386.34f, -39775.33f, 7935.50f, -40000.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 7835.81f, xResultFloat, "Test Float Positive Slope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -39775.33f, 7935.50f, -56789.65f, 386.34f, -40000.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 7835.81f, xResultFloat, "Test Float Positive Slope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -107583.66f, -150872.30f, -29753.40f, -58763.44f, -69298.55f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -105563.00f, xResultFloat, "Test Float Positive Slope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -29753.40f, -58763.44f, -107583.66f, -150872.30f, -69298.55f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -105563.00f, xResultFloat, "Test Float Positive Slope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 829.09f, -265932.3f, 74392.55f, -1986.03f, 68923.66f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -21608.40f, xResultFloat, "Test Float Positive Slope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 74392.55f, -1986.03f, 829.09f, -265932.3f, 68923.66f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -21608.40f, xResultFloat, "Test Float Positive Slope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -675.34, 2.6f, 3000.59f, 1835.8f, 590.87f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 634.06f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3000.59f, 1835.8f, -675.34, 2.6f, 590.87f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 634.06f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -65.34f, -2304.50f, -2.90f, 5923.44f, -30.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 2352.38f, xResultFloat, "Test Float Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -2.90f, 5923.44f, -65.34f, -2304.50f, -30.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 2352.38f, xResultFloat, "Test Float Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -1777.77f, -9832.65f, 77.77f, -564.10f, -600.49f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -3952.06f, xResultFloat, "Test Float Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 77.77f, -564.10f, -1777.77f, -9832.65f, -600.49f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -3952.06f, xResultFloat, "Test Float Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 70.70f, -8080.80f , 3434.34f, 121212.12f, 2323.23f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 78502.80f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3434.34f, 121212.12f, 70.70f, -8080.80f , 2323.23f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 78502.80f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -309.45f, -309.45f, 1500.10f, 3084.90f, 479.80f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 1171.02f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 1500.10f, 3084.90f, -309.45f, -309.45f, 479.80f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 1171.02f, xResultFloat, "Test Float Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_NegativeSlopeCoerced_Success()
{
	/* At this point, the division function is validated and the mocked */
	/* functions are both used once per call so, we just ignore that and return */
	/* false (no infinity or NaN division here). */
	eNepMathFloatIsInfinity_IgnoreAndReturn( eFalse );
	eNepMathFloatIsNaN_IgnoreAndReturn( eFalse );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 5060.33f, 509.50f, 30045.38f, 156.78f, 12778.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 400.55f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 30045.38f, 156.78f, 5060.33f, 509.50f, 12778.00f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 400.55f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -345902.45f, 80543.30f, -45987.54f, 20344.65f, -167324.78f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 44699.40f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -345902.45f, 80543.30f, -45987.54f, 20344.65f, -167324.78f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 44699.40f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -196399.88f, -8000.44f, -12499.88f, -80450.44f, -100670.22f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -45714.51f, xResultFloat, "Test Float Negative Slope Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -12499.88f, -80450.44f, -196399.88f, -8000.44f, -100670.22f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -45714.51f, xResultFloat, "Test Float Negative Slope Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 0.00f, 0.00f, 55555.55f, -7733.55f, 33333.99f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -4640.22f, xResultFloat, "Test Float Negative Slope Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 55555.55f, -7733.55f, 0.00f, 0.00f, 33333.99f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -4640.22f, xResultFloat, "Test Float Negative Slope Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -677.45f, 16543.34f, 1090.70f, 45.39f, -137.13f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 11501.80f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 1090.70f, 45.39f, -677.45f, 16543.34f, -137.13f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 11501.80f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -12999.12f, 3033.33f, -789.44f, -8039.43f, -5423.11f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -3837.23f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -789.44f, -8039.43f, -12999.12f, 3033.33f, -5423.11f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -3837.23f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -6755.32f, -2873.12f, 3875.90f, -10564.29f, -2065.23f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -6266.17f, xResultFloat, "Test Float Negative Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3875.90f, -10564.29f, -6755.32f, -2873.12f, -2065.23f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -6266.17f, xResultFloat, "Test Float Negative Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 2.67f, 158.34f, 9564.33f, -4927.66f, 4873.21f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2432.38f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 9564.33f, -4927.66f, 2.67f, 158.34f, 4873.21f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2432.38f, xResultFloat, "Test Float Negative Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -1222.87f, -2482.61f, 15032.79f, -7834.32f, 25.25f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2893.52f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 15032.79f, -7834.32f, -1222.87f, -2482.61f, 25.25f, eNepMathCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2893.52f, xResultFloat, "Test Float Negative Slope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_PositiveSlopeNotCoerced_Success()
{
	/* At this point, the division function is validated and the mocked */
	/* functions are both used once per call so, we just ignore that and */
	/* return false (no infinity or NaN division here). */
	eNepMathFloatIsInfinity_IgnoreAndReturn( eFalse );
	eNepMathFloatIsNaN_IgnoreAndReturn( eFalse );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 40.87f, 387.94f, 207.12f, 1032.65f, 5.23f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 249.73f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 207.12f, 1032.65f, 40.87f, 387.94f, 5.23f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 249.73f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -56789.65f, 386.34f, -39775.33f, 7935.50f, -20493.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 16490.8f, xResultFloat, "Test Float Positive Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -39775.33f, 7935.50f, -56789.65f, 386.34f, -20493.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 16490.8f, xResultFloat, "Test Float Positive Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -107583.66f, -150872.30f, -29753.40f, -58763.44f, -111111.11f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -155047.34f, xResultFloat, "Test Float Positive Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -29753.40f, -58763.44f, -107583.66f, -150872.30f, -111111.11f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -155047.34f, xResultFloat, "Test Float Positive Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 829.09f, -265932.3f, 74392.55f, -1986.03f, 84345.62f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 33725.7f, xResultFloat, "Test Float Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 74392.55f, -1986.03f, 829.09f, -265932.3f, 84345.62f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 33725.7f, xResultFloat, "Test Float Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -675.34, 2.6f, 3000.59f, 1835.8f, -900.5f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -109.688f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3000.59f, 1835.8f, -675.34, 2.6f, -900.5f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -109.688f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -65.34f, -2304.50f, -2.90f, 5923.44f, -102.55f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -7207.79f, xResultFloat, "Test Float Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -2.90f, 5923.44f, -65.34f, -2304.50f, -102.55f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -7207.79f, xResultFloat, "Test Float Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -1777.77f, -9832.65f, 77.77f, -564.10f, 150.56f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -200.508f, xResultFloat, "Test Float Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 77.77f, -564.10f, -1777.77f, -9832.65f, 150.56f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -200.508f, xResultFloat, "Test Float Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 70.70f, -8080.80f , 3434.34f, 121212.12f, 48.78f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -8923.37f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3434.34f, 121212.12f, 70.70f, -8080.80f , 48.78f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -8923.37f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -309.45f, -309.45f, 1500.10f, 3084.90f, 1789.32f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 3627.42f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 1500.10f, 3084.90f, -309.45f, -309.45f, 1789.32f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 3627.42f, xResultFloat, "Test Float Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Positive Slope Not Coerced, First quadrant and third quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathLinearApproxFloat_NegativeSlopeNotCoerced_Success()
{
	/* At this point, the division function is validated and the mocked */
	/* functions are both used once per call so, we just ignore that and return */
	/* false (no infinity or NaN division here). */
	eNepMathFloatIsInfinity_IgnoreAndReturn( eFalse );
	eNepMathFloatIsNaN_IgnoreAndReturn( eFalse );
	
	/* First quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 5060.33f, 509.50f, 30045.38f, 156.78f, 0.0f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 580.938f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 30045.38f, 156.78f, 5060.33f, 509.50f, 0.0f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 580.938f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -345902.45f, 80543.30f, -45987.54f, 20344.65f, -39734.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 19089.5f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -345902.45f, 80543.30f, -45987.54f, 20344.65f, -39734.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 19089.5f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -196399.88f, -8000.44f, -12499.88f, -80450.44f, -200000.0f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -6582.12f, xResultFloat, "Test Float Negative Slope Not Coerced, Third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Third quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -12499.88f, -80450.44f, -196399.88f, -8000.44f, -200000.0f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -6582.12f, xResultFloat, "Test Float Negative Slope Not Coerced, Third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Third quadrant, 1X > 2X, Return Fail" );
	
	/* Fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 0.00f, 0.00f, 55555.55f, -7733.55f, -6008.60f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 836.421f, xResultFloat, "Test Float Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 55555.55f, -7733.55f, 0.00f, 0.00f, -6008.60f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 836.421f, xResultFloat, "Test Float Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -677.45f, 16543.34f, 1090.70f, 45.39f, 1200.99f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -983.684f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant and second quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and second quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 1090.70f, 45.39f, -677.45f, 16543.34f, 1200.99f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -983.684f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant and second quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -12999.12f, 3033.33f, -789.44f, -8039.43f, -15634.82f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 5423.6f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant and third quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and third quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( -789.44f, -8039.43f, -12999.12f, 3033.33f, -15634.82f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 5423.6f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant and third quadrant, 1X > 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -6755.32f, -2873.12f, 3875.90f, -10564.29f, -7297.08f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2481.18f, xResultFloat, "Test Float Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Third quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 3875.90f, -10564.29f, -6755.32f, -2873.12f, -7297.08f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -2481.18f, xResultFloat, "Test Float Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Third quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( 2.67f, 158.34f, 9564.33f, -4927.66f, -45.54f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 183.984f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* First quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 9564.33f, -4927.66f, 2.67f, 158.34f, -45.54f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( 183.984f, xResultFloat, "Test Float Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, First quadrant and fourth quadrant, 1X > 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X < 2X */
	eResult = eNepMathLinearApproxFloat( -1222.87f, -2482.61f, 15032.79f, -7834.32f, -6356.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -792.562f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X < 2X, Return Fail" );
	
	/* Second quadrant and fourth quadrant, 1X > 2X */
	eResult = eNepMathLinearApproxFloat( 15032.79f, -7834.32f, -1222.87f, -2482.61f, -6356.34f, eNepMathNoCoerce, &xResultFloat );
	TEST_ASSERT_EQUAL_FLOAT_MESSAGE( -792.562f, xResultFloat, "Test Float Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Value Fail" );
	TEST_ASSERT_EQUAL_MESSAGE( eSuccess, eResult, "Test Float Negative Slope Not Coerced, Second quadrant and fourth quadrant, 1X > 2X, Return Fail" );
}
/*----------------------------------------------------------------------------*/
