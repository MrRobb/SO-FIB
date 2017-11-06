#include "mis_funciones.h"

int main(int argc, char *argv[]) {
	int tots_suma = 0;
	int suma = 0;
	for (int i = 1; i < argc; ++i) {
		if (esNumero(argv[i])) {
			if (tots_suma == 0) suma += mi_atoi(argv[i]);
		}
		else if (tots_suma == 0) tots_suma = i;
	}
	if (tots_suma == 0)
		printf("La suma es %i\n", suma);
	else
		printf("Error: el parámetro \"%s\" no es un número\n", argv[tots_suma]);
}
