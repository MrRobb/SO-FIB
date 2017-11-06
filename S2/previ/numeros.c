#include <unistd.h>

#define MAX_SIZE 8

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

int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (esNumero(argv[i])) {
			write(1, "ES NUMERO\n", 10);
		}
		else {
			write(1, "NO ES NUMERO\n", 13);
		}
	}
}
