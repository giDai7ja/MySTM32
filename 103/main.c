#include "stm32f10x.h"                  // Device header
#include "onewire.h"
#include <stddef.h>

unsigned int i;

int main(void){
	OW_Init();
unsigned char command[2]="\xcc\x44";
	
	OW_Send(OW_SEND_RESET, command, 2, NULL, NULL, OW_NO_READ);

	OW_out_set_as_Power_pin();

//	for (i=0; i<10000; i++);
  OW_out_set_as_TX_pin();

    uint8_t buf[2];

	OW_Send(OW_SEND_RESET, "\x55\x28\xF8\xFB\xE1\x01\x00\x00\x76\xbe\xff\xff", 12, buf, 2, 10);
	
	
	return 0;
	}
