/**
  * @file			test_nepMathParity.c
  * @brief
  * @author			Philippe.Boulais
  * @date			Created on 6/7/2019
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
#include "nepMathParity.h"
 
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

void test_eNepMathParityCalcul_InvalidParameter_Fail()
{
	uint8_t ucData[ 1 ]       = { 0x45 };
    uint32_t ulNumberOfBytes  = 1;
    eParityType_t eParityType = eParityOdd;
    eNepError_t eNepError     = eSuccess;
    eBool_t bResponse         = eTrue;
    
    eNepError = eNepMathParityCalcul( NULL, ulNumberOfBytes, eParityType, &bResponse );
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError ); 
    
    eNepError = eNepMathParityCalcul( ucData, 0, eParityType, &bResponse );
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError ); 
	
	eNepError = eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError ); 
	
	eNepError = eNepMathParityCalcul( NULL, 0, eParityType, NULL );
    TEST_ASSERT_EQUAL( eInvalidParameter, eNepError ); 
	
}
/*----------------------------------------------------------------------------*/

void test_eNepMathParityCalcul_Success()
{
    uint8_t ucData[ 1 ]         = { 0x45 };
    uint32_t ulNumberOfBytes  = 1;
    eNepError_t eNepError     = eInvalidParameter;
    eParityType_t eParityType = eParityOdd;
    eBool_t bResponse         = eTrue;
    
    eNepError = eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eSuccess, eNepError ); 
}
/*----------------------------------------------------------------------------*/

void test_eNepMathParityCalcul_OddParity_OneByte_Success()
{
    uint8_t ucData[ 1 ]       = { 0x45 };
    uint32_t ulNumberOfBytes  = 1;
    eParityType_t eParityType = eParityOdd;
    eBool_t bResponse         = eTrue;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eFalse, bResponse ); 
    
    ucData[ 0 ] = 0x44;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eTrue, bResponse ); 
}
/*----------------------------------------------------------------------------*/

void test_eNepMathParityCalcul_EvenParity_OneByte_Success()
{
    uint8_t ucData[ 1 ]        = { 0x45 };
    uint32_t ulNumberOfBytes  = 1;
    eParityType_t eParityType = eParityEven;
    eBool_t bResponse         = eFalse;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eTrue, bResponse ); 
    
    ucData[ 0 ] = 0x44;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eFalse, bResponse); 
}
/*----------------------------------------------------------------------------*/

void test_eNepMathParityCalcul_OddParity_MoreThanOneByte_Success()
{
    uint8_t ucData[ 2 ]    	  = { 0x45, 0x44 };
    uint32_t ulNumberOfBytes  = 2;
    eParityType_t eParityType = eParityOdd;
    eBool_t bResponse         = eTrue;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eFalse, bResponse ); 
    
    ucData[ 0 ] = 0x44;
    ucData[ 1 ] = 0x44;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eTrue, bResponse ); 
}
/*----------------------------------------------------------------------------*/

void test_eNepMathParityCalcul_EvenParity_MoreThanOneByte_Success()
{
    uint8_t ucData[ 2 ]         = { 0x45, 0x44 };
    uint32_t ulNumberOfBytes  = 2;
    eParityType_t eParityType = eParityEven;
    eBool_t bResponse         = eFalse;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eTrue, bResponse ); 
    
    ucData[ 0 ] = 0x44;
    ucData[ 1 ] = 0x44;
    
    eNepMathParityCalcul( ucData, ulNumberOfBytes, eParityType, &bResponse );
    
    TEST_ASSERT_EQUAL( eFalse, bResponse ); 
}
/*----------------------------------------------------------------------------*/