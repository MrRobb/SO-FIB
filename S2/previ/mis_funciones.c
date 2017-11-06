#include "mis_funciones.h"

int esNumero(char *str) {
	if (str) {
		int i = 0;
		if (str[i] == '-') ++str;
		for (; str[i] != '\0'; ++i) {
			if (str[i] < '0' || str[i] > '9')
				return 0;
		}
		return (i > 0) && (i <= MAX_SIZE);
	}
	return 0;
}

unsigned int char2int(char c) {
	return (c - '0');
}

int mi_atoi(char *s) {
	int value;
	int sign;

	value = 0;
	sign = 1;
	while (*s == '\n' || *s == ' ' || *s == '\t' || *s == '\r' ||
		*s == '\v' || *s == '\f')
	{
		++s;
	}
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = 0;
		s++;
	}
	while ((*s) >= '0' && (*s) <= '9')
	{
		value *= 10;
		value = (sign ? value + (char2int(*s)) : value - (char2int(*s)));
		s++;
	}
	return (value);
}