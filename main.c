#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

static int inc = 0;
struct ringbuf_t {
  volatile char buf[256];
  volatile uint8_t writer;
  volatile uint8_t reader;
};
static struct ringbuf_t sendbuf;
static struct ringbuf_t recvbuf;

void send_msg(char *data) {
  while (*data != '\0') {
    sendbuf.buf[sendbuf.writer++] = *(data++);
  }
  UCSR0B |= (1 << UDRIE0);
  // UDR0 = 0; //uncomment if it doesn't work
}

int main(void) {
  DDRB |= (1 << PB5);
  TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR1A =
      0; // we want CTC mode with no PWM behaviour, so WGM11:0 = 0, COM1A/B = 0

  TCCR0B = (1 << CS00);
  TCCR1B =
      (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, with prescalar 1024

  OCR1A = 15624 / 256;
  OCR0A = 0;

  TIMSK1 = (1 << OCIE1A); // Output compare interrupt enable for OCR1A

  DDRD |= (1 << PD1) | (1 << PD6);
  DDRD &= ~(1 << PD0);

  UBRR0 = 103;
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (3 << UCSZ00);
  sei(); // enable global interupts
  while (1) {
  }
}

ISR(TIMER1_COMPA_vect) {
  int inc_old = inc;
  if (inc) {
    OCR0A++;
    if (OCR0A == 255)
      inc = 0;
  } else {
    OCR0A--;
    if (OCR0A == 0)
      inc = 1;
  }
  if (inc != inc_old) {

    PORTB ^= (1 << PB5);
    send_msg("Fade changed\r\n");
  }
}

ISR(USART_UDRE_vect) {
  if (sendbuf.reader == sendbuf.writer) {
    UCSR0B &= ~(1 << UDRIE0);
    return;
  }
  UDR0 = sendbuf.buf[sendbuf.reader++];
}

ISR(USART_RX_vect) { recvbuf.buf[recvbuf.writer++] = UDR0; }
