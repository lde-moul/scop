#ifndef SCOP_UTIL_HPP
#define SCOP_UTIL_HPP

#include <string>
#include <vector>

class Util
{
public:
	static constexpr double PI = 3.14159265358979323846;

	static float degreesToRadians(float degrees);
	static std::vector<std::string> splitString(std::string const & s, char delimiter);

	Util() = delete;

};

#endif
