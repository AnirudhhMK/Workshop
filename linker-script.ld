MEMORY
{
  FLASH (rx) : ORIGIN = 0x0, LENGTH = 32K
  RAM (rw) : ORIGIN = 0x10100, LENGTH = 2K
}

SECTIONS{

  .text :
  {
    KEEP(*(.vectors))
    *(.text*)
  } > FLASH
  
  /DISCARD/ :
  {
    *(.*);
}
}
