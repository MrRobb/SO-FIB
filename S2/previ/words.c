#include <stdio.h>

int		is_whitespace(char c)
{
	return (c == '\n' || c == '.' || c == ' ' || c == ',');
}

int		count_words(char *str)
{
	int	word;
	int number_words;
	int i;

	word = 0;
	number_words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!is_whitespace(str[i]) && word == 0)
		{
			++number_words;
			word = 1;
		}
		else if (is_whitespace(str[i]))
		{
			word = 0;
		}
		++i;
	}
	return (number_words);
}

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		printf("%i palabras\n", count_words(argv[1]));
	}
	return 0;
}