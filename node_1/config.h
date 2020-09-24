#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 4915200UL
#define FOSC 4915200UL // Clock speed
#define BAUD 9600 //Baud rate = symbols pr second.
#define MYUBRR FOSC/16/BAUD-1

#endif