#ifndef INC_BMU_H_
#define INC_BMU_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "spi.h"
#include "tim.h"

class BMU{
public:
	void Wake79600(void);
	void ShutDown79600(void);

protected:
	SPI_HandleTypeDef hspi1;
	TIM_HandleTypeDef htim1;

	void MosiGPIOInit(uint8_t pin); // Initialize pin as GPIO Output
	void Delay_us(uint16_t us);     // New delay function for us
};



#endif /* INC_BMU_H_ */