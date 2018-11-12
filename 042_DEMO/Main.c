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

unsigned char TMP, TMP2, TMP3;
	
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
	
//unsigned int Intensity = 0xFF;	
while (1) {
/*	for ( int j=1 ; j<16 ; j++ ) {
		for ( int i=1; i<9 ; i++ ) {
			Send7219 (9-i, j+i);
		}
*/
    SendI2C(0x48, TMP);

		Send7219 (1, ( TMP%10) );
		Send7219 (2, ( TMP/10) );
//		Send7219 (3, ( TMP2 & 0x0F ) | 0x80);
//		Send7219 (4, ( (TMP2>>4) & 0x07 ));
//		Send7219 (5, ( TMP3 & 0x0F ) | 0x80);
//		Send7219 (6, ( (TMP3>>4) & 0x07 ));

	
//		Send7219( 0x0A, Intensity/3);
//		Intensity++;
		Delay(30000);
		/*
	}
		*/
}
}

void Init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // SPI
	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;  // GPIOF
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
	
	GPIOF->AFR[0] = 1 | 1<<4;
	
	RCC->CFGR3 |= RCC_CFGR3_I2C1SW_SYSCLK;
	
	GPIOF->MODER = GPIO_MODER_MODER0_1 |
								 GPIO_MODER_MODER1_1;
								 
	GPIOF->OTYPER = GPIO_OTYPER_OT_0 |
									GPIO_OTYPER_OT_1;
									
	GPIOF->OSPEEDR = GPIO_OSPEEDER_OSPEEDR0 |
									 GPIO_OSPEEDER_OSPEEDR1;
									 
	GPIOF->PUPDR = GPIO_PUPDR_PUPDR0_0 |
									GPIO_PUPDR_PUPDR1_0;
									 
	I2C1->TIMINGR = 0x00201D2B;
//	I2C1->TIMINGR = 0x0010020A;

	I2C1->CR1 |= I2C_CR1_PE;

/*
	I2C1->CR2 = 0x68<<1;
	I2C1->CR2 |= 1<<16;
//	I2C1->CR2 |= I2C_CR2_AUTOEND;
	I2C1->CR2 |= I2C_CR2_START; // Start

  while(!(I2C1->ISR & I2C_ISR_TXIS)){};	

	I2C1->TXDR = 0x00;

  while(!(I2C1->ISR & I2C_ISR_TXIS)){};	
	I2C1->TXDR = 0x00;
		
  while(!(I2C1->ISR & I2C_ISR_TXIS)){};	
	I2C1->TXDR = 0x10;

  while(!(I2C1->ISR & I2C_ISR_TXIS)){};	
	I2C1->TXDR = 0x21;
		
		
		
  while(!(I2C1->ISR & I2C_ISR_TC)){};	
	I2C1->CR2 |= I2C_CR2_STOP;  // Stop
*/
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
	
	I2C1->CR2 = ADDR<<1;
	I2C1->CR2 |= 1<<16;
//	I2C1->CR2 |= I2C_CR2_AUTOEND;
	I2C1->CR2 |= I2C_CR2_START; // Start

  while(!(I2C1->ISR & I2C_ISR_TXIS)){};	

	I2C1->TXDR = 0x00;

  while(!(I2C1->ISR & I2C_ISR_TC)){};	
	I2C1->CR2 |= I2C_CR2_STOP;  // Stop		
	
	I2C1->CR2 = ADDR<<1 | 1;
	I2C1->CR2 |= 2<<16;
	I2C1->CR2 |= I2C_CR2_RD_WRN;
	I2C1->CR2 |= I2C_CR2_START; // Start
		
while(!(I2C1->ISR & I2C_ISR_RXNE)){};
	TMP = I2C1->RXDR;
while(!(I2C1->ISR & I2C_ISR_RXNE)){};
	TMP2 = I2C1->RXDR;
//while(!(I2C1->ISR & I2C_ISR_RXNE)){};
//	TMP3 = I2C1->RXDR;
		
	I2C1->CR2 |= I2C_CR2_STOP;  // Stop

}
