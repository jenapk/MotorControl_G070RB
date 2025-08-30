//=============================================================================
#ifndef _AW_CONFIG_APP_H_
#define _AW_CONFIG_APP_H_
//=============================================================================

#define AW_PROD_TEST_MODE		0			//to test relays and LEDs in production mode. Must be set 0 for final release
#define AW_TEST_BINARY			0			//set if testing binary. If 1 displayed on POR screen
#define AW_TEST_COUNTER			14			//Test binary counter

//version
#define AW_FW_VER_MAJOR			2
#define AW_FW_VER_MINOR			7

//lcd related configuration
#define NOTIFY_DELAY			5			//last notification diplay persistence time
#define POR_SCREEN_DELAY		3			//seconds to display POR screen
#define INVALID_PARA_INTERVAL	10			//to declare invalid parameters
#define VOLTAGE_UNBAL_PERC_3PH	7			//voltage unbalance percentage in 3ph system
#define LCD_RE_INIT_COUNT		5			//number of LCD reinitialization after relay ON/OFF
#define LCD_RE_INIT_INTERVAL	6			//LCD reinitialization interval after relay ON/OFF

//both must be same
#define MAX_APP_CURRENT_STR		"50"		//maximum current in Amps in ASCII, 26, 32, 40, 50, file name format "rl78i1c_128kb_26v23.hex"
#define MAX_APP_CURRENT_VAL		50			//maximum current in Amps in decimal value

#define MAX(a,b)				(a > b ? a : b)
#define MIN(a,b)				(a <= b ? a : b)
//=============================================================================
#endif //_AW_CONFIG_APP_H_
//=============================================================================
/*
-Motor running text in display

*/
