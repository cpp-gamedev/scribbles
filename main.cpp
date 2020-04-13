#include <iostream>
#include <string.h>

#define MAX_LENGTH 30

void to_lowercase(char* word);

int main()
{
	char word[MAX_LENGTH];

	std::cout << "Enter a word: ";
	std::cin >> word;

	to_lowercase(word);

	std::cout << word << '\n';
	return 0;
}

void to_lowercase(char* word)
{
	int i = 0;

	while (*word != '\0')
	{
		word[i] = tolower(word[i]);
		++word;
	}
}
