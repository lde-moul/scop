#include "GLError.hpp"

GLError::GLError(std::string const & message) : std::runtime_error("OpenGL error: " + message) {}
