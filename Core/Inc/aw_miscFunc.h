/*
 * aw_miscFunc.h
 *
 *  Created on: Jun 14, 2020
 *      Author: Administrator
 */

//=========================================================================================
#ifndef _AW_MISCFUNC_H_
#define _AW_MISCFUNC_H_
//=========================================================================================
#include "aw_typedef.h"

uint8_t aw_miscGetXOR (uint8_t* a_pBuffer, uint8_t a_Len);
uint8_t aw_miscGetStrXOR(uint8_t* a_pBuf1, uint8_t* a_pBuf2, uint8_t a_dataLen);
uint16_t aw_numRev16(uint16_t a_Value);
uint32_t aw_numRev32(uint32_t a_Value);
uint8_t aw_miscGetEpoch(uint8_t* a_pBuf);

void aw_miscGetBigEndianVal2B(uint8_t* a_pBuf);

uint8_t aw_base64Decode(const unsigned char *data, size_t input_length, uint8_t* a_pDest,  size_t *output_length);
void build_decoding_table(void);
uint8_t convBCD2Hex(uint8_t* a_pSrc, uint8_t a_srcLen, uint8_t* a_pDest);
void aw_miscDelay(uint8_t a_msDelay);

void aw_miscConvByte2Asc(uint8_t a_byteData, uint8_t* a_pDest);
void aw_miscGetMonthName(uint8_t a_month, uint8_t* a_pDest);

void aw_miscConvertToDecAsc(uint8_t* a_pDest, uint16_t a_Val, uint8_t a_maxLen);
void aw_miscConvertToDecDigits(uint8_t* a_pDest, uint16_t a_Value, uint8_t a_Len);
//=========================================================================================
#endif /* _AW_MISCFUNC_H_ */
//=========================================================================================
