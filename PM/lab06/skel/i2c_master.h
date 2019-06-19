#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <avr/io.h>


/* Initializeaza I2C. */
void    I2C_init(void);

/* Trimite conditia de start (adresa slave + bit read/write. */
uint8_t I2C_start(uint8_t address);

/* Trimite un cadru de date. */
uint8_t I2C_write(uint8_t data);

/* Returneaza cadrul de date primit de la slave si trimite ACK acestuia. */
uint8_t I2C_read_ack(void);

/* Returneaza cadrul de date primit de la slave si trimite NACK acestuia. */
uint8_t I2C_read_nack(void);

/* Functia trimite conditia de start (adresa slave-ului 'address'),
 * apoi trimite 'length' cadre de date din bufferul 'data'.
 */
uint8_t I2C_transmit(uint8_t address, uint8_t* data, uint16_t length);

/* Functia trimite conditia de start (+adresa slave-ului 'address'),
 * apoi citeste 'length' cadre de date si le salveaza in bufferul 'data'.
 */
uint8_t I2C_receive(uint8_t address, uint8_t* data, uint16_t length);

/* Functia trimite conditia de start (+adresa slave-ului 'address'),
 * apoi realizeaza o operatie de scriere:
 *    - trimite adresa registrului
 *    - trimite 'length' cadre de date din bufferul 'data'.
 */
uint8_t I2C_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);

/* Functia trimite conditia de start (+adresa slave-ului 'address'),
 * apoi realizeaza o operatie de scriere:
 *    - trimite adresa registrului
 * apoi trimite inca o data adresa slave-ului (de data aceasta impreuna cu
 * operatia de citire)
 *    - citeste 'length' cadre de date si le salveaza in bufferul 'data'
 */
uint8_t I2C_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);

/* Trimite conditia de stop. */
void    I2C_stop(void);

#endif // I2C_MASTER_H
