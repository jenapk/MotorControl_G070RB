/*
 * aw_miscFunc.c
 *
 *  Created on: Jun 14, 2020
 *      Author: Administrator
 */

#include <stdint.h>
#include <string.h>
//#include "r_cg_wdt.h"

static uint8_t const fg_monthName[12][3] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
/*============================================================================*/
// calculating xor byte
uint8_t aw_miscGetXOR (uint8_t* a_pBuffer, uint8_t a_Len)
{
    uint8_t l_Counter, l_Temp = 0;

    for(l_Counter = 0; l_Counter < a_Len; l_Counter++)
    {
        l_Temp ^= *a_pBuffer++;
    }

    return(l_Temp);
}

//=================================================================================================
// this function used for check equality of two binary buffers.
// XORing corresponding byte by byte. If both bytes are same result is XOR ZERO else non-ZERO
// in case of non-zero function returns.
uint8_t aw_miscGetStrXOR(uint8_t* a_pBuf1, uint8_t* a_pBuf2, uint8_t a_dataLen)
{
	uint8_t l_retVal = 0, l_Count = 0;

	for(l_Count = 0; l_Count < a_dataLen; l_Count++)
	{
		l_retVal = *(a_pBuf1++) ^ *(a_pBuf2++);

		if(l_retVal) break;
	}

	return(l_retVal);
}


/*============================================================================*/
// useful function to reverse 16bits (endian issue)
uint16_t aw_numRev16(uint16_t a_Value)
{
	uint16_t l_retVal = 0;

	l_retVal =  (uint16_t) (a_Value << 8) | (uint8_t) (a_Value >> 8);

	return(l_retVal);
}

/*============================================================================*/
// useful function to reverse 32bits (endian issue)
uint32_t aw_numRev32(uint32_t a_Value)
{
//	un_4Byte l_src, l_dst;

//	l_src.Value = a_Value;
//	l_dst.Value = 0;

//	l_dst.Byte[0] = l_src.Byte[3];
//	l_dst.Byte[1] = l_src.Byte[2];
//	l_dst.Byte[2] = l_src.Byte[1];
//	l_dst.Byte[3] = l_src.Byte[0];

//	return(l_dst.Value);

	return(0);
}

/*============================================================================*/
uint8_t aw_miscGetEpoch(uint8_t* a_pBuf)
{
//	SysTime_t l_sysTime =  SysTimeGet();		//system epoch time

//	*(a_pBuf + 0) = (uint8_t) (l_sysTime.Seconds >> 24);
//	*(a_pBuf + 1) = (uint8_t) (l_sysTime.Seconds >> 16);
//	*(a_pBuf + 2) = (uint8_t) (l_sysTime.Seconds >> 8);
//	*(a_pBuf + 3) = (uint8_t) (l_sysTime.Seconds >> 0);

	return(4);
}

/*============================================================================*/
uint8_t aw_miscGetBigEndianVal4B(uint32_t a_dataVal,  uint8_t* a_pBuf)
{
	*(a_pBuf + 0) = (uint8_t) (a_dataVal >> 24);
	*(a_pBuf + 1) = (uint8_t) (a_dataVal >> 16);
	*(a_pBuf + 2) = (uint8_t) (a_dataVal >> 8);
	*(a_pBuf + 3) = (uint8_t) (a_dataVal >> 0);
	return(4);
}

/*============================================================================*/
void aw_miscGetBigEndianVal2B(uint8_t* a_pBuf)
{
	uint8_t l_tempVal = 0;
	
	l_tempVal = *(a_pBuf + 0);
	*(a_pBuf + 0) = *(a_pBuf + 1);
	*(a_pBuf + 1) = l_tempVal;
}

/*============================================================================*/
uint8_t aw_miscConvAscBcd2Hex(uint8_t* a_pSrc, uint8_t a_srcLen, uint8_t* a_pDest)
{
	int i = 0;
    uint8_t l_char = 0;

    for(i = 0; i < a_srcLen; i++)
    {
        l_char = *(a_pSrc + i);

        if((l_char >= '0') && (l_char <= '9'))
            l_char -= 0x30;
        else
            l_char -= 55;

        *(a_pSrc + i) = l_char;

    }

    for(i = 0; i < a_srcLen; i+=2)
    {
        l_char = *(a_pSrc + i);
        l_char <<= 4;
        l_char |= *(a_pSrc + i + 1);
        a_pDest[i/2] = l_char;
    }

    return(i/2);
}

//=============================================================================
//converts one byte data to ascii format, useful in display
//0x12 --> "12"
void aw_miscConvByte2Asc(uint8_t a_byteData, uint8_t* a_pDest)
{
	*a_pDest++ = (a_byteData >>   4) + 0x30;
	*a_pDest++ = (a_byteData & 0x0F) + 0x30;
}
//=============================================================================
//to make delay in ms (for Renesas)
void aw_miscDelay(uint8_t a_msDelay)
{
	uint16_t i, j;
	
	for(i = 0; i < a_msDelay; i++)
    {
	    for(j = 0; j < 1024; j++)
        {
	    	//jena: watchdog to be implemented
			//R_WDT_Restart();
	    }
    }
}

//will populate 3 characters of month name corresponding to a_month
// 0x02 ---> Feb
void aw_miscGetMonthName(uint8_t a_month, uint8_t* a_pDest)
{
	if( (a_month >= 1) && (a_month <= 12) )
	{
		memcpy(a_pDest, &fg_monthName[a_month - 1][0], 3);
	}
	else
	{
		memcpy(a_pDest, "***", 3);
	}
}

//=================================================================================================
//displays decimal values at a position. Converts to Asci charachters
void aw_miscConvertToDecAsc(uint8_t* a_pDest, uint16_t a_Val, uint8_t a_maxLen)
{
    uint8_t  l_rem = 0;
    uint16_t l_num = 0;

    l_num = a_Val;
    a_pDest += a_maxLen - 1;
    *a_pDest = '0';     //by default

    while(l_num)
    {
        l_rem = l_num % 10;
        *a_pDest = l_rem + 0x30;
        a_pDest--;

        l_num /= 10;
    }
}


//=============================================================================================
//converts a value to decimal digits (not ascii). 1 byte 240 -> 2 4 0
void aw_miscConvertToDecDigits(uint8_t* a_pDest, uint16_t a_Value, uint8_t a_Len)
{
	uint16_t l_cTemp, l_cCounter;
	uint16_t l_lValue;
	
	l_lValue = a_Value;
		
	for (l_cCounter = 0; l_cCounter < a_Len; l_cCounter++)
	{
		l_cTemp = 0;
		
		if ( l_lValue)
		{   l_cTemp = l_lValue % 10;
			l_lValue -= l_cTemp;
			l_lValue /= 10;
		}
		
		a_pDest[a_Len - l_cCounter -1] =l_cTemp;
	}
}		
