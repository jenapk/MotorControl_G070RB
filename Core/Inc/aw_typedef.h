//=================================================================================================
#ifndef _AW_TYPEDEF_H_
#define _AW_TYPEDEF_H_
//=================================================================================================
#include "typedef.h"

typedef union
{
	uint8_t Byte[4];
	uint32_t Value;
}un_aw_4B;

typedef union
{
	uint8_t Byte[2];
	uint16_t Value;
}un_aw_2B;

typedef struct
{
	uint8_t Para;
	uint8_t Length;		//total number of digits
	uint8_t Pose;		//position in decValue
	uint8_t MaxVal;		//digit Maximum Value
	uint8_t MinVal;		//digit Minimum Value
}st_aw_ProgInfo;

typedef struct
{
	uint8_t Hour;
	uint8_t Minute;
}st_aw_duration;	//motor on duration

typedef struct
{
	uint8_t 		StarDeltaTime;		//in Seconds
	uint8_t 		DryRunCurrent;		//in Amps
	uint8_t 		OverloadCurrent;	//in Amps
	uint8_t 		DryRunTime;			//in Minutes
	uint8_t			Ph2AmpPercMax;
	uint8_t			DryRunRetry;		//retrying in case of dryrun (in minutes)
	uint16_t 		OverVoltage;		//in Volts
	uint16_t 		UnderVoltage;		//in Volts
	st_aw_duration 	MotorOn;			//in Hours and Minutes
	uint16_t		AutoOnDelay;		//Auto On Delay
}st_aw_devConfig;
//=================================================================================================
#endif //_AW_TYPEDEF_H_
//=================================================================================================

