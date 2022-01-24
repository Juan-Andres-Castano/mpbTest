/**
* @file			mpbTimeBase.h
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
/* Header guard ------------------------------------------------------------- */
#ifndef __MPBTIMEBASE_H
#define __MPBTIMEBASE_H
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */

/**
* @brief	Timebase internal structure
*/
typedef struct
{
	uint32_t 	ulTick; 				/**< the actual tick increment */
	uint32_t 	ulMs;						/**< the actual Ms count */
	uint32_t 	ulSecond;				/**< the actual seconds count */
	uint16_t 	usMsCount;			/**< the actual miliseconds count */
	uint8_t 	ucTickCount;		/**< the actual tick count */
	uint8_t 	ucTickReload;		/**< the initial tick load */
}__attribute__ ((packed)) mpbTimeBase_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */

/**
* @brief		Initialize the timebase structure
* @param[in]	pxTimeBase: pointer to the timebase structure
* @param[in]	ucTickPerMs: the number of tick per miliseconds
* @return       Success or library error message
*/
eMpbError_t eMpbTimeBaseInit( mpbTimeBase_t *pxTimeBase, uint8_t ucTickPerMs );

/**
* @brief		Tick of the timebase structure
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       Success or library error message
*/
eMpbError_t eMpbTimeBaseTick( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Get the number of ticks 
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       The number of tick past since init
*/
uint32_t ulMpbTimeBaseGetTick( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Get the number of miliseconds
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       The number of miliseconds past since init
*/
uint32_t ulMpbTimeBaseGetMs( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Get the number of seconds
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       The number of seconds past since init
*/
uint32_t ulMpbTimeBaseGetSecond( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Get the number of minutes
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       The number of minutes past since init
*/
uint32_t ulMpbTimeBaseGetMinute( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Get the number of hour
* @param[in]	pxTimeBase: pointer to the timebase structure
* @return       The number of hour past since init
*/
uint32_t ulMpbTimeBaseGetHour( mpbTimeBase_t *pxTimeBase );

/**
* @brief		Check if the delay is completed
* @param[in]	ulCounter: the value of the timer
* @param[in]	ulTimeStamp: the value at which the timer is completed
* @return       eTrue if the delay is completed, eFalse otherwise
*/
eBool_t eMpbTimeBaseIsDelayDone( uint32_t ulCounter, uint32_t ulTimeStamp );

#endif /* __MPBTIMEBASE_H */
