all: main.hex 

main: main.c 
	avr-gcc -O3 -FCPU=16000000L -mmcu=atmega328p main.c -o main 

main.hex: main
	avr-objcopy -R .eeprom  -O ihex main main.hex 

flash: main.hex  
	avrdude -v -carduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex -b 115200

clean:
	rm -f main main.hex 
