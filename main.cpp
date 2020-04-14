#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

namespace
{
std::string to_lowercase(std::string_view word)
{
	std::string lowercased = word.begin();
	std::transform(word.begin(), word.end(), lowercased.begin(), tolower);
	return lowercased;
}
} // namespace

int main()
{
	std::string_view const test = "Heyo\n";
	std::string lowercased_test = to_lowercase(test);

	std::cout << lowercased_test;
	return 0;
}