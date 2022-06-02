#ifndef SCOP_GLERROR_HPP
#define SCOP_GLERROR_HPP

#include <stdexcept>
#include <string>

class GLError : public std::runtime_error
{
public:
	GLError(std::string const & message);

};

#endif
