// ARDUINO LEONARDO/UNO LED BLINK
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void) {
    // pin 8 as output
    DDRB |= (1 << PB4); // 00000001 -> 00040000 + DBRB |= xxx1xxxx
    
    while(1) {
        // toggle pin 8

        // HIGH
        PORTB |= (1 << PB4); // 000000001 -> 00010000 + PORTB |= xxx1xxxx
        _delay_ms(1000);
        // LOW
        PORTB &= ~(1 << PB4); // 00000001 -> 00010000 -> 11101111 &= (0 - set to 0, 1 - keep og) xxx0xxxx 
        _delay_ms(1000);
    }
    
    return 0;
}