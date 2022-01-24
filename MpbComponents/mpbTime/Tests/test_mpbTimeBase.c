/**
* @file			test_mpbTimeBase.c
* @brief
* @author		juan
* @date			Created on 2021-11-17
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
**/
/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include "mpblibs.h"
#include "mpbTimeBase.h"
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
	
}
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
	
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eMpbTimeBaseInit                      
*******************************************************************************/

void test_eMpbTimeBaseInit_InvalidParam_Fail()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 2;
	
	eMpbError = eMpbTimeBaseInit( NULL, 0 );
	TEST_ASSERT_EQUAL( eInvalidParameter, eMpbError );
	
	eMpbError = eMpbTimeBaseInit( NULL, ucMockTickPerMs );
	TEST_ASSERT_EQUAL( eInvalidParameter, eMpbError );
	
	eMpbError = eMpbTimeBaseInit( &xTimeBase, 0 );
	TEST_ASSERT_EQUAL( eInvalidParameter, eMpbError );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseInit_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 2;
	
	eMpbError = eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	
	TEST_ASSERT_EQUAL( eSuccess, eMpbError );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulTick );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulMs );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulSecond );
	TEST_ASSERT_EQUAL_UINT16( 1000, xTimeBase.usMsCount );
	TEST_ASSERT_EQUAL_UINT8( ucMockTickPerMs, xTimeBase.ucTickCount );
	TEST_ASSERT_EQUAL_UINT8( ucMockTickPerMs, xTimeBase.ucTickReload );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eMpbTimeBaseTick                     
*******************************************************************************/

void test_eMpbTimeBaseTick_InvalidParam_Fail()
{

	eMpbError = eMpbTimeBaseTick( NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eMpbError );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseTick_2TickPerMs_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 2;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );

	eMpbError = eMpbTimeBaseTick( &xTimeBase );
	
	TEST_ASSERT_EQUAL( eSuccess, eMpbError );
	TEST_ASSERT_EQUAL_UINT32( 1, xTimeBase.ulTick );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulMs );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulSecond );
	TEST_ASSERT_EQUAL_UINT16( 1000, xTimeBase.usMsCount );
	TEST_ASSERT_EQUAL_UINT8( ( ucMockTickPerMs - 1 ), xTimeBase.ucTickCount );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseTick_1TickPerMs_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );

	eMpbError = eMpbTimeBaseTick( &xTimeBase );
	
	TEST_ASSERT_EQUAL( eSuccess, eMpbError );
	TEST_ASSERT_EQUAL_UINT32( 1, xTimeBase.ulTick );
	TEST_ASSERT_EQUAL_UINT32( 1, xTimeBase.ulMs );
	TEST_ASSERT_EQUAL_UINT32( 0, xTimeBase.ulSecond );
	TEST_ASSERT_EQUAL_UINT16( ( 1000 - 1 ), xTimeBase.usMsCount );
	TEST_ASSERT_EQUAL_UINT8( ucMockTickPerMs, xTimeBase.ucTickCount );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseTick_1Second_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 1000;
	
	eMpbError = eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );

	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbError = eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL( eSuccess, eMpbError );
	TEST_ASSERT_EQUAL_UINT32( 1000, xTimeBase.ulTick );
	TEST_ASSERT_EQUAL_UINT32( 1000, xTimeBase.ulMs );
	TEST_ASSERT_EQUAL_UINT32( 1, xTimeBase.ulSecond );
	TEST_ASSERT_EQUAL_UINT16( 1000, xTimeBase.usMsCount );
	TEST_ASSERT_EQUAL_UINT8( ucMockTickPerMs, xTimeBase.ucTickCount );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulMpbTimeBaseGetTick                     
*******************************************************************************/

void test_ulMpbTimeBaseGetTick_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 40;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 40, ulMpbTimeBaseGetTick( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulMpbTimeBaseGetMs                     
*******************************************************************************/

void test_ulMpbTimeBaseGetMs_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 2;
	uint32_t ulTickCount = 40;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 20, ulMpbTimeBaseGetMs( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulMpbTimeBaseGetSecond                     
*******************************************************************************/

void test_ulMpbTimeBaseGetSecond_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 2000;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 2, ulMpbTimeBaseGetSecond( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulMpbTimeBaseGetMinute                     
*******************************************************************************/

void test_ulMpbTimeBaseGetMinute_0minute_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 59000;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 0, ulMpbTimeBaseGetMinute( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/

void test_ulMpbTimeBaseGetMinute_1minute_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 60000;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 1, ulMpbTimeBaseGetMinute( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/

void test_ulMpbTimeBaseGetMinute_2minutes_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 142000;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 2, ulMpbTimeBaseGetMinute( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulMpbTimeBaseGetHour                     
*******************************************************************************/

void test_ulMpbTimeBaseGetHour_0Hour_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 10;
	
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 0, ulMpbTimeBaseGetHour( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/

void test_ulMpbTimeBaseGetHour_1Hour_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 1;
	
	/* Cheat tick count because test is too long otherwise */
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	xTimeBase.ulTick = 3599999;
	xTimeBase.ulMs = 3599999;
	xTimeBase.ulSecond = 3599;
	xTimeBase.usMsCount = 1;
	
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 1, ulMpbTimeBaseGetHour( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/

void test_ulMpbTimeBaseGetHour_MoreThen1Hour_Success()
{
	mpbTimeBase_t xTimeBase;
	uint8_t ucMockTickPerMs = 1;
	uint32_t ulTickCount = 1;
	
	/* Cheat tick count because test is too long otherwise */
	eMpbTimeBaseInit( &xTimeBase, ucMockTickPerMs );
	xTimeBase.ulTick = 3799000;
	xTimeBase.ulMs = 3799000;
	xTimeBase.ulSecond = 3799;
	
	for( uint32_t ulI = 0; ulI < ulTickCount; ulI++ )
	{
		eMpbTimeBaseTick( &xTimeBase );
	}
	
	TEST_ASSERT_EQUAL_UINT32( 1, ulMpbTimeBaseGetHour( &xTimeBase ) );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
eMpbTimeBaseIsDelayDone                     
*******************************************************************************/

void test_eMpbTimeBaseIsDelayDone_eTrue_Success()
{
	eBool_t eDelayCompleted;
	uint32_t ulMockCounter = 2000, ulMockTimeStamp = 1000;
	
	eDelayCompleted = eMpbTimeBaseIsDelayDone( ulMockCounter, ulMockTimeStamp );
	
	TEST_ASSERT_EQUAL( eTrue, eDelayCompleted );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseIsDelayDone_eFalse_Success()
{
	eBool_t eDelayCompleted;
	uint32_t ulMockCounter = 44575, ulMockTimeStamp = 48477;
	
	eDelayCompleted = eMpbTimeBaseIsDelayDone( ulMockCounter, ulMockTimeStamp );
	
	TEST_ASSERT_EQUAL( eFalse, eDelayCompleted );
}
/*----------------------------------------------------------------------------*/

void test_eMpbTimeBaseIsDelayDone_eFalse_OverFlow_Success()
{
	eBool_t eDelayCompleted;
	uint32_t ulMockCounter = 0xFFFFFFFF, ulMockTimeStamp = 0;
	
	eDelayCompleted = eMpbTimeBaseIsDelayDone( ulMockCounter, ulMockTimeStamp );
	
	TEST_ASSERT_EQUAL( eFalse, eDelayCompleted );
}
/*----------------------------------------------------------------------------*/
