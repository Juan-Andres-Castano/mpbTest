/**
* @file			neplibs.h
* @brief		This header provides common definitions needed nep library
* @description
* @author		Francis Savaria
* @date			Created on 2018-11-20
* @note			indent using tab size : 4
* @copyright Neptronic, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2018 Neptronic, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of NEPTRONIC (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of NEPTRONIC.</center>
*
*/
/* Header guard ------------------------------------------------------------- */
#ifndef __NEPLIBS_H
#define __NEPLIBS_H

/* Includes ----------------------------------------------------------------- */

/* Standard library headers */
#include <stdint.h> /* for integer types and their limits */
#include <stdlib.h> /* for NULL, size_t, atoi(), div(), etc */
#include <string.h> /* for NULL, size_t, mem* and str* functions */
//#include <ysizet.h>
#include <stdarg.h>
#include <stddef.h>

/* configuration header */
//#include "neplibsconfig.h"

/* Typedef ------------------------------------------------------------------ */

/**
* @brief Neptronic defined error codes
*/
typedef enum
{
	eSuccess				    =  0,
	eInvalidParameter           = -1,
	eAccessDenied			    = -2,
	eBusy	 		    		= -3,
	eTimeout	 		    	= -4,
    eBufferEmpty                = -5,
	eBufferFull		          	= -6,
	eBufferOverflow		    	= -7,
	eOutOfMemory			    = -8,
	eCheckFailed	 			= -9,
	eCorrupted	 		    	= -10,
	eOutOfRange	 		    	= -11,
	eNotFound	 		    	= -12,
	eInvalidObject			    = -13,
	eNotDiscarded		    	= -14,
	eNotRegistered			    = -15,
	ePropertyNotSuported	    = -16,
	eObjectTypeNotSuported	    = -17,
	eDriverError 				= -18,
	eUnknownError	    	    = -19,
    eInternalDeviceError        = -20
}
eNepError_t;

/**
* @brief	Neptronic define access
*/
typedef enum
{
	eREAD_ACCESS = 0,
	eWRITE_ACCESS = 1,
}
eAccess_t;

/**
* @brief boolean definition
*/
typedef enum
{
	eFalse 		= 0,
	eTrue		= !eFalse,
}
eBool_t;

/**
* @brief	user define handle
*/
typedef uint32_t	handle_t;

/* Define ------------------------------------------------------------------- */

/* todo : à déplacer dans  neplibsconfig.h */
#define USE_HEAP
#define USE_NEP_HEAP
#define USE_MALLOC_FAILED_HOOK
//#define USE_ASSERT_FAILED
#define eNepATTR_PACKED			        __packed


/* Exported macro ----------------------------------------------------------- */

/**
* @brief move to nepmathematics	
*/
//#ifndef TABLE_LEN	
//#define TABLE_LEN( table )		( sizeof( table ) / sizeof( table[ 0 ] ) )
//#endif

/**
* @brief	
*/
#ifdef __ICCARM__ 
#include <intrinsics.h>
#define __nop()     __no_operation()
#else
#define __nop()
#endif

/* Exported enum ------------------------------------------------------------ */

/* Exported struct ---------------------------------------------------------- */

/* Global variables --------------------------------------------------------- */

/* Exported function prototypes --------------------------------------------- */

/* SOFTWARE SERVICE GLUE LOGIC */

/**
* @brief		Delay for the specified number of micro seconds
* @param 		ulDelay		Blocking delay in micro seconds
* @note       	Blocking
*/
extern void vNeplibsUsDelay( uint32_t ulDelay );

/* UNIVERSAL SERIAL I/O API GLUE LOGIC for UART, SPI and I2C */

/**
* @brief		opens, optionally takes control and optionally initializes an peripheral channel
* @param 		xStream		Application specific peripheral channel identifier
* @param		ulFlags 	Application specific flags for stream initialization
* @return		success or librairie error message
* @note       A peripheral channel can be define by its communication protocole (Modbus_COM1, BACnet_COM1, etc)
*             or by target external device driver (PCA9555_1, M24C32_1, etc)
*             This is a good place to add RTOS support for mutex or initialize low level layer.
* 			eNep_Open should be called for multiple consecutive access algorithm along with eNep_Close.
*/
extern eNepError_t eNeplibsOpen( handle_t xStream, const uint32_t ulFlags );

/**
* @brief		closes, optionnaly releases control and optionally deinitializes peripheral channel
* @param 		xStream		Application specific peripheral channel identifier
* @return		success or librairie error message
* @note       This is a good place to add RTOS support for mutex.
* 			eNep_Open should be called for multiple consecutive access algorithm along with eNep_Close.
*/
extern eNepError_t eNeplibsClose( handle_t xStream );

/**
* @brief		
* @param 		xStream			Application specific peripheral channel identifier
* @param		xAddrCmdSize	Size in bytes of Memory Address or Device Command sent at the beginning of transaction. Can be 0.
* @param 		pvAddrCmd		Pointer to address or command buffer sent. NULL if xAddrCmdSize = 0, else not NULL.
* @param		pvBuffer		Pointer where to receive read data
* @param 		xBytes			Number of bytes to be read
* @param		pxBytesRead		Pointer where to save number of bytes read. Can be NULL.
* @return		success or librairie error message
* @note       
*/
extern eNepError_t eNeplibsRead( handle_t xStream, size_t xAddrCmdSize, const void *pvAddrCmd, void * const pvBuffer, const size_t xBytes, size_t *pxBytesRead );

/**
* @brief		
* @param 		xStream			Application specific peripheral channel identifier
* @param		xAddrCmdSize	Size in bytes of Memory Address or Device Command sent at the beginning of transaction. Can be 0.
* @param 		pvAddrCmd		Pointer to address or command buffer sent. NULL if xAddrCmdSize = 0, else not NULL.
* @param		pvBuffer		Pointer on data to be written
* @param 		xBytes			number of bytes to be written
* @param		pxBytesRead		Pointer where to save number of bytes written. Can be NULL.
* @return		success or librairie error message
* @note       
*/
extern eNepError_t eNeplibsWrite( handle_t xStream, size_t xAddrCmdSize, const void *pvAddrCmd, const void * pvBuffer, const size_t xBytes, size_t *pxBytesWritten );

/**
* @brief
* @param	xStream		Application specific peripheral channel identifier
* @param	ulRequest	Control Request Identifier. Application Specific.
* @param	pvValue		pointer on write value or where to save read value.
* @return	success or librairie error message
* @note
*/
extern eNepError_t eNeplibsIoCtl( handle_t xStream, uint32_t ulRequest, void *pvValue );

/* OTHER HARDWARE GLUE LOGIC */

/**
* @brief		
* @param 		eAccess			Read / Write access request
* @param 		xI2Cx			I2C peripheral handle, HAL dependant.
* @param 		DevAddr			Application specific external device address
* @param		xAddrCmdSize	Size in bytes of Memory Address or Device Command sent at the beginning of transaction. Can be 0.
* @param 		pvAddrCmd		Pointer to address or command buffer sent. NULL if xAddrCmdSize = 0, else not NULL.
* @param		pvBuffer		Pointer on data to be written or where to save read bytes
* @param 		xBytes			number of bytes to be written or read
* @param		pxBytesRW		Pointer where to save number of bytes written or read. Can be NULL.
* @return		success or librairie error message
* @note       
*/
extern eNepError_t eNeplibsI2CRequest( eAccess_t eAccess, handle_t xI2Cx, uint8_t ucDevAddr, size_t xAddrCmdSize, const void *pvAddrCmd, void *pvBuffer, size_t xBytes, size_t *pxBytesRW );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsSPIBytesReadWrite( handle_t xSPIx, void* const pvBytesOut, void* pvBytesIn, size_t xBytes );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsSPIBlockReadWrite( eAccess_t eAccess, handle_t xSPIx, void *pvBuffer, size_t xBytes, size_t *pxBytesRW );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsUartInit( handle_t xUARTx, handle_t xGPIOx, uint32_t ulPin, uint32_t ulBaudRate, uint8_t ucWordLength, uint8_t ucStopBits, uint8_t ucParity, size_t xSilenceBits, size_t xFrameTimeoutBits );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsUartRead( handle_t xUARTx, void* const pvBuffer, size_t xBytes, size_t *pxBytesRead, uint32_t ulMsTimeout );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsUartWrite( handle_t xUARTx, const void* pvBuffer, size_t xBytes, size_t *pxBytesWritten, uint32_t ulMsTimeout );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsPwrMonInit( void );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eNepError_t eNeplibsPwrMonWaitPwrUp( void );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern int sNeplibsPwrMonIsLow( void );

/**
* @brief
* @param      xANALOGx		Analog peripheral value handle
* @param      plReading		Pointer on variable where to save reading value.
* @param      lResolution	resolution or range in which to return reading
* @return	  success or librairie error message
* @note
*/
extern eNepError_t eNeplibsAnalogReadRaw( handle_t xANALOGx, int32_t *plReading );
extern eNepError_t eNeplibsAnalogReadmV( handle_t xANALOGx, int32_t *plReading );
extern eNepError_t eNeplibsAnalogReadRes( handle_t xANALOGx, int32_t lResolution, int32_t *plReading );

/**
* @brief
* @param      xANALOGx		Analog peripheral value handle
* @param      lOutput		value to write to Analog peripheral
* @param      lResolution	resolution or range of lOutput
* @return	  success or librairie error message
* @note
*/
extern eNepError_t eNeplibsAnalogWriteRaw( handle_t xANALOGx, int32_t lOutput );
extern eNepError_t eNeplibsAnalogWritemV( handle_t xANALOGx, int32_t lOutput );
extern eNepError_t eNeplibsAnalogWriteRes( handle_t xANALOGx, int32_t lResolution, int32_t lOutput );

/**
* @brief
* @param      xBINARYx		Binary peripheral value handle
* @param      peState		Pointer on variable where to save reading value.
* @param      eState		value to write to binary peripheral
* @return	  success or librairie error message
* @note
*/
extern eNepError_t eNeplibsBinaryRead( handle_t xBINARYx, eBool_t* peState );
extern eNepError_t eNeplibsBinaryWrite( handle_t xBINARYx, eBool_t eState );
extern eNepError_t eNeplibsBinaryToggle( handle_t xBINARYx );

#ifdef USE_HEAP
/**
* @brief
* @param      ppvMemBlock	pointer to the memory block pointer
* @param      xSize			size of the memory block to be allocated
* @return	  success or librairie error message
* @note
*/
extern eNepError_t eNeplibsMalloc( void** ppvMemBlock, size_t xSize );
extern eNepError_t eNeplibsRealloc( void** ppvMemBlock, size_t xSize );
extern void vNeplibsFree( void** ppvMemBlock );
extern size_t xNeplibsGetFreeHeapSize( void );
extern size_t xNeplibsGetMinEverFreeHeapSize( void );
#ifdef USE_NEP_HEAP
/**
* @brief
* @return	user defined heap pointer
* @note
*/
extern void* pvNeplibsHeapPtr( void );
#endif
#ifdef USE_MALLOC_FAILED_HOOK
extern void vNeplibsMallocFailedHook( size_t xSizeRequired );
#else
#define vNeplibsMallocFailedHook( expr )			//( (void)0 )
#endif
#endif

/**
* @brief
* @param      expr	expression to be evaluated
* @note
*/
#ifdef USE_ASSERT_FAILED
 #define vNeplibsAssertParam( expr )					if( (expr) == 0 ) vNeplibsAssertFailed( __func__, __FILE__, __LINE__ )	
 extern void vNeplibsAssertFailed( char const *func, char const *file, int line );
#else
 #define vNeplibsAssertParam( expr )												//( (void)0 )
 extern void vNeplibsAssertFailed( char const *func, char const *file, int line );	//( (void)0 )
#endif

/* Header guard ------------------------------------------------------------- */
#endif
/*** (C) COPYRIGHT 2018 NEPTRONIC, Montreal, Quebec, Canada *** END OF FILE ***/