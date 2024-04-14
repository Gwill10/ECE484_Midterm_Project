# ECE484_Midterm_Project
In this repository, there are two different C files named blink_dashes and display_name. These files can be uploaded to an Arduino Uno using an AVR compiler to control a 16x2 LCD that has an I2C chip connected. I have listed the commands below to upload the C files to an Arduino board, but the COM port might need to be changed depending on the Arduino. To change what is displayed on the LCD in the blink-dashes program, you need to edit what is inside the parathesis on the fourth line down of the main function. To change what is displayed on the LCD in the display_name program, you need to edit inside the parathesis on the fifth line down of the main function.

# Commands to upload to board:

blink_dashes

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blink_dashes.o blink_dashes.c

avr-gcc -mmcu=atmega328p blink_dashes.o -o blink_dashes

avr-objcopy -O ihex -R .eeprom blink_dashes blink_dashes.hex

avrdude -patmega328p -Pcom3 -carduino -D -U flash:w:blink_dashes.hex:i

display_name

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o display_name.o display_name.c

avr-gcc -mmcu=atmega328p display_name.o -o display_name

avr-objcopy -O ihex -R .eeprom display_name display_name.hex

avrdude -patmega328p -Pcom3 -carduino -D -U flash:w:display_name.hex:i


