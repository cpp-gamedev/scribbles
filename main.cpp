#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <assert.h>
#include <fstream>
#include <filesystem>

#include "lib/env.h"

namespace
{
size_t randomRange(size_t min, size_t max)
{
	static std::random_device device;
	static std::default_random_engine engine(device());
	std::uniform_int_distribution<> dist(min, max);
	return dist(engine);
}

std::string to_lowercase(const std::string_view word)
{
	std::string lowercased(word);
	std::transform(word.begin(), word.end(), lowercased.begin(), tolower);
	return lowercased;
}

std::vector<std::string> initialize_combolist(std::stringstream& combo_names)
{
	std::vector<std::string> combo_list;
	std::string combo_name;
	while (getline(combo_names, combo_name, ' '))
	{
		combo_list.push_back(combo_name);
	}

	return combo_list;
}

std::vector<std::string> initialize_wordlist(const std::filesystem::path& wordlist_path)
{
	std::ifstream wordlist;
	std::vector<std::string> words;
	wordlist.open(wordlist_path, std::ios_base::in);

	std::string current_line = "";

	while (wordlist.good())
	{
		getline(wordlist, current_line);
		words.push_back(current_line);
	}

	wordlist.close();

	return words;
}

void display_rules()
{
	std::cout << "> RULES: \n";
	std::cout << "> 1. If a number is guessed number of tries goes down by 1\n";
	std::cout << "> 2. If a character that is guessed is not in the word \n";
	std::cout << "     the number of tries goes down by 1\n\n";
}

void start_screen()
{
	std::cout << "\n== HANGMAN ==\n";
	std::cout << "> Press 0 to quit at any time\n\n";
	std::cout << "> OBJECTIVE: \n";
	std::cout << "> Guess the word before running out of tries\n\n";
	display_rules();
}

void ask_for_input(char* dest)
{
	std::string word;
	std::cout << "> ";
	std::cin >> word;

	assert(!word.empty() && "I need a letter though");
	char first_letter = word.at(0);
	*dest = tolower(first_letter);
	std::cout << "\n";
}

void update_letters_used(std::vector<int>& score, size_t pos)
{
	score[pos]++;
}

void fill_letter(const std::string& word, std::string& hangman, size_t pos)
{
	hangman[pos] = word[pos];
}

void display_next_combo_name(size_t tries, const std::vector<std::string>& combolist)
{
	size_t combolist_size = combolist.size();

	if (tries < combolist_size)
	{
		std::cout << combolist[tries] << '\n';
	}
	else
	{
		std::cout << combolist[(combolist_size - 1)] << '\n';
	}
}
} // namespace

int main()
{
	Env finder(std::filesystem::current_path());

	PathSearch to_find;
	to_find.push_back(std::filesystem::path("data/words.txt"));

	std::filesystem::path wordlist_path = finder.findUpwards(finder.GetExeDirectory(), to_find, 5);

	char user_input = ' ';

	size_t failed_attempts = 0;

	size_t correct_letters_guessed = 0;

	// combo system
	// combo names displayed when letter is correctly guessed
	std::stringstream success_combo_names("NICE! ALRIGHT! YESS! AMAZING!");
	const std::vector<std::string> success_combo{initialize_combolist(success_combo_names)};

	// combo names displayed when letter is not correctly guessed
	std::stringstream failed_combo_names("ARG! DAMMIT! DARN! NOO!");
	const std::vector<std::string> failed_combos{initialize_combolist(failed_combo_names)};

	std::vector<std::string> wordlist;

	if (!wordlist_path.empty())
	{
		wordlist = initialize_wordlist(wordlist_path);
	}
	else
	{
		std::cout << "Unable to locate wordlist\nExiting...\n";
		return 1;
	}

	// Word to be guessed
	const size_t random_word_idx = randomRange(0, wordlist.size());
	const std::string_view word = wordlist.at(random_word_idx);
	const size_t len_of_word = word.size();

	// used fill a letter in hangman
	const std::string word_copy(word);

	// # of tries before game over
	const size_t tries = len_of_word + 10;

	// used to check if character guessed exists in word
	const std::string lowercased = to_lowercase(word);

	// used to draw hangman onto screen
	std::string hangman(len_of_word, '_');
	std::vector<int> chars_already_guessed(len_of_word, 0);

	// GAME LOOP
	start_screen();
	while (failed_attempts != tries)
	{
		std::cout << hangman << "\n\n";

		ask_for_input(&user_input);

		if (user_input == '0')
		{
			std::cout << "bye...\n";
			break;
		}

		// attempts to find the character
		size_t pos = lowercased.find(user_input);

		// if character exists
		if (pos != std::string::npos)
		{
			// check if given non-repeated character
			if (chars_already_guessed[pos] != 1)
			{
				// if exists update hangman interface
				update_letters_used(chars_already_guessed, pos);
				fill_letter(word_copy, hangman, pos);

				display_next_combo_name(correct_letters_guessed, success_combo);
				correct_letters_guessed++;

				size_t duplicate = lowercased.find(user_input, pos + 1);

				while (duplicate != std::string::npos)
				{
					update_letters_used(chars_already_guessed, duplicate);
					fill_letter(word_copy, hangman, duplicate);

					display_next_combo_name(correct_letters_guessed, success_combo);
					correct_letters_guessed++;

					duplicate = lowercased.find(user_input, duplicate += 1);
				}
			}
			else
			{
				std::cout << "You've guessed that already, try again\n\n";
				failed_attempts++;
			}
		}
		else if (isdigit(user_input))
		{
			display_next_combo_name(failed_attempts, failed_combos);
			failed_attempts++;
		}
		else
		{
			display_next_combo_name(failed_attempts, failed_combos);
			failed_attempts++;
		}

		if (correct_letters_guessed == len_of_word)
		{
			std::cout << word << " is the word, You WIN!!\n";
			break;
		}
	}

	if (failed_attempts == tries)
	{
		std::cout << "Better luck next time\n";
	}

	return 0;
}
