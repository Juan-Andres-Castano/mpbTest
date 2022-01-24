/**
* @file			test_mpbMathDebounce.c
* @brief
* @author		juan
* @date			Created on 2021-11-18
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2015 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include "mpbMathDebounce.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
eMpbError_t eMpbError;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void setUp()
{
	eMpbError = eUnknownError;
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
vMpbMathDebounceInit                      
*******************************************************************************/
void test_vMpbMathDebounceInit_Shall_fail_if_no_valid_pointer_is_allocated_for_Debouncing_fail()
{
	uint32_t ulMockOnCount = 5, ulMockOffCount = 10;
	eBool_t bMockValue = eTrue;
	
	eMpbError = vMpbMathDebounceInit( NULL, ulMockOnCount, ulMockOffCount, bMockValue );
	
	TEST_ASSERT_EQUAL( eInvalidParameter, eMpbError );
}
/*----------------------------------------------------------------------------*/

void test_vMpbMathDebounceInit_Shall_set_Values_GreaterThan_0_Success()
{
	MpbMathDebounce_t xMpbMathDebounce;
	uint32_t ulMockOnCount = 5, ulMockOffCount = 10;
	
	eBool_t bMockValue = eTrue;
	
	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, bMockValue );
	
	TEST_ASSERT_EQUAL_UINT32( ulMockOffCount, xMpbMathDebounce.ulOffCount );
	TEST_ASSERT_EQUAL_UINT32( ulMockOnCount, xMpbMathDebounce.ulOnCount );
	TEST_ASSERT_EQUAL_UINT32( ulMockOnCount, xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_UINT32( bMockValue, xMpbMathDebounce.bActualState );
	TEST_ASSERT_EQUAL_UINT32( bMockValue, xMpbMathDebounce.bNewProbablyState  );
}
/*----------------------------------------------------------------------------*/

void test_vMpbMathDebounceInit_Shall_run_with_initial_value_EqualTo_0_Success()
{
	MpbMathDebounce_t xMpbMathDebounce;
	uint32_t ulMockOnCount = 5, ulMockOffCount = 10;
	eBool_t bMockValue = eFalse;
	
	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, bMockValue );
	
	TEST_ASSERT_EQUAL_UINT32( ulMockOffCount, xMpbMathDebounce.ulOffCount );
	TEST_ASSERT_EQUAL_UINT32( ulMockOnCount, xMpbMathDebounce.ulOnCount );
	TEST_ASSERT_EQUAL_UINT32( ulMockOffCount, xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_UINT32( bMockValue, xMpbMathDebounce.bActualState );
	TEST_ASSERT_EQUAL_UINT32( bMockValue, xMpbMathDebounce.bNewProbablyState  );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
vMpbMathDebounceUpdate                      
*******************************************************************************/

void test_vMpbMathDebounceUpdate_Shall_fill_the_ADT_with_correct_values_Success()
{
	MpbMathDebounce_t xMpbMathDebounce;
	uint32_t ulMockOnCount = 5, ulMockOffCount = 10;
	eBool_t bMockInitialStateONValue = eTrue, bMockValue2 = eFalse, bState;
	
	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, bMockInitialStateONValue );
	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockValue2, &bState );
	
	TEST_ASSERT_EQUAL_UINT32( ulMockOffCount, xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_UINT32( bMockInitialStateONValue, xMpbMathDebounce.bActualState );
	TEST_ASSERT_EQUAL_UINT32( bMockValue2, xMpbMathDebounce.bNewProbablyState );
	TEST_ASSERT_EQUAL_UINT32( bState, xMpbMathDebounce.bActualState );
}
/*----------------------------------------------------------------------------*/

void test_vMpbMathDebounceUpdate_Shall_Debounce_the_OFF_state_At_X_OFF_repetitions_Success()
{
	MpbMathDebounce_t xMpbMathDebounce;
	uint32_t ulMockOnCount = 2, ulMockOffCount = 3;
	eBool_t bMockInitialState = eTrue, bMockOffState = eFalse, bState = eFalse;
	
	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, bMockInitialState );
	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockOffState, &bState );
	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount ), xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_INT32( bState, bMockInitialState );
	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockOffState, &bState );
	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 1 ), xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_INT32( bState, bMockInitialState );
	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockOffState, &bState );
	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount-2 ), xMpbMathDebounce.ulCount);
	TEST_ASSERT_EQUAL_INT32( bState, bMockInitialState );
	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockOffState, &bState );
	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 3 ), xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_INT32( bState, bMockInitialState );
}
/*----------------------------------------------------------------------------*/

void test_vMpbMathDebounceUpdate_OverCount_Success()
{
	MpbMathDebounce_t xMpbMathDebounce;
	uint32_t ulMockOnCount = 2, ulMockOffCount = 3;
	int32_t slMockValue1 = 1, slMockValue2 = 0, slState;
	eBool_t bMockInitialState = eTrue, bMockOffState = eFalse, bState = eFalse;
	
	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, slMockValue1 );	
	vMpbMathDebounceUpdate( &xMpbMathDebounce, bMockOffState, &bState );	
	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount ), xMpbMathDebounce.ulCount );
	TEST_ASSERT_EQUAL_INT32( bState, bMockInitialState );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 1 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 2 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 3 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue2 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( 0, xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue2 );
}
/*----------------------------------------------------------------------------*/

//void test_vMpbMathDebounceUpdate_ChangeOfConsecutiveValue_Success()
//{
//	MpbMathDebounce_t xMpbMathDebounce;
//	uint32_t ulMockOnCount = 2, ulMockOffCount = 3;
//	int32_t slMockValue1 = 1, slMockValue2 = 0, slState;
//	
//	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 1 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue1, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ulMockOffCount, xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue1, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 1 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue1, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 2 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//}
/*----------------------------------------------------------------------------*/

//void test_vMpbMathDebounceUpdate_ChangeOfStates_Success()
//{
//	MpbMathDebounce_t xMpbMathDebounce;
//	uint32_t ulMockOnCount = 2, ulMockOffCount = 3;
//	int32_t slMockValue1 = 1, slMockValue2 = 0, slState;
//	
//	vMpbMathDebounceInit( &xMpbMathDebounce, ulMockOnCount, ulMockOffCount, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 1 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 2 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue1 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue2, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOffCount - 3 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue2 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue1, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOnCount ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue2 );
//	
//	vMpbMathDebounceUpdate( &xMpbMathDebounce, slMockValue1, &slState );
//	TEST_ASSERT_EQUAL_UINT32( ( ulMockOnCount - 1 ), xMpbMathDebounce.ulCount );
//	TEST_ASSERT_EQUAL_INT32( slState, slMockValue2 );
//}
/*----------------------------------------------------------------------------*/
