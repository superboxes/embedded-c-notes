#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

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

// when timer reaches target
ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PB4);
}

int main(void) {
    DDRB |= (1 << PB4);
    
    // timer1 setup
    TCCR1B |= (1 << WGM12);      // clear timer on compare mode
    
    TCCR1B |= (1 << CS12) |      // 1024 prescaler
              (1 << CS10);       // 16MHz/1024 = 15,625 ticks per second
    
    OCR1A = 78124;               // comp value: 15,625 * 5 = 78,125 - 1
                                
    
    TIMSK1 |= (1 << OCIE1A);     // enable timer compare interrupt
    sei(); 
    
    while(1) {                 
        
    }
}