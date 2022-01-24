/**
* @file			test_nepMathFifo.c
* @brief		Tests for the nepMathFifo library
* @author		Felix Brousseau-Vaillancourt
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
#include "nepMathFifo.h"
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

void tearDown()
{
	
}

/******************************************************************************/
/*                        eNepMathFifoInit Tests                		          */
/******************************************************************************/

void test_eNepMathFifoInit_Success()
{
	xNepMathFifo_t  xFifo;
	uint32_t    ulMockSize      = 10;
	uint8_t     ucBuffer[ 10 ]  = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, xFifo.bFull );
	TEST_ASSERT_EQUAL_UINT16( 0, xFifo.usPush );
	TEST_ASSERT_EQUAL_UINT16( 0, xFifo.usPop );
	TEST_ASSERT_EQUAL( &ucBuffer[ 0 ], xFifo.pvBuf );
	TEST_ASSERT_EQUAL_UINT16( ulMockSize, xFifo.usSize );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoInit_InvalidParam_Fail()
{
	xNepMathFifo_t  xFifo;
	uint32_t    ulMockSize      = 10;
	uint8_t     ucBuffer[ 10 ]  = { 0 };
	
	eResult = eNepMathFifoInit( NULL, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoInit( &xFifo, 0, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoInit( NULL, 0, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/******************************************************************************/
/*                        eNepMathFifoReset Tests                		          */
/******************************************************************************/

void test_eNepMathFifoReset_InvalidParam_Fail()
{  
	eResult = eNepMathFifoReset( NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/
void test_eNepMathFifoReset_Success()
{  
	xNepMathFifo_t  xFifo = { .bFull = eTrue, .usPush = 5, .usPop = 2};	
	
	eResult = eNepMathFifoReset( &xFifo );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, xFifo.bFull );
	TEST_ASSERT_EQUAL_UINT16( 0, xFifo.usPush );
	TEST_ASSERT_EQUAL_UINT16( 0, xFifo.usPop );
}

/******************************************************************************/
/*                        eNepMathFifoPush Tests                		          */
/******************************************************************************/

void test_eNepMathFifoPush_NoInit_InvalidParam_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 10;
	eBool_t     eMockOverWrite   = eFalse;
	
	eResult = eNepMathFifoPush( NULL, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPush( &xFifo, NULL, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	/* pxFifo->pvBuf == NULL since it was never initialized */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPush( NULL, NULL, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPush_WithInit_InvalidParam_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	eBool_t     eMockOverWrite   = eFalse;
	uint32_t    ulMockSize       = 2;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPush( NULL, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPush( &xFifo, NULL, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	/* pxFifo->pvBuf != NULL since it was initialized */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPush( NULL, NULL, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPush_BufferFullBeforePush_NoOverwrite_BufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	eBool_t     eMockOverWrite   = eFalse;
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eTrue, eFifoIsFull );    /* Buffer Full */
	
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/
void test_eNepMathFifoPush_BufferFullBeforePush_WithOverwrite_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData      = 5;
	uint32_t    ulMockLength    = 1;
	eBool_t     eMockOverWrite  = eTrue;
	uint32_t    ulMockSize      = 1;
	uint8_t     ucBuffer[ 10 ]  = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eTrue, eFifoIsFull );    /* Buffer Full */
	
	/* Overwrite the full buffer */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( 5, ucMockData );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPush_PushMoreThanFifoSize_NoOverwrite_BufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 2;
	eBool_t     eMockOverWrite   = eFalse;
	uint32_t    ulMockSize       = 1; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsFull );   /* Buffer Not Full */
	
	/* ulMockLength > ulMockSize and no overwrite causes the error */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPush_PushLengthOfFifoSize_NoOverwrite_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 2 ] = { 8, 10 };
	uint32_t    ulMockLength    = 2;
	eBool_t     eMockOverWrite  = eFalse;
	uint32_t    ulMockSize      = 2; 
	uint8_t     ucBuffer[ 10 ]  = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsFull );   /* Buffer Not Full */
	
	/* ulMockLength == ulMockSize and no overwrite */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( 8, ucMockData[ 0 ] );
	TEST_ASSERT_EQUAL( 10, ucMockData[ 1 ] );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                        eNepMathFifoPop Tests                		              */
/******************************************************************************/

void test_eNepMathFifoPop_NullPointers_eInvalidParameter_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 1; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	
	eResult = eNepMathFifoPop( NULL, &ucMockData, ulMockLength );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPop( &xFifo, NULL, ulMockLength );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPop( NULL, NULL, ulMockLength );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPop_PopEmptyFifo_eUnknownError_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 1; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	
	eResult = eNepMathFifoPop( &xFifo, &ucMockData, ulMockLength );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPop_PopNotEmptyNotFullFifo_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eFalse );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPop( &xFifo, &ucMockData, ulMockLength );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPop_PopMoreThanPushed_eBufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eFalse );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPop( &xFifo, &ucMockData, 2 );
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPop_PopMoreThanFifoSize_eBufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 3;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eTrue );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPop( &xFifo, &ucMockData, ulMockLength );
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPop_PopLengthSameAsFifoSize_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 3;
	uint32_t    ulMockSize       = 3; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eTrue );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPop( &xFifo, &ucMockData, ulMockLength );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                        eNepMathFifoPeak Tests                		          */
/******************************************************************************/

void test_eNepMathFifoPeak_NullPointers_eInvalidParameter_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 1; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	
	eResult = eNepMathFifoPeak( NULL, &ucMockData, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, NULL, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, ulMockLength, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoPeak( NULL, NULL, ulMockLength, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPeak_PeakEmptyFifo_eUnknownError_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 1; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eUnknownError, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPeak_PeakNotEmptyNotFullFifo_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eFalse );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPeak_PeakMoreThanPushed_eBufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eFalse );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, 2, &ulBytesRead );
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPeak_PeakLengthMoreThanFifoSize_eBufferOverflow_Fail()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 3;
	uint32_t    ulMockSize       = 2; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eTrue );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eBufferOverflow, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoPeak_PeakLengthSameAsFifoSize_Success()
{   
	xNepMathFifo_t  xFifo;
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 3;
	uint32_t    ulMockSize       = 3; 
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint32_t    ulBytesRead;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eTrue );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPeak( &xFifo, &ucMockData, ulMockLength, &ulBytesRead );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                        eNepMathFifoIsFull Tests                		  */
/******************************************************************************/

void test_eNepIsFifoFull_InvalidParam_Fail()
{  
	xNepMathFifo_t  xFifo;	
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsFull( &xFifo, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoIsFull( NULL, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoIsFull( NULL, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoIsFull_eTrue_Success()
{  
	xNepMathFifo_t  xFifo;	
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	eBool_t     eMockOverWrite   = eFalse;
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eTrue, eFifoIsFull );    /* Buffer Full */	
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoIsFull_eFalse_Success()
{  
	xNepMathFifo_t  xFifo;	
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsFull );
}

/******************************************************************************/
/*                        eNepMathFifoIsEmpty Tests                		  */
/******************************************************************************/

void test_eNepMathFifoIsEmpty_InvalidParam_Fail()
{  
	xNepMathFifo_t  xFifo;
	eBool_t     eFifoIsEmpty;
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsEmpty( &xFifo, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoIsEmpty( NULL, &eFifoIsEmpty );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
	
	eResult = eNepMathFifoIsEmpty( NULL, NULL );
	TEST_ASSERT_EQUAL( eInvalidParameter, eResult );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoIsEmpty_eTrue_Success()
{  
	xNepMathFifo_t  xFifo;
	eBool_t     eFifoIsEmpty;
	uint32_t    ulMockSize       = 1;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsEmpty( &xFifo, &eFifoIsEmpty );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eTrue, eFifoIsEmpty );
	
}
/*----------------------------------------------------------------------------*/

void test_eNepMathFifoIsEmpty_eFalse_Success()
{  
	xNepMathFifo_t  xFifo;
	eBool_t     eFifoIsEmpty;
	uint32_t    ulMockSize       = 2;
	uint8_t     ucBuffer[ 10 ]   = { 0 };
	uint8_t     ucMockData[ 10 ] = { 0 };
	uint32_t    ulMockLength     = 1;
	eBool_t     eMockOverWrite   = eFalse;
	eBool_t     eFifoIsFull;
	
	eResult = eNepMathFifoInit( &xFifo, ulMockSize, &ucBuffer[ 0 ] );
	TEST_ASSERT_EQUAL( eSuccess, eResult );   
	
	/* First Push Buffer isn't Full */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsFull );    /* Buffer Not Full */	
	
	eResult = eNepMathFifoIsEmpty( &xFifo, &eFifoIsEmpty );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsEmpty );	
	
	/* Second Push Buffer is Full */
	eResult = eNepMathFifoPush( &xFifo, &ucMockData, ulMockLength, eMockOverWrite );  
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	
	eResult = eNepMathFifoIsFull( &xFifo, &eFifoIsFull );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eTrue, eFifoIsFull );    /* Buffer Full */	
	
	eResult = eNepMathFifoIsEmpty( &xFifo, &eFifoIsEmpty );
	TEST_ASSERT_EQUAL( eSuccess, eResult );
	TEST_ASSERT_EQUAL( eFalse, eFifoIsEmpty );	
}
/*----------------------------------------------------------------------------*/
