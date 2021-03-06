/*
 * main.h
 *This function is created for providing compile time
 *switches for selecting logging functionality depending upon platform
 *Also enabling and disabling unittest
 *
 *  Created on: 11-Oct-2016
 *      Author: Gaurav Gandhi
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_
//#define UNIT_TESTS
// FOR FRDM ARCH=1
// FOR BBB ARCH= 2
#define BOARD (1)
#include"log.h"
typedef enum{NONE=0,LIGHT,TEMP,PWM,ACCELEROMTER,TSI}sensor_t;
sensor_t sensor;
uint32_t sensor_data[10];
uint32_t log_flag;
#ifdef BOARD==1

#define LOG0(c) uart_log((uint8_t*) c)
#define LOG1(x,y,z) uart_log1((uint8_t*) x, (uint32_t) y,(uint32_t) z)

#elif	BOARD==2

#define LOG0(c) bbb_log((uint8_t*) c)

#else

#define LOG0(c)
#endif

#ifdef UNIT_TESTS

#include"unittest.h"
#define unittest_init()	  unittest()

#else

#define unittest_init()

#endif

#endif /* INCLUDES_MAIN_H_ */
