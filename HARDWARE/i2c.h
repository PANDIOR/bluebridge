#ifndef  __I2C_H__
#define  __I2C_H__

#include <stm32f10x.h>

extern void delay_ms(u32 nTime);






void i2c_init(void);
void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);



void u8_write(u8 addr,u8 data);
u8 u8_read(u8 addr);


void u32_write(u8 addr,u32 data);
u32 u32_read(u8 addr);


#endif
