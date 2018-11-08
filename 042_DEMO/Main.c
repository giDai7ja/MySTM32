// PA4 - CS
// PA5 - CLK
// PA7 - DIN
// PF0 - I2C1_SDA
// PF1 - I2C1_SCL

#include "stm32f0xx.h"

void Init(void);
void Send7219(unsigned char ADDR, unsigned char DATA); 
void Delay(unsigned int Val);
void SendI2C(unsigned char ADDR, unsigned char DATA);
	
int main(void)
{
Init();

Send7219 (0x00, 0x00);
Send7219 (0x09, 0xFF);
Send7219 (0x0A, 0xFF);
Send7219 (0x0B, 0xFF);
Send7219 (0x0C, 0xFF);
Send7219 (0x0F, 0x00);

	for ( int i=1; i<9 ; i++ ) {
		Send7219 (i, 0x0A);
	}
	
SendI2C(0x68, 0x00);
//unsigned int Intensity = 0xFF;	
while (1) {
	for ( int j=1 ; j<16 ; j++ ) {
		for ( int i=1; i<9 ; i++ ) {
			Send7219 (9-i, j+i);
		}
//		Send7219( 0x0A, Intensity/3);
//		Intensity++;
		Delay(300000);
	}
}
}

void Init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // GPIO
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // SPI
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // i2c
	
	GPIOA->MODER = GPIO_MODER_MODER4_1  |
								 GPIO_MODER_MODER5_1  |
								 GPIO_MODER_MODER7_1  |
	  						 GPIO_MODER_MODER13_1 |
								 GPIO_MODER_MODER14_1 ;
	
	GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR4  |
									 GPIO_OSPEEDER_OSPEEDR5  |
									 GPIO_OSPEEDER_OSPEEDR7  |
									 GPIO_OSPEEDER_OSPEEDR13 ;
	
	GPIOA->PUPDR = GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR14_1 ;
		
	SPI1->CR1 = SPI_CR1_MSTR; // | SPI_CR1_BR ;
	SPI1->CR2 = SPI_CR2_SSOE | SPI_CR2_NSSP | SPI_CR2_DS ;
	SPI1->CR1 |= SPI_CR1_SPE;
	
// I2C1 init
	I2C1->CR1 &= ~I2C_CR1_PE;
	
	GPIOF->MODER = GPIO_MODER_MODER0_1 |
								 GPIO_MODER_MODER1_1;
								 
	GPIOF->OTYPER = GPIO_OTYPER_OT_0 |
									GPIO_OTYPER_OT_1;
									
	GPIOF->OSPEEDR = GPIO_OSPEEDER_OSPEEDR0 |
									 GPIO_OSPEEDER_OSPEEDR1;
									 
	I2C1->TIMINGR = 0x00201D2B;

	I2C1->CR1 |= I2C_CR1_PE;
	
// I2C init	

}

void Send7219(unsigned char ADDR, unsigned char DATA){
while ( !(SPI1->SR & SPI_SR_TXE) ) {};
	SPI1->DR=(ADDR<<8 | DATA );
}

void Delay( unsigned int Val) {
  for( ; Val != 0; Val--) {
    __NOP();
  }
}

void SendI2C(unsigned char ADDR, unsigned char DATA){
	
	I2C1->CR2 |= I2C_CR2_START; // Start
	
	
	I2C1->CR2 |= I2C_CR2_STOP;  // Stop

}