/*
 * tsi.c
 *
 *  Created on: 20-Nov-2016
 *      Author: Admin
 */
#include "MKL25Z4.h"
#include "uart.h"
#include"circbuf.h"
#include"data.h"
#include"log.h"
#include"led.h"
#include"memory.h"
#include"main.h"
#include"dma.h"
#include"message.h"
#include"tsi.h"
#include<malloc.h>




void tsi_init()
{
	SIM_SCGC5 |= SIM_SCGC5_TSI_MASK;  // Enable  	Access to the TSI module
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;// Enable Port B Gate CLock

	PORTB_PCR16 |= PORT_PCR_MUX(0);		// Choose Alternate function 0 as TSI channel 9
	//PORTB_PCR17 |= PORT_PCR_MUX(0);


	TSI0_GENCS |= TSI_GENCS_ESOR_MASK;	// End of Scan interurpt in allowed
	TSI0_GENCS |= TSI_GENCS_NSCN_MASK;	// 'i' scans per electrode
	TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;	// Enable Touch sensing input mode
	TSI0_GENCS |= TSI_GENCS_TSIIEN_MASK; // Enable Touch sensing input interrupt
	TSI0_GENCS |= TSI_GENCS_EXTCHRG(0);
	TSI0_GENCS |= TSI_GENCS_REFCHRG(5);

	NVIC_EnableIRQ(TSI0_IRQn);			// Enable Global Interrupt
	__enable_irq();

	TSI0_DATA |= TSI_DATA_TSICH(9);		// Select channel number 9 for input


	TSI0_TSHD = 0xFF00;					// THRESHOLD VALUE


}


void tsi_start_scan()
{
	TSI0_GENCS |= (TSI_GENCS_TSIIEN_MASK);
	TSI0_DATA |= TSI_DATA_SWTS_MASK;     // START SCAN
}

void tsi_stop_scan()
{
	TSI0_GENCS &= ~(TSI_GENCS_TSIIEN_MASK);
}


void tsi_led()
{
	uint8_t prot_flag[8];
			if(d>19000 && d<23000)
				{


					LEDFunction(OFF,200);
				}
			else if(d>23000 && d<27000)
				{

					LEDFunction(YELLOW,200);
				}
			else if(d>27000 && d<31000)
				{

					LEDFunction(GREEN,200);
				}
			else if(d>31000 && d<35000)
				{

					LEDFunction(BLUE,200);
				}
			else if(d>35000 && d<39000)
				{

					LEDFunction(MAGENTA,200);
				}
			else if(d>39000 && d<43000)
				{

					LEDFunction(CYAN,200);
				}
			else if(d>43000 && d<47000)
				{

					LEDFunction(WHITE,200);
				}
			else if(d>47000 && d<51000)
				{

					LEDFunction(RED,200);
				}

			tsi_start_scan();
}



//tsi_dac(uint16_t data)

void TSI0_IRQHandler(void)
{
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK;
	TSI0_GENCS &= ~(TSI_GENCS_TSIIEN_MASK);
	tsi_flag=1;
	d = (TSI0_DATA);
	DAC0_DAT0L =d;
	DAC0_DAT0H = d>>12;
	//d=d/65536;
	//TSI0_GENCS |= (TSI_GENCS_TSIIEN_MASK);
	//TSI0_DATA |= TSI_DATA_SWTS_MASK;     // START SCAN

}
