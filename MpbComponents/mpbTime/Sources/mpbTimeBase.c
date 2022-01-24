/**
* @file 		mpbTimeBase.c
* @brief			
* This library provides a management system for the timing of the 
* differents process in the application. 
* Each on of the timers neeeded in a application should be initialized, triggerd inside a timer interruption
* and read for verify his deadline. 
* @author		juan andres Castano
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
* this library allows to instantiate all the timers the application needs. alls are instatiated from the same hardware timer.
* @code
* mpbTimeBase_t *myTimeBase = eMpbTimeBaseInit( &myTimeBase, 1000 );
* inside a timer interruption: eMpbTimeBaseTick( &myTimeBase ) ; //usually timer on 1ms
* uint32_t timerValue = ulMpbTimeBaseGetTick( &myTimeBase );
* @endcode
* @param mpbTimeBase_t datatype for aech timer.
* @param ticks. uint32 valur.
* @return returns the time counting in several formats or a delay. 
* @note could be instantiate in everywhere of the application. in that point the timer instantiation should be placed.
* @warning none.
**/

 
/* Includes ----------------------------------------------------------------- */
#include "mpbTimeBase.h"
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private enum ------------------------------------------------------------- */
/* Private struct ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* External variables ------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */
/* Exported functions ------------------------------------------------------- */

eMpbError_t eMpbTimeBaseInit( mpbTimeBase_t *pxTimeBase, uint8_t ucTickPerMs )
{
	/* Validate Entry Parameter */
	if( ( pxTimeBase == NULL ) || ( ucTickPerMs == 0 ) )
	{
		return eInvalidParameter;
	}
	
	pxTimeBase->ulTick = 0;
	pxTimeBase->ulMs = 0;
	pxTimeBase->ulSecond = 0;
	pxTimeBase->usMsCount = 1000; /* 1000 ms in a sec */
	pxTimeBase->ucTickCount = ucTickPerMs;
	pxTimeBase->ucTickReload = ucTickPerMs;
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/

eMpbError_t eMpbTimeBaseTick( mpbTimeBase_t *pxTimeBase )
{
	/* Validate Entry Parameter */
	if( pxTimeBase == NULL )
	{
		return eInvalidParameter;
	}
	
	pxTimeBase->ulTick++;
	
	/* Update sec and ms counter*/
	pxTimeBase->ucTickCount--;
	if( pxTimeBase->ucTickCount == 0 )
	{
		pxTimeBase->ucTickCount = pxTimeBase->ucTickReload;
		pxTimeBase->ulMs++;
		pxTimeBase->usMsCount--;
		/* Update seconds */
		if( pxTimeBase->usMsCount == 0 )
		{
			pxTimeBase->usMsCount = 1000;
			pxTimeBase->ulSecond++;
		}
	}
	
	return eSuccess;
}
/*----------------------------------------------------------------------------*/

uint32_t ulMpbTimeBaseGetTick( mpbTimeBase_t *pxTimeBase )
{
	return pxTimeBase->ulTick;
}
/*----------------------------------------------------------------------------*/

uint32_t ulMpbTimeBaseGetMs( mpbTimeBase_t *pxTimeBase )
{
	return pxTimeBase->ulMs;
}
/*----------------------------------------------------------------------------*/

uint32_t ulMpbTimeBaseGetSecond( mpbTimeBase_t *pxTimeBase )
{
	return pxTimeBase->ulSecond;
}
/*----------------------------------------------------------------------------*/

uint32_t ulMpbTimeBaseGetMinute( mpbTimeBase_t *pxTimeBase )
{
	return ( pxTimeBase->ulSecond / 60 );
}
/*----------------------------------------------------------------------------*/

uint32_t ulMpbTimeBaseGetHour( mpbTimeBase_t *pxTimeBase )
{
	return ( pxTimeBase->ulSecond / 3600 );
}
/*----------------------------------------------------------------------------*/

eBool_t eMpbTimeBaseIsDelayDone( uint32_t ulCounter, uint32_t ulTimeStamp )
{
	if( ( int32_t )( ulCounter - ulTimeStamp ) >= 0 )
	{
		return eTrue;
	}
	else
	{
		return eFalse;
	}
}
/*----------------------------------------------------------------------------*/


