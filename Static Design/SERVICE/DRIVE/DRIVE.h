
#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#include "../../ECUAL/MOTOR/MOTOR_interface.h"

#define SLOW 30 
#define MIDIUM 60 
#define FAST 90 
#define STOP 0 

#define MODE1 0 
#define MODE2 1
#define MODE3 2
#define MODE4 3
#define MODE5 4

uint8_t DRIVE_u8Init ( void );
uint8_t DRIVE_u8Right ( void );
uint8_t DRIVE_u8Left ( void );
uint8_t DRIVE_u8Mode ( uint8_t mode);

#endif
