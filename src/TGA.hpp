#ifndef SCOP_TGA_HPP
#define SCOP_TGA_HPP

#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

class TGA
{
private:
	std::unique_ptr<uint8_t[]> pixels;
	uint16_t width;
	uint16_t height;
	std::ifstream file;

	int8_t readInt8();
	int16_t readInt16();
	void flip();

public:
	class LoadError : public std::runtime_error
	{
	public:
		LoadError(std::string const & message);

	};

	uint8_t const * getPixels() const;
	uint16_t getWidth() const;
	uint16_t getHeight() const;
	void load(std::string const & fileName);

	TGA(std::string const & fileName);
	TGA();
	~TGA();

};

#endif
