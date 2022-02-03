/*
 * INTERFACE_SLAVE.h
 *
 * Created: 1/28/2022 11:19:46 PM
 *  Author: Khaled Ali
 */ 


#ifndef INTERFACE_SLAVE_H_
#define INTERFACE_SLAVE_H_

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/SPI/SPI.h"

uint8_t INTERFACE_u8Init(void);

uint8_t INTERFACE_u8SendData(uint8_t* str);
#endif /* INTERFACE_SLAVE_H_ */
