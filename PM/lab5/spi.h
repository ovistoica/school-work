#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/* SPI config */
#define SPI_PORT	PORTC
#define SPI_DDR 	DDRC
#define SPI_MISO	PB6
#define SPI_MOSI	PB5
#define SPI_SCK 	PB7

void SPI_init(void);
uint8_t SPI_exchange(uint8_t data);

#endif // SPI_H

