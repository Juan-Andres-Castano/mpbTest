/**
* @file 		mpbMathDebounce.c
* @brief	
* This library provides a management system for the debouncing of digital inputs. 
* @author		juan
* @date			Created on 2021-11-18
* @note
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 MPB, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of MPB.</center>
*
* @verbatim Usage Example@endverbatim
* this library allows to debounbce all the inputs AC/DC the application needs. 
* @code
* vMpbMathDebounceInit( &MyMpbMathDebounce,  ulOnCount, ullOffCount, slValue );
* eMpbError = vMpbMathDebounceUpdate( &MyMpbMathDebounce, slValue, &pslState );
* plState will give you the filtered input
* @endcode
* @param MpbMathDebounce_t datatype for the debouncing.
* @param ulOnCount, ullOffCount. config. of the debouncer.
* @return pslState. final read.
* @note could be instantiate in everywhere of the application. in that point the timer instantiation should be placed.
* @warning none.
**/
/* Includes ----------------------------------------------------------------- */
#include "mpbMathDebounce.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eMpbError_t vMpbMathDebounceInit( MpbMathDebounce_t *pxMpbMathDebounce, uint32_t ulOnCount, uint32_t ulOffCount,  eBool_t bInitialState )
{
	eMpbError_t eMpbError = eSuccess;
	
	if( pxMpbMathDebounce == NULL )
	{
		eMpbError = eInvalidParameter;
	}
	else
	{
		pxMpbMathDebounce->ulOffCount = ulOffCount;
		pxMpbMathDebounce->ulOnCount = ulOnCount;
		pxMpbMathDebounce->bNewProbablyState = bInitialState;
		pxMpbMathDebounce->bActualState = bInitialState;
		
		pxMpbMathDebounce->ulCount = ( bInitialState == eFalse ) ? ulOffCount : ulOnCount; 
	}
	
	return eMpbError;
}
/*----------------------------------------------------------------------------*/

eMpbError_t vMpbMathDebounceUpdate( MpbMathDebounce_t *pxMpbMathDebounce, eBool_t bActualState, eBool_t *pbFinalState )
{
	
	eMpbError_t eMpbError = eSuccess;
	
	if( ( pbFinalState == NULL ) || ( pxMpbMathDebounce == NULL ) )
	{
		eMpbError = eInvalidParameter;
	}
	else
	{	
		if( pxMpbMathDebounce->bNewProbablyState == bActualState )
		{
			if( pxMpbMathDebounce->ulCount > 0 )
			{
				pxMpbMathDebounce->ulCount--;
				if( pxMpbMathDebounce->ulCount == 0 )
				{
					pxMpbMathDebounce->bActualState = pxMpbMathDebounce->bNewProbablyState;
				}
			}
		}
		else
		{
			pxMpbMathDebounce->bNewProbablyState = bActualState;
			pxMpbMathDebounce->ulCount = ( bActualState == eFalse ) ? pxMpbMathDebounce->ulOffCount : pxMpbMathDebounce->ulOnCount;
		}
		
		*pbFinalState = pxMpbMathDebounce->bActualState;
	}
	return eMpbError;
}
/*----------------------------------------------------------------------------*/
