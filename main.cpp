#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <algorithm>

namespace
{
int random_no(unsigned int range)
{
	srand(time(NULL));
	int secret_num = rand() % range;
	return secret_num;
}

std::string to_lowercase(std::string_view word)
{
	std::string lowercased = word.begin();
	std::transform(word.begin(), word.end(), lowercased.begin(), tolower);
	return lowercased;
}

void initialize_combolist(std::stringstream& combo_names, std::vector<std::string>& combo_list)
{
	std::string combo_name;
	while (getline(combo_names, combo_name, ' '))
	{
		combo_list.push_back(combo_name);
	}
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
	std::cout << "> ";
	std::cin >> *dest;
	std::cout << "\n";
}

void update_letters_used(std::vector<int>& score, int pos)
{
	score[pos]++;
}

void fill_letter(std::string& word, std::string& hangman, int pos)
{
	hangman[pos] = word[pos];
}

// used to display the next combo name
void display_combo_name(std::string combo_name)
{
	std::cout << combo_name << '\n';
}

void display_next_combo_name(int tries, std::vector<std::string>& combolist, int combolist_length)
{
	if (tries < combolist_length)
	{
		display_combo_name(combolist[tries]);
	}
	else
	{
		display_combo_name(combolist[combolist_length - 1]);
	}
}
} // namespace

int main()
{
	char usr_input = ' ';

	// # of failed attempts
	int f_tries = 0;

	// # of correctly guessed letters
	int s_tries = 0;

	const int combo_length = 4;

	// combo system
	// combo names displayed when letter is correctly guessed
	std::vector<std::string> s_combos;
	std::stringstream s_combonames("NICE! ALRIGHT! YESS! AMAZING!");
	initialize_combolist(s_combonames, s_combos);

	// combo names displayed when letter is not correctly guessed
	std::vector<std::string> f_combos;
	std::stringstream f_combonames("ARG! DAMMIT! DARN! NOO!");
	initialize_combolist(f_combonames, f_combos);

	// Word to be guessed
	std::string_view const word = "Oxygen";
	const int len_of_word = word.size();

	// used fill a letter in hangman
	std::string word_copy(word);

	// # of tries before game over
	const int tries = len_of_word + random_no(16);

	// used to check if character guessed exists in word
	const std::string lowercased = to_lowercase(word);

	// used to draw hangman onto screen
	std::string hangman(word.size(), '_');
	std::vector<int> chars_already_guessed(word.size(), 0);

	// GAME LOOP
	start_screen();
	while (f_tries != tries)
	{
		std::cout << hangman << "\n\n";

		ask_for_input(&usr_input);

		if (usr_input == '0')
		{
			std::cout << "bye...\n";
			break;
		}

		// attempts to find the character
		int pos = lowercased.find(usr_input);

		// if character exists
		if (pos != -1)
		{
			// check if given non-repeated character
			if (chars_already_guessed[pos] != 1)
			{
				// if exists update hangman interface
				update_letters_used(chars_already_guessed, pos);
				fill_letter(word_copy, hangman, pos);

				display_next_combo_name(s_tries, s_combos, combo_length);
				s_tries++;

				// check for duplicates
				int pos2 = lowercased.find(usr_input, pos + 1);

				// check if duplicate was found
				if (pos2 != -1)
				{
					update_letters_used(chars_already_guessed, pos2);
					fill_letter(word_copy, hangman, pos2);

					display_next_combo_name(s_tries, s_combos, combo_length);
					s_tries++;
				}
			}
			else
			{
				std::cout << "You've guessed that already, try again\n\n";
				f_tries++;
			}
		}
		else if (isdigit(usr_input))
		{
			display_next_combo_name(f_tries, f_combos, combo_length);
			f_tries++;
		}
		else
		{
			display_next_combo_name(f_tries, f_combos, combo_length);
			f_tries++;
		}

		if (s_tries == len_of_word)
		{
			std::cout << word << " is the word, You WIN!!\n";
			break;
		}
	}

	if (f_tries == tries)
		std::cout << "Better luck next time\n";

	return 0;
}
