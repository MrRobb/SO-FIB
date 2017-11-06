#ifndef MIS_FUNCIONES_H
# define MIS_FUNCIONES_H

#include <stdio.h>
#define MAX_SIZE 8

int esNumero(char *str);
/*
	Pre:	Cierto
	Post:	Devuelve 1 si str es un número y tiene como mucho 8 cifras.
			En caso contrario, devuelve 0.
*/

unsigned int char2int(char c);
/*
	Pre:	c es un carácter mayor o igual que '0' y menor o igual que '9'.
	Post:	Devuelve el carácter transformado a integer.
*/

int mi_atoi(char *s);
/*
	Pre:	cierto.
	Post:	Devuelve s transformado a integer. Funcionamiento idéntico a
			atoi de la librería standard.
*/

#endif