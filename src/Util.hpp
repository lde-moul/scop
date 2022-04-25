#ifndef SCOP_UTIL_HPP
#define SCOP_UTIL_HPP

#include <string>
#include <vector>

class Util
{
public:
	static std::vector<std::string> splitString(std::string const & s, char delimiter);

	Util() = delete;

};

#endif
