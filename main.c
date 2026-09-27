#include <avr/interrupt.h>
#include <avr/io.h>

int main(void) {
  DDRB |= (1 << PB5);
  TCCR1A =
      0; // we want CTC mode with no PWM behaviour, so WGM11:0 = 0, COM1A/B = 0
  TCCR1B =
      (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, with prescalar 1024
  OCR1A = 15624; // TOP = OCR1A = 15624, so the interrupt is called every
                 // 1024*(15624+1)/(16*10^6) seconds

  TIMSK1 = (1 << OCIE1A); // Output compare interrupt enable for OCR1A

  sei(); // enable global interupts
  while (1) {
  }
}

void my_own_interrupt(void) __attribute__((__signal__, __used__));
void my_own_interrupt(void) { PORTB ^= (1 << PB5); }
