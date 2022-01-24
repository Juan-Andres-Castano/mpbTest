/**
  * @file			test_nepMathCrcUtil.c
  * @brief          nepMathCrcUtil test source file.
  * @author			Philippe.Boulais
  * @date			Created on 11/8/2019
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
#include "nepMathCrcUtil.h"
 
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
/*                    	  vNepMathCrcUtilReflectData                          */
/******************************************************************************/

void test_vNepMathCrcReflectData_Success()
{   
    uint8_t ucNumberOfBits    = 32;
    uint32_t ulData           = 0x12345678;
    uint32_t ulResult         = 0;
    
    vNepMathCrcUtilReflectData( ucNumberOfBits, ulData, &ulResult );
    
    TEST_ASSERT_EQUAL( 0x1E6A2C48, ulResult );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                    	  vNepMathCrcUtilReflectBytes                         */
/******************************************************************************/

void test_vNepMathCrcReflectBytes_Success()
{   
    uint32_t ulNumberOfBytes       = 4;
    uint8_t pucData[ 4 ]           = { 0x31, 0x32, 0x33, 0x34 };
    uint8_t pucResult[ 4 ]         = { 0, 0, 0, 0 };
    uint8_t pucExpectedResult[ 4 ] = { 0x8C, 0x4C, 0xCC, 0x2C };
    
    vNepMathCrcUtilReflectBytes( ulNumberOfBytes, pucData, pucResult );
    
    TEST_ASSERT_EQUAL_UINT8_ARRAY( pucExpectedResult, pucResult, 4 );
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                	     vNepMathCrcUtilPreCalculate            			  */
/******************************************************************************/

void test_vNepMathCrcUtilPreCalculate_CRC32_Success()
{
    uint8_t ucWidth          = 32;
    uint32_t ulInitial       = 0x00000000;
    uint32_t ulPolynomial    = 0x4C11DB7;
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };  
    uint32_t ulCrcValue      = 0;
    
    
    vNepMathCrcUtilCalculate( ucWidth, ulInitial, ulPolynomial, ulNumberOfBytes, pucBuffer, &ulCrcValue );
    
    ulCrcValue ^= 0xFFFFFFFF;
    
    TEST_ASSERT_EQUAL_UINT32( 0x765E7680 , ulCrcValue );
}
/*----------------------------------------------------------------------------*/

void test_vNepMathCrcUtilPreCalculate_CRC16_Success()
{
    uint8_t ucWidth          = 16;
    uint32_t ulInitial       = 0xFFFF;
    uint32_t ulPolynomial    = 0xC867;
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };  
    uint32_t ulCrcValue      = 0;
    
    
    vNepMathCrcUtilCalculate( ucWidth, ulInitial, ulPolynomial, ulNumberOfBytes, pucBuffer, &ulCrcValue );
    
    ulCrcValue ^= 0x0000; 
    
    TEST_ASSERT_EQUAL_UINT32( 0x4C06 , ulCrcValue );
}
/*----------------------------------------------------------------------------*/

void test_vNepMathCrcUtilPreCalculate_CRC8_Success()
{
    uint8_t ucWidth          = 8;
    uint32_t ulInitial       = 0x00;
    uint32_t ulPolynomial    = 0x07;
    uint32_t ulNumberOfBytes = 9;
    uint8_t pucBuffer[ 9 ]   = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };  
    uint32_t ulCrcValue      = 0;
    
    
    vNepMathCrcUtilCalculate( ucWidth, ulInitial, ulPolynomial, ulNumberOfBytes, pucBuffer, &ulCrcValue );
    
    ulCrcValue ^= 0x00; 
    
    TEST_ASSERT_EQUAL_UINT32( 0xF4 , ulCrcValue );
}
/*----------------------------------------------------------------------------*/
