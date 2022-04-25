#include "Util.hpp"

#include <sstream>

std::vector<std::string> Util::splitString(std::string const & s, char delimiter)
{
	std::istringstream stream(s);

	std::vector<std::string> words;
	while (true)
	{
		std::string word;
		std::getline(stream, word, delimiter);

		if (stream.eof())
		{
			break;
		}

		words.push_back(std::move(word));
	}

	return words;
}
