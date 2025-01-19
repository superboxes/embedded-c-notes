#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

// dont optimize/more accurate
volatile uint16_t milliseconds = 0;
volatile uint8_t seconds = 0;

/*
CS12  CS11  CS10   Description
  0     0     0    Timer stopped
  0     0     1    No prescaler (F_CPU)
  0     1     0    Prescaler /8
  0     1     1    Prescaler /64
  1     0     0    Prescaler /256
  1     0     1    Prescaler /1024
  1     1     0    External clock on T1 pin, falling edge
  1     1     1    External clock on T1 pin, rising edge
*/

void timer1_init(void) {
    // clear control registers
    TCCR1A = 0;
    TCCR1B = 0;
    
    // compare mode
    TCCR1B |= (1 << WGM12);
    
    // 64 prescaler
    TCCR1B |= (1 << CS11) | (1 << CS10);
    
    // 1ms compare value
    // 16MHz/64 = 250kHz
    // for 1ms need 250 ticks
    OCR1A = 249;  // (250 - 1)
    
    // enable compare match interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    // counter init
    TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect) {
    milliseconds++;
    
    if (milliseconds >= 1000) {
        milliseconds = 0;
        seconds++;
        PORTB ^= (1 << PB4);  // toggle LED every 1s
    }
    
    // LED2 blink every 100s
    if ((milliseconds % 100) == 0) {
        PORTB ^= (1 << PB5);
    }
}

int main(void) {
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB6);
    
    timer1_init();
    sei();  
    
    while(1) {
        
    }
}