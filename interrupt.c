#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// interrupt func
ISR(INT6_vect) {
    PORTB ^= (1 << PB4);
}

int main(void) {
    DDRB |= (1 << PB4);
    
    // pin 7 input
    DDRE &= ~(1 << PE6);
    // pin 7 pullup
    PORTE |= (1 << PE6);

    /* FOR PIN 7
    ISC61  ISC60   Binary   Result
    0      0      00      LOW level
    0      1      01      Any edge
    1      0      10      Falling edge
    1      1      11      Rising edge
    */
    
    // pin 7 interrupt
    EICRB |= (1 << ISC61);    // ISC61 1
    EICRB &= ~(1 << ISC60);   // ISC60 0

    EIMSK |= (1 << INT6);     // enable interrupt
    
    // enable interrupts
    sei();
    
    while(1) {
        _delay_ms(100);
    }
    return 0;
}