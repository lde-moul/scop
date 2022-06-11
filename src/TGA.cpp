#include "TGA.hpp"

#include <cstring>

int8_t TGA::readInt8()
{
	int8_t n;
	file.read(reinterpret_cast<char*>(&n), 1);
	return n;
}

int16_t TGA::readInt16()
{
	int16_t n;
	file.read(reinterpret_cast<char*>(&n), 2);
	return n;
}

void TGA::flip()
{
	size_t lineLength = width * 3;
	auto swapLine = std::unique_ptr<uint8_t[]>(new uint8_t[lineLength]);

	for (size_t y = 0; y < height / 2; y++)
	{
		size_t top = y * lineLength;
		size_t bottom = (height - y - 1) * lineLength;
		std::memcpy(swapLine.get(), &pixels[top], lineLength);
		std::memcpy(&pixels[top], &pixels[bottom], lineLength);
		std::memcpy(&pixels[bottom], swapLine.get(), lineLength);
	}
}

uint16_t TGA::getWidth() const
{
	return width;
}

uint16_t TGA::getHeight() const
{
	return height;
}

uint8_t const * TGA::getPixels() const
{
	return pixels.get();
}

void TGA::load(std::string const & fileName)
{
	try
	{
		file.open(fileName, std::ios::binary);
		file.exceptions(std::ios::failbit | std::ios::eofbit);
		if (file.fail())
		{
			throw TGA::LoadError("cannot open file");
		}

		int8_t idLength = readInt8();

		if (readInt8() != 0)
		{
			throw TGA::LoadError("color maps are unsupported");
		}

		if (readInt8() != 2)
		{
			throw TGA::LoadError("unsupported image type");
		}

		readInt16();
		readInt16();
		readInt8();

		readInt16();
		readInt16();

		width = readInt16();
		height = readInt16();

		if (readInt8() != 24)
		{
			throw TGA::LoadError("unsupported pixel depth");
		}
		if (readInt8() != 32)
		{
			throw TGA::LoadError("unsupported pixel format");
		}

		file.read(nullptr, idLength);

		size_t length = width * height * 3;
		pixels = std::unique_ptr<uint8_t[]>(new uint8_t[length]);
		file.read(reinterpret_cast<char*>(pixels.get()), length);
		flip();

		file.close();
	}
	catch (std::ios::failure)
	{
		throw TGA::LoadError("cannot read file");
	}
}

TGA::TGA(std::string const & fileName)
{
	load(fileName);
}

TGA::TGA() {}

TGA::~TGA() {}

TGA::LoadError::LoadError(std::string const & message) : std::runtime_error("failed to load TGA file: " + message) {}
