.section .vectors
reset:
  jmp main //our main function written in C
  jmp __badisr //an ISR that fires when its not supposed to should just get trapped in an infinite loop
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp my_own_interrupt //this is interrupt 11, which corresponds to TIMER1_COMPA interrupt
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr
  jmp __badisr

__badisr:
  rjmp __badisr
 
