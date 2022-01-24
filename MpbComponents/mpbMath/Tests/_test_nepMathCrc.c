/**
  * @file			test_nepMathCrc.c
  * @brief          nepMathCrc test source file.
  * @author			Philippe.Boulais
  * @date			Created on 11/12/2019
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
#include "nepMathCrc.h"
#include "mock_nepMathCrcUtil.h"
#include "mock_neplibs.h"

/* Private define ------------------------------------------------------------*/
#define UNITY_SUPPORT_64	/* Allows unity to support 64 bits variables */
#define CMOCK_MEM_DYNAMIC	/* Allows ceedling to dynamically manages its memory */
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
/*----------------------------------------------------------------------------*/ 
void tearDown()
{
  
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    	      eNepMathCrcInit                                 */
/******************************************************************************/

void test_eNepMathCrcInit_CheckUpFailed_Failed()
{
    eNepError_t eNepError = eSuccess; 
    uint8_t ucWidth       = 10;
    uint32_t ulInitial    = 0;
    uint32_t ulPolynomial = 0x3456;
    uint32_t ulXorOutput  = 0xFFFFFFFF; 
    eBool_t bRefInput     = eFalse;
    eBool_t bRefOutput    = eFalse;
    xNepCrc_t xNepCrc;
    
    eNepError = eNepMathCrcInit( 0, ulInitial, ulPolynomial, ulXorOutput, bRefInput, bRefOutput, &xNepCrc );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
    eNepError = eSuccess;
    eNepError = eNepMathCrcInit( ucWidth, ulInitial, 0, ulXorOutput, bRefInput, bRefOutput, &xNepCrc );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
    eNepError = eSuccess;
    eNepError = eNepMathCrcInit( ucWidth, ulInitial, ulPolynomial, ulXorOutput, bRefInput, bRefOutput, NULL );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcInit_Success()
{
    eNepError_t eNepError = eSuccess; 
    uint8_t ucWidth       = 10;
    uint32_t ulInitial    = 0;
    uint32_t ulPolynomial = 0x3456;
    uint32_t ulXorOutput  = 0xAAAAAAAA; 
    eBool_t bRefInput     = eFalse;
    eBool_t bRefOutput    = eFalse;
    xNepCrc_t xNepCrc = 
    {
        .ucWidth      = 32,
        .ulPolynomial = 0x4C11DB7,
        .ulInitial    = 0xFFFFFFFF,
        .ulXorOutput  = 0xFFFFFFFF,
        .ulResidue    = 0xDEBB20E3,
        .bRefInput    = eTrue,
        .bRefOutput   = eTrue
    };
    
    eNepError = eNepMathCrcInit( ucWidth, ulInitial, ulPolynomial, ulXorOutput, bRefInput, bRefOutput, &xNepCrc );
    TEST_ASSERT_EQUAL_UINT32( 10, ( xNepCrc.ucWidth ) );
    TEST_ASSERT_EQUAL_UINT32( 0,  ( xNepCrc.ulInitial ) );
    TEST_ASSERT_EQUAL_UINT32( 0x3456,  ( xNepCrc.ulPolynomial ) );
    TEST_ASSERT_EQUAL_UINT32( 0xAAAAAAAA,  ( xNepCrc.ulXorOutput ) );
    TEST_ASSERT_EQUAL( eFalse,  ( xNepCrc.bRefInput ) );
    TEST_ASSERT_EQUAL( eFalse,  ( xNepCrc.bRefOutput ) );
    TEST_ASSERT_EQUAL( eSuccess, eNepError ); 
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    	    eNepMathCrcValidate                               */
/******************************************************************************/

void test_eNepMathCrcCalculate_WrongParameters_Failed()
{
    eNepError_t eNepError = eSuccess; 
    xNepCrc_t xNepCrc = 
    {
        .ucWidth      = 32,
        .ulPolynomial = 0x4C11DB7,
        .ulInitial    = 0xFFFFFFFF,
        .ulXorOutput  = 0xFFFFFFFF,
        .ulResidue    = 0xDEBB20E3,
        .bRefInput    = eTrue,
        .bRefOutput   = eTrue
    };
    uint8_t pucBuffer[ 9 ] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint32_t ulData        = 0;
    uint32_t ulSize        = 10;
    eNepError = eNepMathCrcCalculate( xNepCrc, 0, pucBuffer, &ulData );
 
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
    eNepError = eSuccess; 
    eNepError = eNepMathCrcCalculate( xNepCrc, ulSize, NULL, &ulData );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
    eNepError = eSuccess; 
    eNepError = eNepMathCrcCalculate( xNepCrc, ulSize, pucBuffer, NULL );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcCalculate_MallocFailed_Failed()
{
    eNepError_t eNepError = eSuccess; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .ulResidue    = 0xDEBB20E3,
      .bRefInput    = eTrue,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulData = 0;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eInvalidParameter );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcCalculate( xNepCrc, ulNumberOfBytes, pucBuffer, &ulData );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcCalculate_CRC32_NoReflection_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .ulResidue    = 0xDEBB20E3,
      .bRefInput    = eFalse,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulData          = 0;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    
    eNepError = eNepMathCrcCalculate( xNepCrc, ulNumberOfBytes, pucBuffer, &ulData );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_UINT32( 0x765E7680, ulData );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcCalculate_CRC32_ReflectInputReflectOutput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .ulResidue    = 0xDEBB20E3,
      .bRefInput    = eTrue,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277; 
    uint32_t ulData          = 0;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucResult, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcCalculate( xNepCrc, ulNumberOfBytes, pucBuffer, &ulData );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_UINT32( 0x2DFD2D88, ulData );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcCalculate_CRC32_ReflectInput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .ulResidue    = 0xDEBB20E3,
      .bRefInput    = eTrue,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulData          = 0;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucResult, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcCalculate( xNepCrc, ulNumberOfBytes, pucBuffer, &ulData );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_UINT32( 0x765E7680, ulData );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcCalculate_CRC32_ReflectOutput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .ulResidue    = 0xDEBB20E3,
      .bRefInput    = eFalse,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277;
    uint32_t ulData          = 0;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcCalculate( xNepCrc, ulNumberOfBytes, pucBuffer, &ulData );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
    TEST_ASSERT_EQUAL_UINT32( 0x2DFD2D88, ulData );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    	    eNepMathCrcValidate                               */
/******************************************************************************/

void test_eNepMathCrcValidate_WrongParameters_Failed()
{
    eNepError_t eNepError = eSuccess; 
    xNepCrc_t xNepCrc = 
    {
        .ucWidth      = 32,
        .ulPolynomial = 0x4C11DB7,
        .ulInitial    = 0xFFFFFFFF,
        .ulXorOutput  = 0xFFFFFFFF,
        .bRefInput    = eFalse,
        .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };   
    uint32_t ulCrcRead = 0x45;
 
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, 0, pucBuffer );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
    
    eNepError = eSuccess;
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, NULL );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_MallocFailed_Failed()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eFalse,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0xD202D277;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eInvalidParameter );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_NoReflexion_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eFalse,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x765E7680;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_NoReflexion_Failed()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eFalse,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x765E7681;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eCheckFailed, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectInput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eTrue,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x765E7680;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucResult, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectInput_Failed()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eTrue,
      .bRefOutput   = eFalse
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x765E7681;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucResult, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eCheckFailed, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectOutput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eFalse,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x2DFD2D88;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectOutput_Failed()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eFalse,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x2DFD2D80;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );    
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eCheckFailed, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectInputReflectOutput_Success()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
      .ucWidth      = 32,
      .ulPolynomial = 0x4C11DB7,
      .ulInitial    = 0xFFFFFFFF,
      .ulXorOutput  = 0xFFFFFFFF,
      .bRefInput    = eTrue,
      .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x2DFD2D88;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError );
}
/*----------------------------------------------------------------------------*/

void test_eNepMathCrcValidate_CRC32_ReflectInputReflectOutput_Failed()
{
    eNepError_t eNepError = eInvalidParameter; 
    xNepCrc_t xNepCrc = 
    {
        .ucWidth      = 32,
        .ulPolynomial = 0x4C11DB7,
        .ulInitial    = 0xFFFFFFFF,
        .ulXorOutput  = 0xFFFFFFFF,
        .bRefInput    = eTrue,
        .bRefOutput   = eTrue
    };
    uint32_t ulNumberOfBytes = 9;
    uint32_t ulCrcRead       = 0x2DFD2D80;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 }; 
    uint8_t *pucData         = &pucBuffer[ 0 ];
    uint8_t pucResult [ 9 ]  = { 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C };
    uint32_t ulCrcValue      = 0x89A1897F;
    uint32_t ulPostCrcValue  = 0xD202D277;
    
    eNeplibsMalloc_ExpectAndReturn( NULL, ( ulNumberOfBytes * sizeof( uint8_t ) ), eSuccess );
    eNeplibsMalloc_IgnoreArg_ppvMemBlock();
    eNeplibsMalloc_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    vNepMathCrcUtilReflectBytes_Expect( ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilReflectBytes_IgnoreArg_pucResult();
    vNepMathCrcUtilReflectBytes_ReturnThruPtr_pucResult( pucResult ); 
    
    vNepMathCrcUtilCalculate_Expect( ( xNepCrc.ucWidth ), ( xNepCrc.ulInitial ), ( xNepCrc.ulPolynomial ), ulNumberOfBytes, pucBuffer, NULL );
    vNepMathCrcUtilCalculate_IgnoreArg_pulCrcValue();
    vNepMathCrcUtilCalculate_ReturnThruPtr_pulCrcValue( &ulCrcValue );
    
    vNepMathCrcUtilReflectData_Expect( ( xNepCrc.ucWidth ), ulCrcValue, NULL );
    vNepMathCrcUtilReflectData_IgnoreArg_pulResult();
    vNepMathCrcUtilReflectData_ReturnThruPtr_pulResult( &ulPostCrcValue );
    
    vNeplibsFree_Expect( NULL );
    vNeplibsFree_IgnoreArg_ppvMemBlock();
    vNeplibsFree_ReturnThruPtr_ppvMemBlock( ( void** )&pucData );
    
    eNepError = eNepMathCrcValidate( xNepCrc, ulCrcRead, ulNumberOfBytes, pucBuffer );
    
    TEST_ASSERT_EQUAL( eCheckFailed, eNepError );
}
/*----------------------------------------------------------------------------*/

