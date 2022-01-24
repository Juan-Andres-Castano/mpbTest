/**
* @file			mpbMathDebounce.h
* @brief
* @author		juan andres
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
**/
 
/* Header guard ------------------------------------------------------------- */
#ifndef __MPBMATHDEBOUNCE_H
#define __MPBMATHDEBOUNCE_H
/* Includes ----------------------------------------------------------------- */
#include "mpblibs.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */

/**
* @brief	Structure to debounce a AC/DC signal
*/
typedef struct
{
	uint32_t		ulOffCount; /**< the number of consecutive value for the state to be considered off */
	uint32_t		ulOnCount;	/**< the number of consecutive value for the state to be considered on */
	uint32_t		ulCount;						/**< the number of consecutive value */
	eBool_t			bNewProbablyState; 	/**< the new state */
	eBool_t			bActualState;			/**< the actual real state */
}
MpbMathDebounce_t;

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */


/**
* @brief		Initialize the debounce structure
* @param[in]	ulOnCount: the number of on count desired
* @param[in]	ulOffCount: the number of off count desired
* @param[in]	slValue: the inital value
* @param[out]	pxMpbMathDebounce: the initialize debounce structure
*/
eMpbError_t vMpbMathDebounceInit( MpbMathDebounce_t *pxMpbMathDebounce, uint32_t ulOnCount, uint32_t ulOffCount, eBool_t bInitialState );

/**
* @brief		Updates the state of the debounce
* @param[in]	pxMpbMathDebounce: the debounce structure
* @param[in]	slValue: the new value
* @param[out]	pslState: the debounce state
*/
eMpbError_t vMpbMathDebounceUpdate( MpbMathDebounce_t *pxMpbMathDebounce, eBool_t bActualState, eBool_t *pbFinalState );

#endif /* __MPBMATHDEBOUNCE_H */
