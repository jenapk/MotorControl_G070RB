
#include "aw_config_io.h"
#include "aw_lcd_gdm.h"

#define NO_E1			0
#define WITH_E1			1

#define E1_PRESENCE		NO_E1


#define LCD_DELAY	aw_lcdDelay()	
		
/* RS Pin : High- data, Low- Command
 * RW Pin : High - Read, Low - Write
 * EN Pin : High to Low Enables Module
 */
 
void aw_appDelay(uint8_t a_msValue);
void aw_lcdWriteByte(uint8_t a_Data);
void aw_lcdDelay(void);
//=============================================================================
void aw_lcdInit (void)
{

//	LCD_DB4 = 0x00;
//	LCD_DB5 = 0x00;
//	LCD_DB6 = 0x00;
//	LCD_DB7 = 0x00;
	//jena: write 0x00 to LCD data port for above commented lines

//	LCD_RW_LOW();
	LCD_EN_LOW();
	LCD_RS_LOW();
	LCD_DELAY;
	
	//---------------------------------------------------
	//command Initialization
#if(E1_PRESENCE)				//1: with E1, 0: free run (witout E1)
	aw_lcdCommand(0x28);		// for specifications as lines and char pixels i.e 5x8
	LCD_DELAY;
	aw_lcdCommand(0x0C);		// Cursor ON/OFF:: 1/0	//0x0E
	LCD_DELAY;
	aw_lcdCommand(0x02);		// Set Cursor to home
	LCD_DELAY;
	aw_lcdCommand(0x01);		// Clear LCD
	LCD_DELAY;
	aw_lcdCommand(0x80);		//set
	LCD_DELAY;
#else	//for free run
	aw_lcdCommand(0x02);		// Set Cursor to home
	LCD_DELAY;
	aw_lcdCommand(0x28);		// for specifications as lines and char pixels i.e 5x8
	LCD_DELAY;
	aw_lcdCommand(0x0C);		// Cursor ON/OFF:: 1/0	//0x0E
	LCD_DELAY;
	aw_lcdCommand(0x06);		/* Auto Increment cursor */
	LCD_DELAY;
	aw_lcdCommand(0x01);		// Clear LCD
	LCD_DELAY;
	aw_lcdCommand(0x80);		/* cursor at home position */
	LCD_DELAY;	
#endif
}

void aw_lcdReInit (void)
{
	uint8_t i = 0;
	
	//	LCD_DB4 = 0x00;
	//	LCD_DB5 = 0x00;
	//	LCD_DB6 = 0x00;
	//	LCD_DB7 = 0x00;
	//jena: write 0x00 to LCD data port for above commented lines

//	LCD_RW_LOW();
	LCD_EN_LOW();
	LCD_RS_LOW();
	LCD_DELAY;
	
	for(i = 0; i < 10; i++)
	{
		aw_lcdCommand(0x30);		// Set Cursor to home
		LCD_DELAY;
	}
	
	LCD_DELAY;
	LCD_DELAY;
	aw_lcdInit();
}
//=============================================================================
void aw_lcdDisplay (uint8_t a_lineNo, uint8_t* a_pData)
{
	uint8_t l_tmpVal = 0;
	
	if(a_lineNo == LCD_LINE_1)
	{
		l_tmpVal = 0x80;
	}
	else if(a_lineNo == LCD_LINE_2)
	{
		l_tmpVal = 0xC0;
	}
	else if(a_lineNo == LCD_LINE_3)
	{
		l_tmpVal = 0x94;
	}
	else if(a_lineNo == LCD_LINE_4)
	{
		l_tmpVal = 0xD4;
	}
		
	aw_lcdCommand (l_tmpVal);
	
	for(l_tmpVal = 0; l_tmpVal < LCD_BUFFER_LEN; l_tmpVal++)
	{
		aw_lcdData(a_pData[l_tmpVal]);		//send data to LCD
	}
}

//=============================================================================
void aw_lcdCommand(uint8_t a_Data)
{
	LCD_RS_LOW();
	LCD_EN_HIGH();
	aw_lcdWriteByte(a_Data);
}

//=============================================================================
void aw_lcdData(uint8_t a_Data)
{	
	LCD_RS_HIGH();
	LCD_EN_HIGH();
	aw_lcdWriteByte(a_Data);
}

//=============================================================================
void aw_lcdWriteByte(uint8_t a_Data)
{
	//jena: write display byte to LCD data port for above commented lines
	
	aw_lcdEnPulse();
}
//=============================================================================
// Function to pulse EN pin after data is written
void aw_lcdEnPulse(void)
{
    LCD_DELAY;
	LCD_EN_HIGH();
	LCD_DELAY;
	LCD_EN_LOW();
	LCD_DELAY;
	LCD_DELAY;
}

void aw_lcdDelay(void)
{
	uint8_t j;
	for(j = 0; j < 20; j++)
    {
		asm("nop");
	}
}
