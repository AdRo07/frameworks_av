/**
 * 
 * File Name:  omxVCM4P10_SADQuar_4x.c
 * OpenMAX DL: v1.0.2
 * Revision:   9641
 * Date:       Thursday, February 7, 2008
 * 
 * (c) Copyright 2007-2008 ARM Limited. All Rights Reserved.
 * 
 * 
 * Description:
 * This function will calculate SAD of pSrc with average of two Ref blocks
 * of 4x8 or 4x4 blocks
 * 
 */

#include "omxtypes.h"
#include "armOMX.h"
#include "omxVC.h"

#include "armVC.h"
#include "armCOMM.h"

/**
 * Function:  omxVCM4P10_SADQuar_4x   (6.3.5.4.2)
 *
 * Description:
 * This function calculates the SAD between one block (pSrc) and the average 
 * of the other two (pSrcRef0 and pSrcRef1) for 4x8 or 4x4 blocks.  Rounding 
 * is applied according to the convention (a+b+1)>>1. 
 *
 * Input Arguments:
 *   
 *   pSrc - Pointer to the original block; must be aligned on a 4-byte 
 *            boundary. 
 *   pSrcRef0 - Pointer to reference block 0 
 *   pSrcRef1 - Pointer to reference block 1 
 *   iSrcStep - Step of the original block buffer; must be a multiple of 4. 
 *   iRefStep0 - Step of reference block 0 
 *   iRefStep1 - Step of reference block 1 
 *   iHeight - Height of the block; must be equal to either 4 or 8. 
 *
 * Output Arguments:
 *   
 *   pDstSAD - Pointer of result SAD 
 *
 * Return Value:
 *    OMX_Sts_NoErr, if the function runs without error.
 *    OMX_Sts_BadArgErr - bad arguments: if one of the following cases occurs: 
 *    -    iHeight is not equal to either 4 or 8. 
 *    -    One of more of the following pointers is NULL: pSrc, pSrcRef0, 
 *              pSrcRef1, pDstSAD. 
 *    -    iSrcStep is not a multiple of 4 
 *    -    Any alignment restrictions are violated 
 *
 */
OMXResult omxVCM4P10_SADQuar_4x( 
	  const OMX_U8* 	pSrc,
      const OMX_U8* 	pSrcRef0,
	  const OMX_U8* 	pSrcRef1,	
      OMX_U32 	iSrcStep,
      OMX_U32	iRefStep0,
      OMX_U32	iRefStep1,
      OMX_U32*	pDstSAD,
      OMX_U32   iHeight
)
{
    /* check for argument error */
    armRetArgErrIf(pSrc == NULL, OMX_Sts_BadArgErr);
    armRetArgErrIf(pSrcRef0 == NULL, OMX_Sts_BadArgErr);
    armRetArgErrIf(pSrcRef1 == NULL, OMX_Sts_BadArgErr);
    armRetArgErrIf(pDstSAD == NULL, OMX_Sts_BadArgErr);
    armRetArgErrIf((iHeight != 8) && (iHeight != 4), OMX_Sts_BadArgErr);
    armRetArgErrIf(armNot4ByteAligned(pSrc), OMX_Sts_BadArgErr);
    armRetArgErrIf((iSrcStep == 0) || (iSrcStep & 3), OMX_Sts_BadArgErr);
    
    return armVCM4P10_SADQuar
        (pSrc, pSrcRef0, pSrcRef1, iSrcStep, 
        iRefStep0, iRefStep1, pDstSAD, iHeight, 4);
}

/*****************************************************************************
 *                              END OF FILE
 *****************************************************************************/

