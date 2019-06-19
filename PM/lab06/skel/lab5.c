/*
 * lab5.c
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "I2C_master.h"
#include "spi.h"

#include "MPL3115A2.h"
#include "LSM9DS0.h"
#include "ST7735R_TFT.h"

#include "game.h"

/*****************************************************************************
 * Preprocessor definitions
 ****************************************************************************/

/* Tensiunea de referinta utilizata de ADC. */
#define ADC_AREF_VOLTAGE 3.3
#define ADC_MAX_CHANNELS 6

/* Decomentati linia pentru a activa ADC IRQ. */
/* #define ADC_USE_IRQ */

/*****************************************************************************
 * Private types
 ****************************************************************************/

/* Numele canalelor de ADC. */
typedef struct
{
  const char *name;
  uint8_t    channel;
} adc_channel_t;

/*****************************************************************************
 * Private data
 ****************************************************************************/

/* Perechi de (Nume canal, Numar canal). */
const adc_channel_t ADC_channels[] = {
  // Senzor de temperatura conectat la ADC0
  {"Distanta", 0},

  // Senzor de lumina conectat la ADC1
  {"Lumina", 1},

  // Butoane conectate la ADC5 (!)
  {"Buton", 5}
};

/* Numarul de canale ADC utilizate. */
const int adc_num_channels = sizeof(ADC_channels) / sizeof(ADC_channels[0]);

#ifdef ADC_USE_IRQ
/* Numarul canalului initial. */
#  define ADC_INIT_CHANNEL 0

/* Valorile citite de la fiecare canal. */
volatile uint16_t ADC_value[ADC_MAX_CHANNELS];
#endif

/*****************************************************************************
 * Private functions
 ****************************************************************************/
#ifdef ADC_USE_IRQ
ISR(ADC_vect)
{
    // Interrupt is tirggered whenever a conversion is complet
    // TODO 5
    // * store new result
    // * change channel
    // * start a new conversion if there are any channels left
    // * be aware that we are using only ADC channels 0, 1 and 5

}

ISR(TIMER1_COMPA_vect)
{
    // TODO 5
    // * start an ADC conversion
}
#endif

/*
 * Functia initializeaza convertorul Analog-Digital.
 */
void ADC_init(void)
{
#ifndef ADC_USE_IRQ
    // TODO 2
    // enable ADC with:
    // * reference AVCC with external capacitor at AREF pin
    // * without left adjust of conversion result
    // * no auto-trigger
    // * no interrupt
    // * prescaler at 32

#else
    // TODO 5
    // enable ADC with interrupt, the rest of the settings like in TODO 2

#endif
}

/*
 * Functia porneste o noua conversie pentru canalul precizat.
 * In modul fara intreruperi, apelul functiei este blocant. Aceasta se
 * intoarce cand conversia este finalizata.
 *
 * In modul cu intreruperi apelul NU este blocant.
 *
 * @return Valoarea numerica raw citita de ADC de pe canlul specificat.
 */
uint16_t ADC_get(uint8_t channel)
{
#ifndef ADC_USE_IRQ
    // TODO 2
    // start ADC conversion on "channel"
    // wait for completion
    // return the result

#else
    // TODO 5

#endif

    (void)channel;
    return 0;
}

/*
 * Functia primeste o valoare numerica raw citita de convertul Analog-Digital
 * si calculeaza tensiunea (in volti) pe baza tensiunei de referinta.
 */
double ADC_voltage(int raw)
{
    (void)raw;
    // TODO 2

}

/*
 * Functia afiseaza pe display-ul grafic numele canalelor ADC si valorile
 * citite de la acestea.
 */
void ADC_show(void)
{
    char buf[32];

    // La ADC-ul microcontroller-ului avem conectate urmatoarele:
    //   ADC0: senzor temperatura
    //   ADC1: senzor lumina
    //   ADC5: 6 butoane + rezeistente (divizor de tensiune)

    // TODO 1: Afisati pe display-ul grafic numele fiecarui canalelor, cate
    // unul pe fiecare linie. Folositi-va de array-ul 'ADC_channels'
    //
    // Inaltimea unei linii este de ST7735R_FONT_HEIGHT pixeli (15 pixeli)
    // Afisati incepand de la coordonatele (0, 5)

    uint8_t line_y = 5;

}

/*
 * Functia afiseaza pe display-ul grafic numele senzorilor digitali si
 * valorile citite de la acestia.
 */
void I2C_show(void)
{
    // Ca sa putem printa in aceasi locatie un alt text, este necesar sa facem
    // clear la vechiul text, apoi sa il scriem pe cel nou. Cel mai simplu
    // mod de a face acest lucru este de a scrie caracterul <space> de cateva
    // ori, cat sa acoperim tot textul vechi.

    static const char *spaces = "                     ";
    uint8_t line_y = 50;
    char buf[32];

    // Prin interfata I2C avem urmatorii senzori conectati la microcontroller:
    //   MPL3115A2: Senzor digital - Temperatura si Presiune
    //   LSM9DS0: Senzor digital - Accelerometru, Giroscop si Magnetometru

    // TODO 3: Afisati pe display-ul grafic numele fiecarui senzor, cate
    // unul pe fiecare linie, impreuna cu valorile acestora (cu doua zecimale).
    // Incepeti cu coordonatele (0, 50). Valorile de la accelerometru (x, y, z)
    // afisati-le pe linii spearate.
    //
    // Incepem cu 50 pe OY ca sa nu suprascriem textul afisat de ADC_show().

    // Read Accelerometer
    // Print Accelerometer
    vector3f_t accel;


    // Read Pressure
    // Print Pressure
    double pressure;


    // Read Temperature
    // Print Temperature
    double temperature;


    // Read Altitude
    // Print Altitude
    double altitude;

}

/*
 * Functia initializeaza Timer1 pentru a genera o intrerupere care sa
 * porneasca ADC-ul la fiecare 100ms.
 */
#ifdef ADC_USE_IRQ
void TIMER1_init()
{
    // TODO 5
    // initialize timer to trigger COMPA interrupts every 100ms

}
#endif

int main(void)
{
    uint8_t mode = 0;

    // Init PB2 Button (Input, Pull-Up enabled).
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    // Init USART.
    USART0_init();

    // Init ADC.
    ADC_init();

    // Init I2C in master mode.
    I2C_init();

    // Init SPI for LCD.
    SPI_init();

    // Init MPL3115A2 Pressure sensor
    if(!MPL3115A2_init())
    {
        printf("ERROR: Couldn't init pressure sensor\r\n");
    }

    // Init LSM9DS0 Accel/Gyro/Mag sensors
    if(!LSM9DS0_init())
    {
        printf("ERROR: Couldn't init accel sensor\r\n");
    }

    // Init LCD
    ST7735R_Begin();

#ifdef ADC_USE_IRQ
    // Init Timer1
    TIMER1_init();
#endif

    // Enable interrupts.
    sei();

    // Clear screen with BLACK.
    ST7735R_FillRect(0, 0, ST7735R_WIDTH - 1, ST7735R_HEIGHT - 1, 0, 0, 0);

    for(;;)
    {
        // PB2 changes the mode.
        if ((PINB & (1 << PB2)) == 0)
        {
            // Clear screen with BLACK.
            ST7735R_FillRect(0, 0, ST7735R_WIDTH - 1, ST7735R_HEIGHT - 1, 0, 0, 0);
            mode = (mode + 1) % 2;

            // Re-init Game
            if (mode == 1)
            {
                GAME_init();
            }

            _delay_ms(125);
        }

        switch(mode)
        {
        // Sensors mode
        case 0:
            ADC_show();
            I2C_show();
            break;

        // Game mode
        case 1:
            // TODO 4
            // Read accel, move paddle


            // Magic. Don't touch.
            GAME_loop();
            _delay_ms(12);
            break;
        }
    }

    /* A happy compiler is a healthy compiler. */
    return 0;
}
