#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 4915200UL
#define FOSC 4915200UL // Clock speed
#define BAUD 9600 //Baud rate = symbols pr second.
#define MYUBRR FOSC/16/BAUD-1
#define test_bit(reg, bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg, bit) while( !test_bit(reg, bit))
#define set_bit(reg, bit) (reg |= (1<< bit))

#endif