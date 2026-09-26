#include <avr/io.h> //for PORTB, PB5, etc
#include <stdint.h> //for uint8_t etc types

#define Z_VAL 61

int main() {
  DDRB |= (1 << PB5); // set the 5th bit in DDRB to 1
  uint8_t x = 0xFF;   // starting value of our counter
  uint8_t y = 0xFF;
  uint8_t z = Z_VAL; // starting value of the last counter that we can
                     // manipulate to get a delay of our choice
  while (1) {
    for (; z > 0; z--) {
      for (; y > 0; y--) {
        for (; x > 0; x--)
          asm volatile("nop"); // gives a "nop" instruction
        x = 0xFF;              // reset our counter
      }
      y = 0xFF; // reset our counter
    }
    z = Z_VAL;           // reset our counter
    PORTB ^= (1 << PB5); // flip the 5th bit in PORTB (XOR)
  }
}
