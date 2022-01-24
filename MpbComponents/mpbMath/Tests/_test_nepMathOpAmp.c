/**
* @file			test_nepMathOpAmp.c
* @brief		Tests for the nepMathOpAmp library
* @author		Mikael Plouffe
* @date			Created on 2019-04-26
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

#include "nepMathOpAmp.h"
#include "mock_nepMathResistor.h"
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
	eResult = eUnknownError;
}
/*----------------------------------------------------------------------------*/

void tearDown()
{
	
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eNepMathOpAmpInitCircuit                          
*******************************************************************************/

void test_eNepMathOpAmpInitCircuit_InvalidFeedbackResistance_Fail()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000;
	float xMockPullUpVoltage = 3300;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, 0, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_InvalidPullDownResistance_Fail()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullUpResistor = 8000, ulMockFeedbackResistor = 9000;
	float xMockPullUpVoltage = 3300;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, 0, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_InvalidPullUpVoltage_Fail()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_InvalidPullUpResistance_Fail()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xMockPullUpVoltage = 3300;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockPullDownResistor, ulMockFeedbackResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_NullPointer_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xMockPullUpVoltage = 3300;
	
	eResult = eNepMathOpAmpInitCircuit( NULL, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_PullUp_Success()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xMockPullUpVoltage = 3300;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( 0, xOpAmpConfig.xGain );
	TEST_ASSERT_EQUAL_FLOAT( xMockPullUpVoltage, xOpAmpConfig.xPullUpVoltage );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullUpResistor, xOpAmpConfig.ulPullUpResistor );
	TEST_ASSERT_EQUAL_UINT32( ulMockFeedbackResistor, xOpAmpConfig.ulFeedbackResistor );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullDownResistor, xOpAmpConfig.ulPullDownResistor );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitCircuit_NoPullUp_Success()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( 0, xOpAmpConfig.xGain );
	TEST_ASSERT_EQUAL_FLOAT( 0, xOpAmpConfig.xPullUpVoltage );
	TEST_ASSERT_EQUAL_UINT32( 0, xOpAmpConfig.ulPullUpResistor );
	TEST_ASSERT_EQUAL_UINT32( ulMockFeedbackResistor, xOpAmpConfig.ulFeedbackResistor );
	TEST_ASSERT_EQUAL_UINT32( ulMockPullDownResistor, xOpAmpConfig.ulPullDownResistor );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
eNepMathOpAmpInitGain                              
*******************************************************************************/

void test_eNepMathOpAmpInitGain_InvalidGain_Fail()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	float xMockGain = 0.0f;
	
	eResult = eNepMathOpAmpInitGain( &xOpAmpConfig, xMockGain );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitGain_NullPointer_Fail()
{
	float xMockGain = 1.2f;
	
	eResult = eNepMathOpAmpInitGain( NULL, xMockGain );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpInitGain_Success()
{
	xNepMathOpAmpConfig_t xOpAmpConfig;
	float xMockGain = 1.2f;
	
	eResult = eNepMathOpAmpInitGain( &xOpAmpConfig, xMockGain );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockGain, xOpAmpConfig.xGain );
	TEST_ASSERT_EQUAL_FLOAT( 0, xOpAmpConfig.xPullUpVoltage );
	TEST_ASSERT_EQUAL_UINT32( 0, xOpAmpConfig.ulPullUpResistor );
	TEST_ASSERT_EQUAL_UINT32( 0, xOpAmpConfig.ulFeedbackResistor );
	TEST_ASSERT_EQUAL_UINT32( 0, xOpAmpConfig.ulPullDownResistor );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
eNepMathOpAmpGetInputVoltage                           
*******************************************************************************/

void test_eNepMathOpAmpGetInputVoltage_NullPointer_Fail()
{
	float xInputVoltage, xMockOutputVoltage = 5.7f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, NULL, &xInputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, NULL, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModeNoPullUp_eNepMathResistorFloatVoltageDividerGetVout_Fail()
{
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xInputVoltage, xMockOutputVoltage = 5.7f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorFloatVoltageDividerGetVout_ExpectAndReturn( ulMockFeedbackResistor, ulMockPullDownResistor, xMockOutputVoltage, &xInputVoltage, eUnknownError );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModeNoPullUp_Success()
{
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockInputVoltage = 3.16f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorFloatVoltageDividerGetVout_ExpectAndReturn( ulMockFeedbackResistor, ulMockPullDownResistor, xMockOutputVoltage, &xInputVoltage, eSuccess );
	eNepMathResistorFloatVoltageDividerGetVout_ReturnThruPtr_pxOutputVoltage( &xMockInputVoltage );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockInputVoltage, xInputVoltage );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModePullUp_eNepMathDivisionFloatForOutputCurrent_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockPullUpVoltage = 3.3f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, ulMockFeedbackResistor, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModePullUp_eNepMathDivisionFloatForPullUpCurrent_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockPullUpVoltage = 3.3f, xMockOutputCurrent = 0.000633f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockOutputCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModePullUp_eNepMathResistorGetEquivalentInParallelPullDownFeedback_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockPullUpVoltage = 3.3f, xMockOutputCurrent = 0.000633f, xMockPullUpCurrent = 0.0004125f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockOutputCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullUpCurrent );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eUnknownError );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModePullUp_eNepMathResistorGetEquivalentInParallelPullUpEquivalent_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockPullUpVoltage = 3.3f, xMockOutputCurrent = 0.000633f, xMockPullUpCurrent = 0.000413f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockOutputCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullUpCurrent );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eUnknownError );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_CircuitModePullUp_Success()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214, ulMockEquivalentResistor = 2292;
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockPullUpVoltage = 3.3f, xMockOutputCurrent = 0.000633f, xMockPullUpCurrent = 0.000413f, xMockInputVoltage = 2.397f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockOutputCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullUpCurrent );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockEquivalentResistor );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( xMockInputVoltage, xInputVoltage );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_GainMode_eNepMathDivisionFloat_Fail()
{
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockGain = 1.2f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitGain( &xOpAmpConfig, xMockGain );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, xMockGain, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetInputVoltage_GainMode_Success()
{
	float xInputVoltage, xMockOutputVoltage = 5.7f, xMockGain = 1.2f, xMockInputVoltage = 4.75f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitGain( &xOpAmpConfig, xMockGain );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockOutputVoltage, xMockGain, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockInputVoltage );
	
	eResult = eNepMathOpAmpGetInputVoltage( xMockOutputVoltage, &xOpAmpConfig, &xInputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockInputVoltage, xInputVoltage );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
eNepMathOpAmpGetOutputVoltage                          
*******************************************************************************/

void test_eNepMathOpAmpGetOutputVoltage_NullPointer_Fail()
{
	float xOutputVoltage, xMockInputVoltage = 3.16f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	/* pxOpAmpConfig NULL */
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, NULL, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	/* pxOutputVoltage NULL */
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	/* pxOpAmpConfig & pxOutputVoltage NULL */
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, NULL, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModeNoPullUp_eNepMathResistorFloatVoltageDividerGetVin_Fail()
{
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xOutputVoltage, xMockInputVoltage = 3.16f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorFloatVoltageDividerGetVin_ExpectAndReturn( ulMockFeedbackResistor, ulMockPullDownResistor, xMockInputVoltage, &xOutputVoltage, eUnknownError );
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModeNoPullUp_Success()
{
	uint32_t ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xOutputVoltage, xMockInputVoltage = 3.16f, xMockOutputVoltage = 5.7f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, 0, ulMockFeedbackResistor, ulMockPullDownResistor, 0 );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorFloatVoltageDividerGetVin_ExpectAndReturn( ulMockFeedbackResistor, ulMockPullDownResistor, xMockInputVoltage, &xOutputVoltage, eSuccess );
	eNepMathResistorFloatVoltageDividerGetVin_ReturnThruPtr_pxInputVoltage( &xMockOutputVoltage );
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockOutputVoltage, xOutputVoltage );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModePullUp_eNepMathResistorGetEquivalentInParallelPullDownFeedback_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000;
	float xOutputVoltage, xMockInputVoltage = 2.397f, xMockPullUpVoltage = 3.3f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eUnknownError );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModePullUp_eNepMathResistorGetEquivalentInParallelEquivalentPullDown_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214;
	float xOutputVoltage, xMockInputVoltage = 2.397f, xMockPullUpVoltage = 3.3f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eUnknownError );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModePullUp_eNepMathDivisionFloatForPullUpCurrent_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214, ulMockEquivalentResistor = 2292;
	float xOutputVoltage, xMockInputVoltage = 2.397f, xMockPullUpVoltage = 3.3f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockEquivalentResistor );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModePullUp_eNepMathDivisionFloatForInputCurrent_Fail()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214, ulMockEquivalentResistor = 2292;
	float xOutputVoltage, xMockInputVoltage = 2.397f, xMockPullUpVoltage = 3.3f, xMockPullUpCurrent = 0.000413f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockEquivalentResistor );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullUpCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockInputVoltage, ulMockEquivalentResistor, NULL, eUnknownError );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_CircuitModePullUp_Success()
{
	uint32_t ulMockPullUpResistor = 8000, ulMockPullDownResistor = 5000, ulMockFeedbackResistor = 9000, ulMockPullDownFeedbackEquivalentResistor = 3214, ulMockEquivalentResistor = 2292;
	float xOutputVoltage, xMockInputVoltage = 2.397f, xMockPullUpVoltage = 3.3f, xMockPullUpCurrent = 0.000413f, ulMockInputCurrent = 0.001046f, xMockOutputVoltage = 5.697f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitCircuit( &xOpAmpConfig, ulMockPullUpResistor, ulMockFeedbackResistor, ulMockPullDownResistor, xMockPullUpVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownResistor, ulMockFeedbackResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockPullDownFeedbackEquivalentResistor );
	
	eNepMathResistorGetEquivalentInParallel_ExpectAndReturn( ulMockPullDownFeedbackEquivalentResistor, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathResistorGetEquivalentInParallel_IgnoreArg_pulEquivalentResistor();
	eNepMathResistorGetEquivalentInParallel_ReturnThruPtr_pulEquivalentResistor( &ulMockEquivalentResistor );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockPullUpVoltage, ulMockPullUpResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &xMockPullUpCurrent );
	
	eNepMathDivisionFloat_ExpectAndReturn( xMockInputVoltage, ulMockEquivalentResistor, NULL, eSuccess );
	eNepMathDivisionFloat_IgnoreArg_pfResult();
	eNepMathDivisionFloat_ReturnThruPtr_pfResult( &ulMockInputCurrent );
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockOutputVoltage, xOutputVoltage );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathOpAmpGetOutputVoltage_GainMode_Success()
{
	float xOutputVoltage, xMockInputVoltage = 4.75f, xMockGain = 1.2f, xMockOutputVoltage = 5.7f;
	xNepMathOpAmpConfig_t xOpAmpConfig;
	
	eResult = eNepMathOpAmpInitGain( &xOpAmpConfig, xMockGain );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathOpAmpGetOutputVoltage( xMockInputVoltage, &xOpAmpConfig, &xOutputVoltage );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL_FLOAT( xMockOutputVoltage, xOutputVoltage );
}
/*----------------------------------------------------------------------------*/