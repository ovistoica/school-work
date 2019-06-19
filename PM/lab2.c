#include "util.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

/* TODO 2: implementati rutinele de tratare a intreruperii de butoane.
 * Cele doua butoane sunt asociate unor intreruperi diferite
ISR(...)
{
	// TODO 2: Verificati daca PB2 este apasat si modificati starea led-ului conectat la PB3.

	// TODO 3: Modificati valoarea registrului de comparare OCR1A in functie de butonul apasat.
}
ISR(...)
{
	// TODO 2: Verificati daca PB2 este apasat si modificati starea led-ului conectat la PB3.

	// TODO 3: Modificati valoarea registrului de comparare OCR1A in functie de butonul apasat.
}
*/

/* intreruperea de comparatie cu OCR1A */
ISR(TIMER1_COMPA_vect)
{
    PORTD ^= (1 << PD7);
}

/* TODO 4: implementati rutina de tratare a intreruperii de comparatie cu OCR1B.
ISR(...)
{

}
*/

/* TODO 6: implementati rutina de tratare a intreruperii de overflow.
ISR(...)
{

}
*/

/* initializeaza intrarile si iesirile */
void IO_init()
{
    // LED-ul verde este pus ca iesire
    DDRD |= (1 << PD7);
    // backlight LCD
    DDRC |= (1 << PC7);
    PORTC |= (1 << PC7);

	// TODO 2: Initializati LED-ul conectat la PB3 ca iesire.
    DDRB |= (1 << PB3);

	// TODO 6: Initializati LED-ul conectat la PD4 ca iesire.
    DDRD |= (1 << PD4);

    // butoanele sunt puse ca intrare, cu rezistenta de pull-up
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    DDRD &= ~(1 << PD6);
    PORTD |= (1 << PD6);

	// TODO 2: Activati intreruperile pe butoane

}

/* initializeaza timer-ul 1 */
void timer1_init()
{
	//TODO 6: Initializati ICR1

    // pragul initial de comparare
	// TODO 4: Moficati valoarea lui OCR1A pentru a obtine comportamentul specificat in enunt.
    OCR1A = 20600;
	// TODO 4: initializati OCR1B la valoarea corecta pentru a obtine comportamentul specificat in enunt.

    // activeaza intreruperea de comparare cu OCR1A
	// TODO 4: Activat intreruperea de comparare cu OCR1B
    TIMSK1 = (1 << OCIE1A);
	// TODO 6: Activati intreruperea de Overflow.

	// TODO 6: Modificati modul de functionare in CTC cu TOP la ICR1
    TCCR1B = (5 << CS10) | (1 << WGM12);
}

int main(void)
{
    // initializari si testare interfeta afisare/debug
    UI_init();
    printf_init();
    printf("USART ok\n");

    _delay_ms(1000);

    // codul relevant laboratorului incepe aici
    sei();

    timer1_init();
    IO_init();

    while(1)
    {
        drawProgressBars(TCNT1, OCR1A, 0xFFFF); // pentru afisare, ignorati
        _delay_ms(100);
    }

    return 0;
}

