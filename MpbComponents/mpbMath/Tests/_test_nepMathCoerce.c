/**
* @file			test_nepMathCoerce.c
* @brief		Tests for the nepMathCoerce library
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

#include "nepMathCoerce.h"
/* Private define ------------------------------------------------------------*/
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
/*******************************************************************************
slNepMathCoerce                      
*******************************************************************************/

void test_slNepMathCoerce_Minimum_Success()
{
	int32_t slResult;
	
	/* Positive minimum and maximum */
	slResult = slNepMathCoerce( 12456, 92345, 5636 );
	TEST_ASSERT_EQUAL_INT32( 12456, slResult );
	/* Value is minimum */
	slResult = slNepMathCoerce( 5635, 7345, 5635 );
	TEST_ASSERT_EQUAL_INT32( 5635, slResult );
	
	/* Negative minimum and positive maximum */
	slResult = slNepMathCoerce( -56477, 67323, -978344 );
	TEST_ASSERT_EQUAL_INT32( -56477, slResult );
	/* Value is minimum */
	slResult = slNepMathCoerce( -100945, 467823, -100945 );
	TEST_ASSERT_EQUAL_INT32( -100945, slResult );
	
	/* Negative minimum and maximum */
	slResult = slNepMathCoerce( -827456, -50664, -924654 );
	TEST_ASSERT_EQUAL_INT32( -827456, slResult );
	/* Value is minimum */
	slResult = slNepMathCoerce( -827456, -50664, -50664 );
	TEST_ASSERT_EQUAL_INT32( -50664, slResult );
}
/*----------------------------------------------------------------------------*/

void test_slNepMathCoerce_Maximum_Success()
{
	int32_t slResult;
	
	/* Positive minimum and maximum */
	slResult = slNepMathCoerce( 879543, 956754, 1089676 );
	TEST_ASSERT_EQUAL_INT32( 956754, slResult );
	/* Value is maximum */
	slResult = slNepMathCoerce( 5, 376, 376 );
	TEST_ASSERT_EQUAL_INT32( 376, slResult );
	
	/* Negative minimum and positive maximum */
	slResult = slNepMathCoerce( -34, 67889, 345678 );
	TEST_ASSERT_EQUAL_INT32( 67889, slResult );
	/* Value is maximum */
	slResult = slNepMathCoerce( -2457, 1765, 1765 );
	TEST_ASSERT_EQUAL_INT32( 1765, slResult );
	
	/* Negative minimum and maximum */
	slResult = slNepMathCoerce( -146894, -3467, 687 );
	TEST_ASSERT_EQUAL_INT32( -3467, slResult );
	/* Value is maximum */
	slResult = slNepMathCoerce( -897434, -46578, -46578 );
	TEST_ASSERT_EQUAL_INT32( -46578, slResult );
}
/*----------------------------------------------------------------------------*/

void test_slNepMathCoerce_NotCoerced_Success()
{
	int32_t slResult;
	
	/* Positive minimum and maximum */
	slResult = slNepMathCoerce( 568445, 29485634, 745683 );
	TEST_ASSERT_EQUAL_INT32( 745683, slResult );
	
	/* Negative minimum and positive maximum */
	slResult = slNepMathCoerce( -13256745, 2364675, -65334 );
	TEST_ASSERT_EQUAL_INT32( -65334, slResult );
	
	/* Negative minimum and maximum */
	slResult = slNepMathCoerce( -23454674, -456234, -1234546 );
	TEST_ASSERT_EQUAL_INT32( -1234546, slResult );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ulNepMathCoerce                      
*******************************************************************************/

void test_ulNepMathCoerce_Minimum_Success()
{
	uint32_t ulResult;
	
	ulResult = ulNepMathCoerce( 34663, 34567345, 12567 );
	TEST_ASSERT_EQUAL_UINT32( 34663, ulResult );
	
	/* Value is minimum */
	ulResult = ulNepMathCoerce( 456733, 25678568, 456733 );
	TEST_ASSERT_EQUAL_UINT32( 456733, ulResult );
}
/*----------------------------------------------------------------------------*/

void test_ulNepMathCoerce_Maximum_Success()
{
	uint32_t ulResult;
	
	ulResult = ulNepMathCoerce( 55, 7654, 23456 );
	TEST_ASSERT_EQUAL_UINT32( 7654, ulResult );
	
	/* Value is maximum */
	ulResult = ulNepMathCoerce( 675, 50987, 50987 );
	TEST_ASSERT_EQUAL_UINT32( 50987, ulResult );
}
/*----------------------------------------------------------------------------*/

void test_ulCoerce_NotCoerced_Success()
{
	uint32_t ulResult;
	
	ulResult = ulNepMathCoerce( 4677, 75899, 36578 );
	TEST_ASSERT_EQUAL_UINT32( 36578, ulResult );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
xNepMathCoerceFloat                      
*******************************************************************************/
void test_xNepMathCoerceFloat_Minimum_Success()
{
	float xResultFloat;
	
	/* Positive minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( 345767.34f, 1353737374.4f, 23542.3f );
	TEST_ASSERT_EQUAL_FLOAT( 345767.34f, xResultFloat );
	/* Value is minimum */
	xResultFloat = xNepMathCoerceFloat( 7456.54f, 346373.42f, 7456.54f );
	TEST_ASSERT_EQUAL_FLOAT( 7456.54f, xResultFloat );
	
	/* Negative minimum and positive maximum */
	xResultFloat = xNepMathCoerceFloat( -8235.45f, 23566.12f, -276534.46f );
	TEST_ASSERT_EQUAL_FLOAT( -8235.45f, xResultFloat );
	/* Value is minimum */
	xResultFloat = xNepMathCoerceFloat( -3467.29f, 46377345.23f, -3467.29f );
	TEST_ASSERT_EQUAL_FLOAT( -3467.29f, xResultFloat );
	
	/* Negative minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( -2384762.55f, -862.98f, -346735734.56f );
	TEST_ASSERT_EQUAL_FLOAT( -2384762.55f, xResultFloat );
	/* Value is minimum */
	xResultFloat = xNepMathCoerceFloat( -862543.45f, -98624.00f, -862543.45f );
	TEST_ASSERT_EQUAL_FLOAT( -862543.45f, xResultFloat );
}
/*----------------------------------------------------------------------------*/

void test_xNepMathCoerceFloat_Maximum_Success()
{
	float xResultFloat;
	
	/* Positive minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( 45736.45f, 4843835.29f, 698263547.65f );
	TEST_ASSERT_EQUAL_FLOAT( 4843835.29f, xResultFloat );
	/* Value is maximum */
	xResultFloat = xNepMathCoerceFloat( 463.54f, 346737.45f, 346737.45f );
	TEST_ASSERT_EQUAL_FLOAT( 346737.45f, xResultFloat );
	
	/* Negative minimum and positive maximum */
	xResultFloat = xNepMathCoerceFloat( -347383.34f, 536334.75f, 923754727.56f );
	TEST_ASSERT_EQUAL_FLOAT( 536334.75f, xResultFloat );
	/* Value is minimum */
	xResultFloat = xNepMathCoerceFloat( -8625745.45f, 347834.98f, 347834.98f );
	TEST_ASSERT_EQUAL_FLOAT( 347834.98f, xResultFloat );
	
	/* Negative minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( -82365834.56f, -9763.35f, 378345.23f );
	TEST_ASSERT_EQUAL_FLOAT( -9763.35f, xResultFloat );
	/* Value is minimum */
	xResultFloat = xNepMathCoerceFloat( -72366534.45f, -6257.35f, -6257.35f );
	TEST_ASSERT_EQUAL_FLOAT( -6257.35f, xResultFloat );
}
/*----------------------------------------------------------------------------*/

void test_xNepMathCoerceFloat_NotCoerced_Success()
{
	float xResultFloat;
	
	/* Positive minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( 56.56f, 473457.90f, 378.90f );
	TEST_ASSERT_EQUAL_FLOAT( 378.90f, xResultFloat );
	
	/* Negative minimum and positive maximum */
	xResultFloat = xNepMathCoerceFloat( -3874.34f, 7933.20f, 3279.23f );
	TEST_ASSERT_EQUAL_FLOAT( 3279.23f, xResultFloat );
	
	/* Negative minimum and maximum */
	xResultFloat = xNepMathCoerceFloat( -837644.76f, -9733.34f, -24890.23f );
	TEST_ASSERT_EQUAL_FLOAT( -24890.23f, xResultFloat );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
sllNepMathCoerce                      
*******************************************************************************/
void test_sllNepMathCoerce_Minimum_Success()
{
	int64_t sllResult;
	
	/* Positive minimum and maximum */
	sllResult = sllNepMathCoerce( 456774, 456346346, -627 );
	TEST_ASSERT_EQUAL_INT64( 456774, sllResult );
	/* Value is minimum */
	sllResult = sllNepMathCoerce( 3463, 633737, 3463 );
	TEST_ASSERT_EQUAL_INT64( 3463, sllResult );
	
	/* Negative minimum and positive maximum */
	sllResult = sllNepMathCoerce( -235636, 346723346, -346357377 );
	TEST_ASSERT_EQUAL_INT64( -235636, sllResult );
	/* Value is minimum */
	sllResult = sllNepMathCoerce( -456, 765444, -456 );
	TEST_ASSERT_EQUAL_INT64( -456, sllResult );
	
	/* Negative minimum and maximum */
	sllResult = sllNepMathCoerce( -53463336, -3453, -9123765445 );
	TEST_ASSERT_EQUAL_INT64( -53463336, sllResult );
	/* Value is minimum */
	sllResult = sllNepMathCoerce( -23424, -9875, -23424 );
	TEST_ASSERT_EQUAL_INT64( -23424, sllResult );
}
/*----------------------------------------------------------------------------*/

void test_sllNepMathCoerce_Maximum_Success()
{
	int64_t sllResult;
	
	/* Positive minimum and maximum */
	sllResult = sllNepMathCoerce( 3456, 3734563, 234647485 );
	TEST_ASSERT_EQUAL_INT64( 3734563, sllResult );
	/* Value is maximum */
	sllResult = sllNepMathCoerce( 457345, 4567457, 4567457 );
	TEST_ASSERT_EQUAL_INT64( 4567457, sllResult );
	
	/* Negative minimum and positive maximum */
	sllResult = sllNepMathCoerce( -4573345, 235773, 15680034 );
	TEST_ASSERT_EQUAL_INT64( 235773, sllResult );
	/* Value is maximum */
	sllResult = sllNepMathCoerce( -34647585, 344967834, 344967834 );
	TEST_ASSERT_EQUAL_INT64( 344967834, sllResult );
	
	/* Negative minimum and maximum */
	sllResult = sllNepMathCoerce( -2345744455, -33453634, -678456 );
	TEST_ASSERT_EQUAL_INT64( -33453634, sllResult );
	/* Value is maximum */
	sllResult = sllNepMathCoerce( -467568568, -4456, -4456 );
	TEST_ASSERT_EQUAL_INT64( -4456, sllResult );
}
/*----------------------------------------------------------------------------*/

void test_sllNepMathCoerce_NotCoerced_Success()
{
	int64_t sllResult;
	
	/* Positive minimum and maximum */
	sllResult = sllNepMathCoerce( 673457, 34788935, 864356 );
	TEST_ASSERT_EQUAL_INT64( 864356, sllResult );
	
	/* Negative minimum and positive maximum */
	sllResult = sllNepMathCoerce( -7899223, 902248842, -3568 );
	TEST_ASSERT_EQUAL_INT64( -3568, sllResult );
	
	/* Negative minimum and maximum */
	sllResult = sllNepMathCoerce( -36373574, -21373574, -25373574 );
	TEST_ASSERT_EQUAL_INT64( -25373574, sllResult );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ullNepMathCoerce                      
*******************************************************************************/

void test_ullNepMathCoerce_Minimum_Success()
{
	uint64_t ullResult;
	
	ullResult = ullNepMathCoerce( 457345, 568584848, 57746 );
	TEST_ASSERT_EQUAL_UINT64( 457345, ullResult );
	
	/* Value is minimum */
	ullResult = ullNepMathCoerce( 978674, 3575907680, 978674 );
	TEST_ASSERT_EQUAL_UINT64( 978674, ullResult );
}
/*----------------------------------------------------------------------------*/

void test_ullNepMathCoerce_Maximum_Success()
{
	uint64_t ullResult;
	
	ullResult = ullNepMathCoerce( 238483, 56735745, 85234678546562 );
	TEST_ASSERT_EQUAL_UINT64( 56735745, ullResult );
	
	/* Value is maximum */
	ullResult = ullNepMathCoerce( 1234855, 6789434633, 6789434633 );
	TEST_ASSERT_EQUAL_UINT64( 6789434633, ullResult );
}
/*----------------------------------------------------------------------------*/

void test_ullNepMathCoerce_NotCoerced_Success()
{
	uint64_t ullResult;
	
	ullResult = ullNepMathCoerce( 45745848, 95673462424, 845912356 );
	TEST_ASSERT_EQUAL_UINT64( 845912356, ullResult );
}
/*----------------------------------------------------------------------------*/

/*******************************************************************************
scNepMathCoerce                      
*******************************************************************************/
void test_scNepMathCoerce_Minimum_Success()
{
	int8_t scResult;
	
	/* Positive minimum and maximum */
	scResult = scNepMathCoerce( 10, 20, -100 );
	TEST_ASSERT_EQUAL_INT8( 10, scResult );
	/* Value is minimum */
	scResult = scNepMathCoerce( 10, 20, 10 );
	TEST_ASSERT_EQUAL_INT8( 10, scResult );
	
	/* Negative minimum and positive maximum */
	scResult = scNepMathCoerce( -20, 10, -100 );
	TEST_ASSERT_EQUAL_INT8( -20, scResult );
	/* Value is minimum */
	scResult = scNepMathCoerce( -20, 10, -20 );
	TEST_ASSERT_EQUAL_INT8( -20, scResult );
	
	/* Negative minimum and maximum */
	scResult = scNepMathCoerce( -20, -10, -100 );
	TEST_ASSERT_EQUAL_INT8( -20, scResult );
	/* Value is minimum */
	scResult = scNepMathCoerce( -20, -10, -20 );
	TEST_ASSERT_EQUAL_INT8( -20, scResult );
}
/*----------------------------------------------------------------------------*/

void test_scNepMathCoerce_Maximum_Success()
{
	int8_t scResult;
	
	/* Positive minimum and maximum */
	scResult = scNepMathCoerce( 10, 20, 100 );
	TEST_ASSERT_EQUAL_INT8( 20, scResult );
	/* Value is maximum */
	scResult = scNepMathCoerce( 10, 20, 20 );
	TEST_ASSERT_EQUAL_INT8( 20, scResult );
	
	/* Negative minimum and positive maximum */
	scResult = scNepMathCoerce( -10, 20, 100 );
	TEST_ASSERT_EQUAL_INT8( 20, scResult );
	/* Value is maximum */
	scResult = scNepMathCoerce( -10, 20, 20 );
	TEST_ASSERT_EQUAL_INT8( 20, scResult );
	
	/* Negative minimum and maximum */
	scResult = scNepMathCoerce( -20, -10, -5 );
	TEST_ASSERT_EQUAL_INT8( -10, scResult );
	/* Value is maximum */
	scResult = scNepMathCoerce( -20, -10, -10 );
	TEST_ASSERT_EQUAL_INT8( -10, scResult );
}
/*----------------------------------------------------------------------------*/

void test_scNepMathCoerce_NotCoerced_Success()
{
	int8_t scResult;
	
	/* Positive minimum and maximum */
	scResult = scNepMathCoerce( 10, 20, 15 );
	TEST_ASSERT_EQUAL_INT8( 15, scResult );
	
	/* Negative minimum and positive maximum */
	scResult = scNepMathCoerce( -10, 20, 2 );
	TEST_ASSERT_EQUAL_INT8( 2, scResult );
	
	/* Negative minimum and maximum */
	scResult = scNepMathCoerce( -20, -10, -15 );
	TEST_ASSERT_EQUAL_INT8( -15, scResult );
}
/*----------------------------------------------------------------------------*/
/*******************************************************************************
ucNepMathCoerce                      
*******************************************************************************/

void test_ucNepMathCoerce_Minimum_Success()
{
	uint8_t ucResult;
	
	ucResult = ucNepMathCoerce( 10, 20, 5 );
	TEST_ASSERT_EQUAL_UINT8( 10, ucResult );
	
	/* Value is minimum */
	ucResult = ucNepMathCoerce( 10, 20, 10 );
	TEST_ASSERT_EQUAL_UINT8( 10, ucResult );
}
/*----------------------------------------------------------------------------*/

void test_ucNepMathCoerce_Maximum_Success()
{
	uint8_t ucResult;
	
	ucResult = ucNepMathCoerce( 10, 20, 100 );
	TEST_ASSERT_EQUAL_UINT8( 20, ucResult );
	
	/* Value is maximum */
	ucResult = ucNepMathCoerce( 10, 20, 20 );
	TEST_ASSERT_EQUAL_UINT8( 20, ucResult );
}
/*----------------------------------------------------------------------------*/

void test_ucNepMathCoerce_NotCoerced_Success()
{
	uint8_t ucResult;
	
	ucResult = ucNepMathCoerce( 10, 20, 15 );
	TEST_ASSERT_EQUAL_UINT8( 15, ucResult );
}
/*----------------------------------------------------------------------------*/

