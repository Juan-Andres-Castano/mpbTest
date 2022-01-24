/**
* @file			mpblibs.h
* @brief		This header provides common definitions needed mpb library
* @description
* @author	        juan
* @date			Created on 2021-03-1
* @note			indent using tab size : 4
* @copyright MPB, Montreal, Qc
* <h2><center>&copy; COPYRIGHT 2021 Mpb, Montreal, Quebec, Canada</center></h2>
* <h2><center>&copy; All rights reserved.</center></h2><br/><br/>
* <center>This document contains confidential and proprietary information
* of MPB (subject to a non-disclosure agreement) and shall</center>
* <center>not be disclosed, distributed, or reproduced in whole or in
* part, without the prior written authorization of NEPTRONIC.</center>
*
*/
/* Header guard ------------------------------------------------------------- */
#ifndef __MPBLIBS_H
#define __MPBLIBS_H

/* Includes ----------------------------------------------------------------- */

/* Standard library headers */
#include <stdint.h> /* for integer types and their limits */
#include <stdlib.h> /* for NULL, size_t, atoi(), div(), malloc, etc */
#include <string.h> /* for NULL, size_t, mem* and str* functions */
#include <stdarg.h> /* for variable arguments, va_start, va_arg */
#include <stddef.h> /* for NULL, size_t, etc */



/* Typedef ------------------------------------------------------------------ */

/**
* @brief Mpb defined error codes
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
eMpbError_t;

/**
* @brief	Mpbtronic define access
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

/* todo : à déplacer dans  mpblibsconfig.h */
#define USE_HEAP
#define USE_NEP_HEAP
#define USE_MALLOC_FAILED_HOOK
//#define USE_ASSERT_FAILED
#define eMpbATTR_PACKED			        __packed


/* Exported macro ----------------------------------------------------------- */

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
extern void vMpblibsUsDelay( uint32_t ulDelay );

/* UNIVERSAL SERIAL I/O API GLUE LOGIC for UART, SPI and I2C */

/**
* @brief		opens, optionally takes control and optionally initializes an peripheral channel
* @param 		xStream		Application specific peripheral channel identifier
* @param		ulFlags 	Application specific flags for stream initialization
* @return		success or librairie error message
* @note       A peripheral channel can be define by its communication protocole (Modbus_COM1, BACnet_COM1, etc)
*             or by target external device driver (PCA9555_1, M24C32_1, etc)
*             This is a good place to add RTOS support for mutex or initialize low level layer.
* 			eMpb_Open should be called for multiple consecutive access algorithm along with eMpb_Close.
*/
extern eMpbError_t eMpblibsOpen( handle_t xStream, const uint32_t ulFlags );

/**
* @brief		closes, optionnaly releases control and optionally deinitializes peripheral channel
* @param 		xStream		Application specific peripheral channel identifier
* @return		success or librairie error message
* @note       This is a good place to add RTOS support for mutex.
* 			eMpb_Open should be called for multiple consecutive access algorithm along with eMpb_Close.
*/
extern eMpbError_t eMpblibsClose( handle_t xStream );

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
extern eMpbError_t eMpblibsRead( handle_t xStream, size_t xAddrCmdSize, const void *pvAddrCmd, void * const pvBuffer, const size_t xBytes, size_t *pxBytesRead );

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
extern eMpbError_t eMpblibsWrite( handle_t xStream, size_t xAddrCmdSize, const void *pvAddrCmd, const void * pvBuffer, const size_t xBytes, size_t *pxBytesWritten );

/**
* @brief
* @param	xStream		Application specific peripheral channel identifier
* @param	ulRequest	Control Request Identifier. Application Specific.
* @param	pvValue		pointer on write value or where to save read value.
* @return	success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsIoCtl( handle_t xStream, uint32_t ulRequest, void *pvValue );

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
extern eMpbError_t eMpblibsI2CRequest( eAccess_t eAccess, handle_t xI2Cx, uint8_t ucDevAddr, size_t xAddrCmdSize, const void *pvAddrCmd, void *pvBuffer, size_t xBytes, size_t *pxBytesRW );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsSPIBytesReadWrite( handle_t xSPIx, void* const pvBytesOut, void* pvBytesIn, size_t xBytes );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsSPIBlockReadWrite( eAccess_t eAccess, handle_t xSPIx, void *pvBuffer, size_t xBytes, size_t *pxBytesRW );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsUartInit( handle_t xUARTx, handle_t xGPIOx, uint32_t ulPin, uint32_t ulBaudRate, uint8_t ucWordLength, uint8_t ucStopBits, uint8_t ucParity, size_t xSilenceBits, size_t xFrameTimeoutBits );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsUartRead( handle_t xUARTx, void* const pvBuffer, size_t xBytes, size_t *pxBytesRead, uint32_t ulMsTimeout );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsUartWrite( handle_t xUARTx, const void* pvBuffer, size_t xBytes, size_t *pxBytesWritten, uint32_t ulMsTimeout );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsPwrMonInit( void );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsPwrMonWaitPwrUp( void );

/**
* @brief
* @return		success or librairie error message
* @note
*/
extern int sMpblibsPwrMonIsLow( void );

/**
* @brief			Do a soft reset of the system
*/
extern void vMpblibsPowerMonitorSoftReset( void );

/**
* @brief
* @param      xANALOGx		Analog peripheral value handle
* @param      plReading		Pointer on variable where to save reading value.
* @param      lResolution	resolution or range in which to return reading
* @return	  success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsAnalogReadRaw( handle_t xANALOGx, int32_t *plReading );
extern eMpbError_t eMpblibsAnalogReadmV( handle_t xANALOGx, int32_t *plReading );
extern eMpbError_t eMpblibsAnalogReadRes( handle_t xANALOGx, int32_t lResolution, int32_t *plReading );

/**
* @brief
* @param      xANALOGx		Analog peripheral value handle
* @param      lOutput		value to write to Analog peripheral
* @param      lResolution	resolution or range of lOutput
* @return	  success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsAnalogWriteRaw( handle_t xANALOGx, int32_t lOutput );
extern eMpbError_t eMpblibsAnalogWritemV( handle_t xANALOGx, int32_t lOutput );
extern eMpbError_t eMpblibsAnalogModulationWritemV( handle_t xANALOGx, int32_t lOutput, int32_t lLowOutput );
extern eMpbError_t eMpblibsAnalogWriteRes( handle_t xANALOGx, int32_t lResolution, int32_t lOutput );

/**
* @brief
* @param      xBINARYx		Binary peripheral value handle
* @param      peState		Pointer on variable where to save reading value.
* @param      eState		value to write to binary peripheral
* @return	  success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsBinaryRead( handle_t xBINARYx, eBool_t* peState );
extern eMpbError_t eMpblibsBinaryWrite( handle_t xBINARYx, eBool_t eState );
extern eMpbError_t eMpblibsBinaryToggle( handle_t xBINARYx );

#ifdef USE_HEAP
/**
* @brief
* @param      ppvMemBlock	pointer to the memory block pointer
* @param      xSize			size of the memory block to be allocated
* @return	  success or librairie error message
* @note
*/
extern eMpbError_t eMpblibsMalloc( void** ppvMemBlock, size_t xSize );
extern eMpbError_t eMpblibsRealloc( void** ppvMemBlock, size_t xSize );
extern void vMpblibsFree( void** ppvMemBlock );
extern size_t xMpblibsGetFreeHeapSize( void );
extern size_t xMpblibsGetMinEverFreeHeapSize( void );
#ifdef USE_MPB_HEAP
/**
* @brief
* @return	user defined heap pointer
* @note
*/
extern void* pvMpblibsHeapPtr( void );
#endif
#ifdef USE_MALLOC_FAILED_HOOK
extern void vMpblibsMallocFailedHook( size_t xSizeRequired );
#else
#define vMpblibsMallocFailedHook( expr )			//( (void)0 )
#endif
#endif

/**
* @brief
* @param      expr	expression to be evaluated
* @note
*/
#ifdef USE_ASSERT_FAILED
 #define vMpblibsAssertParam( expr )					if( (expr) == 0 ) vMpblibsAssertFailed( __func__, __FILE__, __LINE__ )	
 extern void vMpblibsAssertFailed( char const *func, char const *file, int line );
#else
 #define vMpblibsAssertParam( expr )	        								    //( (void)0 )
 extern void vMpblibsAssertFailed( char const *func, char const *file, int line );	//( (void)0 )
#endif

/* Header guard ------------------------------------------------------------- */
#endif
/*** (C) COPYRIGHT 2021 MPB, Montreal, Quebec, Canada *** END OF FILE ***/
