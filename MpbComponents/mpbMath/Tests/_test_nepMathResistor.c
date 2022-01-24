/**
* @file			test_nepMathResistor.c
* @brief		Tests for the nepMathResistor library
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

#include "nepMathResistor.h"
#include "mock_nepMathDivision.h"
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
	eResult = eDriverError;
}

void tearDown()
{
	
}

/******************************************************************************/
/*                     eNepMathResistorVoltageDividerGetVout                  */
/******************************************************************************/

void test_eNepMathResistorVoltageDividerGetVoutNULLpulOutputVoltageReturnError_fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, *pulOutputVoltage = NULL;
	
	eResult = eNepMathResistorVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, ulMockInputVoltage, pulOutputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetVout_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, ulOutputVoltage;
	
	eNepMathDivisionU32_ExpectAndReturn( 1000000, 200, &ulOutputVoltage, eUnknownError );
	
	eResult = eNepMathResistorVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, ulMockInputVoltage, &ulOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetVout_Success()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, ulOutputVoltage;
	
	eNepMathDivisionU32_ExpectAndReturn( 1000000, 200, &ulOutputVoltage, eSuccess );
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockOutputVoltage );
	
	eResult = eNepMathResistorVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, ulMockInputVoltage, &ulOutputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockOutputVoltage, ulOutputVoltage );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                      eNepMathResistorVoltageDividerGetVin                  */
/******************************************************************************/

void test_eNepMathResistorVoltageDividerGetVinNULLpulInputVoltageReturnError_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockOutputVoltage = 5000, *pulInputVoltage = NULL;
	
	eResult = eNepMathResistorVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, ulMockOutputVoltage, pulInputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetVin_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockOutputVoltage = 5000, ulInputVoltage;
	
	eNepMathDivisionU32_ExpectAndReturn( 1000000, 100, &ulInputVoltage, eUnknownError );
	
	eResult = eNepMathResistorVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, ulMockOutputVoltage, &ulInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetVin_Success()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100, ulMockOutputVoltage = 5000, ulMockInputVoltage = 10000, ulInputVoltage;
	
	eNepMathDivisionU32_ExpectAndReturn( 1000000, 100, &ulInputVoltage, eSuccess );
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockInputVoltage );
	
	eResult = eNepMathResistorVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, ulMockOutputVoltage, &ulInputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockInputVoltage, ulInputVoltage );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                eNepMathResistorVoltageDividerGetPullUpResistor             */
/******************************************************************************/

void test_eNepMathResistorVoltageDividerGetPullUpResistor_NullPointer_Fail()
{
	uint32_t ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000;
	
	eResult = eNepMathResistorVoltageDividerGetPullUpResistor( ulMockPullDownResistor, ulMockInputVoltage, ulMockOutputVoltage, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetPullUpResistor_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, ulPullUpResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( ulMockInputVoltage, ulMockOutputVoltage, NULL, eUnknownError );
	eNepMathDivisionU32_IgnoreArg_pulResult();
	
	eResult = eNepMathResistorVoltageDividerGetPullUpResistor( ulMockPullDownResistor, ulMockInputVoltage, ulMockOutputVoltage, &ulPullUpResistor );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetPullUpResistor_Success()
{
	uint32_t ulMockPullDownResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, ulMockPullUpResistor = 100, ulDivisionResult = 2, ulPullUpResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( ulMockInputVoltage, ulMockOutputVoltage, NULL, eSuccess );
	eNepMathDivisionU32_IgnoreArg_pulResult();
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulDivisionResult );
	
	eResult = eNepMathResistorVoltageDividerGetPullUpResistor( ulMockPullDownResistor, ulMockInputVoltage, ulMockOutputVoltage, &ulPullUpResistor );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullUpResistor, ulPullUpResistor );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*               eNepMathResistorVoltageDividerGetPullDownResistor            */
/******************************************************************************/

void test_eNepMathResistorVoltageDividerGetPullDownResistor_NullPointer_Fail()
{
	uint32_t ulMockPullupResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, *pulPullDownResistor = NULL;
		
	eResult = eNepMathResistorVoltageDividerGetPullDownResistor( ulMockPullupResistor, ulMockInputVoltage, ulMockOutputVoltage, pulPullDownResistor );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

void test_eNepMathResistorVoltageDividerGetPullDownResistor_OutputVoltageSuperiorThanInputVoltage_Fail()
{
	uint32_t ulMockPullupResistor = 100, ulMockInputVoltage = 5000, ulMockOutputVoltage = 10000, *pulPullDownResistor = NULL;
		
	eResult = eNepMathResistorVoltageDividerGetPullDownResistor( ulMockPullupResistor, ulMockInputVoltage, ulMockOutputVoltage, pulPullDownResistor );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetPullDownResistor_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullupResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, ulPullDownResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( 500000, 5000, &ulPullDownResistor, eUnknownError );
	
	eResult = eNepMathResistorVoltageDividerGetPullDownResistor( ulMockPullupResistor, ulMockInputVoltage, ulMockOutputVoltage, &ulPullDownResistor );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorVoltageDividerGetPullDownResistor_Success()
{
	uint32_t ulMockPullupResistor = 100, ulMockInputVoltage = 10000, ulMockOutputVoltage = 5000, ulMockPullDownResistor = 100, ulPullDownResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( 500000, 5000, &ulPullDownResistor, eSuccess );
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockPullDownResistor );
	
	eResult = eNepMathResistorVoltageDividerGetPullDownResistor( ulMockPullupResistor, ulMockInputVoltage, ulMockOutputVoltage, &ulPullDownResistor );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullDownResistor, ulPullDownResistor );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                   eNepMathResistorFloatVoltageDividerGetVout               */
/******************************************************************************/

void test_eNepMathResistorFloatVoltageDividerGetVout_NullPointer_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockInputVoltage = 10000.5f, *pxOutputVoltage = NULL;
		
	eResult = eNepMathResistorFloatVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, xMockInputVoltage, pxOutputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetVout_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockInputVoltage = 10000.5f, xOutputVoltage;
	
	eNepMathDivisionFloat_ExpectAndReturn( 1000050.0f, 200.0f, &xOutputVoltage, eUnknownError );
	
	eResult = eNepMathResistorFloatVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, xMockInputVoltage, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetVout_Success()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f, xOutputVoltage;
	
	eNepMathDivisionFloat_ExpectAndReturn( 1000050.0f, 200.0f, &xOutputVoltage, eSuccess );
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockOutputVoltage );
	
	eResult = eNepMathResistorFloatVoltageDividerGetVout( ulMockPullUpResistor, ulMockPullDownResistor, xMockInputVoltage, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockOutputVoltage, xOutputVoltage );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                   eNepMathResistorFloatVoltageDividerGetVin                */
/******************************************************************************/

void test_eNepMathResistorFloatVoltageDividerGetVin_NullPointer_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockOutputVoltage = 5000.25f, *pxInputVoltage = NULL;
		
	eResult = eNepMathResistorFloatVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, xMockOutputVoltage, pxInputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetVin_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockOutputVoltage = 5000.25f, xInputVoltage;
	
	eNepMathDivisionFloat_ExpectAndReturn( 1000050.0f, 100.0f, &xInputVoltage, eUnknownError );
	
	eResult = eNepMathResistorFloatVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, xMockOutputVoltage, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetVin_Success()
{
	uint32_t ulMockPullUpResistor = 100, ulMockPullDownResistor = 100;
	float xMockOutputVoltage = 5000.25f, xMockInputVoltage = 10000.5f, xInputVoltage;
	
	eNepMathDivisionFloat_ExpectAndReturn( 1000050.0f, 100.0f, &xInputVoltage, eSuccess );
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockInputVoltage );
	
	eResult = eNepMathResistorFloatVoltageDividerGetVin( ulMockPullUpResistor, ulMockPullDownResistor, xMockOutputVoltage, &xInputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockInputVoltage, xInputVoltage );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*             eNepMathResistorFloatVoltageDividerGetPullUpResistor           */
/******************************************************************************/

void test_eNepMathResistorFloatVoltageDividerGetPullUpResistor_NullPointer_Fail()
{
	uint32_t ulMockPullDownResistor = 100;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f;
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullUpResistor( ulMockPullDownResistor, xMockInputVoltage, xMockOutputVoltage, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetPullUpResistor_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullDownResistor = 100, ulPullUpResistor;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f;
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockInputVoltage, xMockOutputVoltage, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullUpResistor( ulMockPullDownResistor, xMockInputVoltage, xMockOutputVoltage, &ulPullUpResistor );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetPullUpResistor_Success()
{
	uint32_t ulMockPullDownResistor = 100, ulPullUpResistor;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f, xDivisionResult = 2.0f;
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockInputVoltage, xMockOutputVoltage, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xDivisionResult );
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullUpResistor( ulMockPullDownResistor, xMockInputVoltage, xMockOutputVoltage, &ulPullUpResistor );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullDownResistor, ulPullUpResistor );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*             eNepMathResistorFloatVoltageDividerGetPullDownResistor         */
/******************************************************************************/

void test_eNepMathResistorFloatVoltageDividerGetPullDownResistor_NullPointer_Fail()
{
	uint32_t ulMockPullupResistor = 100, *pulPullDownResistor = NULL;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f;
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullDownResistor( ulMockPullupResistor, xMockInputVoltage, xMockOutputVoltage, pulPullDownResistor );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetPullDownResistor_OutputVoltageSuperiorThanInputVoltage_Fail()
{
	uint32_t ulMockPullupResistor = 100, ulPullDownResistor;
	float xMockInputVoltage = 5000.5f, xMockOutputVoltage = 10000.25f;
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullDownResistor( ulMockPullupResistor, xMockInputVoltage, xMockOutputVoltage, &ulPullDownResistor );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetPullDownResistor_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockPullupResistor = 100, ulPullDownResistor;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f;
	
	eNepMathDivisionFloat_ExpectAndReturn( 500025.0f, 5000.25f, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullDownResistor( ulMockPullupResistor, xMockInputVoltage, xMockOutputVoltage, &ulPullDownResistor );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorFloatVoltageDividerGetPullDownResistor_Success()
{
	uint32_t ulMockPullupResistor = 100, ulPullDownResistor;
	float xMockInputVoltage = 10000.5f, xMockOutputVoltage = 5000.25f, xMockPullDownResistor = 100.0f;
	
	eNepMathDivisionFloat_ExpectAndReturn( 500025.0f, 5000.25f, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullDownResistor );
	
	eResult = eNepMathResistorFloatVoltageDividerGetPullDownResistor( ulMockPullupResistor, xMockInputVoltage, xMockOutputVoltage, &ulPullDownResistor );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( xMockPullDownResistor, ulPullDownResistor );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                      eNepMathResistorGetEquivalentInParallel               */
/******************************************************************************/

void test_eNepMathResistorGetEquivalentInParallel_NullPointer_Fail()
{
	uint32_t ulMockResistor1 = 100, ulMockResistor2 = 100, *pulEquivalentResistor = NULL;
		
	eResult = eNepMathResistorGetEquivalentInParallel( ulMockResistor1, ulMockResistor2, pulEquivalentResistor );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorGetEquivalentInParallel_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockResistor1 = 100, ulMockResistor2 = 100, ulEquivalentResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( 10000, 200, &ulEquivalentResistor, eUnknownError );
	
	eResult = eNepMathResistorGetEquivalentInParallel( ulMockResistor1, ulMockResistor2, &ulEquivalentResistor );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorGetEquivalentInParallel_Success()
{
	uint32_t ulMockResistor1 = 100, ulMockResistor2 = 100, ulMockEquivalentResistor = 50, ulEquivalentResistor;
	
	eNepMathDivisionU32_ExpectAndReturn( 10000, 200, &ulEquivalentResistor, eSuccess );
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockEquivalentResistor );
	
	eResult = eNepMathResistorGetEquivalentInParallel( ulMockResistor1, ulMockResistor2, &ulEquivalentResistor );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockEquivalentResistor, ulEquivalentResistor );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                      eNepMathResistorGetResistorInParallel                 */
/******************************************************************************/

void test_eNepMathResistorGetResistorInParallel_NullPointer_Fail()
{
	uint32_t ulMockResistor1 = 100, ulMockEquivalentResistor = 50, *pulResistor2 = NULL;
		
	eResult = eNepMathResistorGetResistorInParallel( ulMockEquivalentResistor, ulMockResistor1, pulResistor2 );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorGetResistorInParallel_EquivalentResistorSuperiorThanResistot1_Fail()
{
	uint32_t ulMockResistor1 = 50, ulMockEquivalentResistor = 100, *pulResistor2 = NULL;
		
	eResult = eNepMathResistorGetResistorInParallel( ulMockEquivalentResistor, ulMockResistor1, pulResistor2 );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}

/*----------------------------------------------------------------------------*/

void test_eNepMathResistorGetResistorInParallel_eNepMathDivisionU32_Fail()
{
	uint32_t ulMockResistor1 = 100, ulMockEquivalentResistor = 50, ulResistor2;
	
	eNepMathDivisionU32_ExpectAndReturn( 5000, 50, &ulResistor2, eUnknownError );
	
	eResult = eNepMathResistorGetResistorInParallel( ulMockEquivalentResistor, ulMockResistor1, &ulResistor2 );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathResistorGetResistorInParallel_Success()
{
	uint32_t ulMockResistor1 = 100, ulMockEquivalentResistor = 50, ulMockResistor2 = 100, ulResistor2;
	
	eNepMathDivisionU32_ExpectAndReturn( 5000, 50, &ulResistor2, eSuccess );
	eNepMathDivisionU32_ReturnThruPtr_pulResult( &ulMockResistor2 );
	
	eResult = eNepMathResistorGetResistorInParallel( ulMockEquivalentResistor, ulMockResistor1, &ulResistor2 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_UINT32( ulMockResistor2, ulResistor2 );
}
/*----------------------------------------------------------------------------*/