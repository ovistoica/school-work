#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <stdlib.h>
#include <stdio.h>

#include "lcd.h"
#include "util.h"


/* definitii note (Hz) */
#define c    261
#define d    294
#define e    329
#define f    349
#define g    391
#define gS   415
#define a    440
#define aS   455
#define b    466
#define cH   523
#define cSH  554
#define dH   587
#define dSH  622
#define eH   659
#define fH   698
#define fSH  740
#define gH   784
#define gSH  830
#define aH   880

uint16_t surprise_notes[] = {a, a, a, f, cH, a, f, cH, a, eH, eH, eH, fH, cH, gS, f, cH, a, aH, a, a, aH, gSH, gH, fSH, fH, fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, a, cH, a, cH, eH, aH, a, a, aH, gSH, gH, fSH, fH, fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, cH, a, f, cH, a};

uint16_t durations[] = {500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 300, 150, 400, 200, 200, 125, 125, 250, 250, 400, 200, 200, 125, 125, 250, 125, 500, 375, 125, 500, 375, 125, 650, 500, 300, 150, 400, 200, 200, 125, 125, 250, 250, 400, 200, 200, 125, 125, 250, 250, 500, 375, 125, 500, 375, 125, 650};

uint8_t num_notes = sizeof(durations) / sizeof(durations[0]);


ISR(TIMER1_OVF_vect)
{
    PORTD &= ~(1 << PD5);
}

ISR(TIMER1_COMPA_vect)
{
    PORTD |= (1 << PD5);
}

ISR(PCINT1_vect)
{
}

ISR(PCINT3_vect)
{
}

void IO_init()
{
    /* LED-ul RGB si speaker-ul sunt puse ca iesire */
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD7);
    /* LED-ul RGB este stins (punem pinii in starea HIGH) */
    PORTB |= (1 << PB3);
    PORTD |= (1 << PD5) | (1 << PD7);

    /* butoanele sunt puse ca intrare, cu rezistenta de pull-up */
    DDRB &= ~(1 << PB2);
    DDRD &= ~(1 << PD6);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD6);

    /* intreruperile pentru butoane sunt activate */
    PCICR |= (1 << PCIE1) | (1 << PCIE3);
    PCMSK1 |= (1 << PCINT10);
    PCMSK3 |= (1 << PCINT30);
}

void timer0_init()
{
}

void timer1_init()
{
    /* timer1 este configurat cu modul Normal, top 0xFFFF si prescaler 256 */
    TCCR1B |= (1 << CS12);
    TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1);

    /* duty cycle-ul este setat initial la 25% */
    OCR1A = 0xFFFF / 4;
    /* duty cycle-ul initial pentru speaker (OC1B) este 50% */
    OCR1B = 0xFFFF / 2;
}

void timer2_init()
{
}

void update_color()
{
}

void update_song()
{
}


int main(void)
{
    /* initializari UI, ignorati */
    UI_init();
    sei();

    /* laboratorul incepe aici */
    IO_init();
    timer0_init();
    timer1_init();
    timer2_init();

    uint8_t iterations = 0;
    while(1)
    {
            iterations = (iterations + 1) % 4;
            if(iterations == 0)
                update_color();

            update_song();
            
            UI_draw();  // afisare UI, ignorati

            _delay_ms(25);
    }

    return 0;
}

