/*
 * lab1.c
 */

#include "lcd.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>


#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",   // a
    (char*)"3111", // b
    (char*)"3131", // c
    (char*)"311",  // d
    (char*)"1",    // e
    (char*)"1131", // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	// t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};


void exemplu_usart()
{
    for(;;)
    {
        USART0_print("Salut!\n\r");
        _delay_ms(10);
    }
}

void task1_usart()
{
    // configurare porturi folosite
    DDRB &= ~(1 << PB2);
    DDRD &= ~(1 << PD6);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD6);

    // main loop
    int8_t PB2_flag = 0, PD6_flag = 0;
    for(;;)
    {
        // cand PB2 este apasat trimite un mesaj pe USART o singura data
        if(!(PINB & (1 << PB2)) && !PB2_flag)
        {
            PB2_flag = 1;
            USART0_print("PB2 apasat\n");
        }

        // cand PB2 este lasat trimite un mesaj pe USART o singura data
        if((PINB & (1 << PB2)) && PB2_flag)
        {
            PB2_flag = 0;
            USART0_print("PB2 lasat\n");
        }

        // cand PD6 este apasat trimite un mesaj pe USART o singura data
        if(!(PIND & (1 << PD6)) && !PD6_flag)
        {
            PD6_flag = 1;
            USART0_print("PD6 apasat\n");
        }

        // cand PD6 este lasat trimite un mesaj pe USART o singura data
        if((PIND & (1 << PD6)) && PD6_flag)
        {
            PD6_flag = 0;
            USART0_print("PD6 lasat\n");
        }

        // much switch, so debouncing, such delay
        _delay_ms(5);
    }
}


/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

void task2_usart()
{
    // configurare porturi folosite
    DDRC = 0xff;
    PORTC = 0x00;

    // main loop
    char c;
    for(;;)
    {
        c = USART0_receive();

        if (c >= 'a' && c <= 'z')
        {
            UDR0 = c;
            char * m = morse_alphabet[c - 'a'];
            while (*m)
            {
                speaker_morse(*m - '0');
                _delay_ms(50);
                m++;
                DDRC = 0xff;
                PORTC ^= 0xff;
            }
            _delay_ms(50);
        }
    }
}


void exemplu_lcd()
{
    LCD_print("Hello World!    salut");

    for(;;);
}

void task1_lcd()
{
    // configurare porturi folosite
    DDRB &= ~(1 << PB2);
    DDRD &= ~(1 << PD6);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD6);

    // initializari
    char str[] = "Hello World";
    LCD_print(str);

    // main loop
    int8_t pos = 0;
    uint8_t PINB_old = 0xff;
    uint8_t PIND_old = 0xff;
    for(;;)
    {
        uint8_t PINB_crt = PINB;
        uint8_t PIND_crt = PIND;

        if((PINB_old & (1 << PB2)) && !(PINB_crt & (1 << PB2)))
        {
            pos += 1;
            if(pos + (sizeof(str) - 1) > 16)
                pos = 16 - (sizeof(str) - 1);

            LCD_writeInstr(LCD_INSTR_clearDisplay);
            LCD_printAt(pos, str);
        }

        if((PIND_old & (1 << PD6)) && !(PIND_crt & (1 << PD6)))
        {
            pos -= 1;
            if(pos < 0)
                pos = 0;

            LCD_writeInstr(LCD_INSTR_clearDisplay);
            LCD_printAt(pos, str);
        }

        PINB_old = PINB_crt;
        PIND_old = PIND_crt;

        _delay_ms(5);
    }
}

void task2_lcd()
{
    // main loop
    uint8_t pos = 0;
    for(;;)
    {
        LCD_putCharAt(pos++, USART0_receive());

        switch(pos)
        {
            case 0x10:
                pos = 0x40;
                break;
            case 0x50:
                pos = 0x00;
                break;
        }
    }
}

void bonus_lcd()
{
    // configurare porturi folosite
    DDRB &= ~(1 << PB2);
    DDRD &= ~(1 << PD6);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD6);

    // creare caracter custom
    uint8_t chuck[] = {0x00, 0x0e, 0x0e, 0x04, 0x0e, 0x04, 0x0e, 0xa};
    LCD_writeInstr(LCD_INSTR_CGRAM);
    for(uint8_t i = 0; i < sizeof(chuck); ++i)
        LCD_writeData(chuck[i]);
    LCD_writeInstr(LCD_INSTR_DDRAM);

    // main loop
    int8_t pos_old = 0x40;
    uint8_t PINB_old = 0xff;
    uint8_t PIND_old = 0xff;
    LCD_putCharAt(pos_old, 0);
    for(;;)
    {
        uint8_t PINB_crt = PINB;
        uint8_t PIND_crt = PIND;

        uint8_t pb2 = (PINB_old & (1 << PB2)) && !(PINB_crt & (1 << PB2));
        uint8_t pd6 = (PIND_old & (1 << PD6)) && !(PIND_crt & (1 << PD6));

        int8_t pos = pos_old;

        if(!(PINB_crt & (1 << PB2)) && !(PIND_crt & (1 << PD6)))
        {
            if(pos >= 0x40)
                pos -= 0x40;
        }
        else if(pb2)
        {
            pos -= 1;
            if(pos == 0x3f)
                pos = 0x40;
        }
        else if(pd6)
        {
            pos += 1;
            if(pos == 0x50)
                pos = 0x4f;
        }
        else
        {
            if(pos <= 0x1f)
                pos += 0x40;
        }

        if(pos != pos_old)
        {
            LCD_writeInstr(LCD_INSTR_clearDisplay);
            LCD_putCharAt(pos, 0);

            pos_old = pos;
        }

        PINB_old = PINB_crt;
        PIND_old = PIND_crt;

        _delay_ms(5);
    }
}

void bonus_usart()
{
    // configurari porturi folosite
    DDRB &= ~(1 << PB2);
    DDRD &= ~(1 << PD6);
    PORTB |= (1 << PB2);
    PORTD |= (1 << PD6);

    // configurarea stdout
    FILE mystdout;
    mystdout.put = USART0_printf;
    mystdout.flags = __SWR;
    stdout = &mystdout;

    // main loop
    int8_t PB2_flag = 0, PD6_flag = 0;
    for(;;)
    {
        // cand PB2 este apasat trimite un mesaj pe USART
        if(!(PINB & (1 << PB2)) && !PB2_flag)
        {
            PB2_flag = 1;
            printf("PB2 apasat\n");
        }

        // cand PB2 este lasat trimite un mesaj pe USART
        if((PINB & (1 << PB2)) && PB2_flag)
        {
            PB2_flag = 0;
            printf("PB2 lasat\n");
        }

        // cand PD6 este apasat trimite un mesaj pe USART
        if(!(PIND & (1 << PD6)) && !PD6_flag)
        {
            PD6_flag = 1;
            printf("PD6 apasat\n");
        }

        // cand PD6 este lasat trimite un mesaj pe USART
        if((PIND & (1 << PD6)) && PD6_flag)
        {
            PD6_flag = 0;
            printf("PD6 lasat\n");
        }

        // much switch, so debouncing, such delay
        _delay_ms(5);
    }
}

int main()
{
    USART0_init();
    LCD_init();

    DDRD |= (1 << PC2);
    PORTD |= (1 << PC2);
    switch(3)
    {
        //USART
        case 0: exemplu_usart();    break;
        case 1: task1_usart();      break;
        case 2: task2_usart();      break;

        //LCD
        case 3: exemplu_lcd();      break;
        case 4: task1_lcd();        break;
        case 5: task2_lcd();        break;


        //bonus
        case 6: bonus_lcd();        break;
        case 7: bonus_usart();      break;
    }

    return 0;
}

