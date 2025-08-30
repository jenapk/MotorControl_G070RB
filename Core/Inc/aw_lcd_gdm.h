//===========================================================================
#ifndef _AW_LCD_GDM1602B_H_
#define _AW_LCD_GDM1602B_H_
//===========================================================================
#include "aw_typedef.h"

#define LCD_BUFFER_LEN			20
#define LCD_CHAR_SPACE			' '

#define LCD_LINE_1				1
#define LCD_LINE_2				2
#define LCD_LINE_3				3
#define LCD_LINE_4				4


void aw_lcdInit(void);
void aw_lcdReInit(void);
void aw_lcdCommand(uint8_t a_Data);
void aw_lcdData(uint8_t a_Data);
void aw_lcdDisplay  (uint8_t a_lineNo, uint8_t* a_pData);
void aw_lcdEnPulse(void);
//===========================================================================
#endif //_AW_LCD_GDM1602B_H_
//===========================================================================
