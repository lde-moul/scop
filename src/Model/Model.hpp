#ifndef SCOP_MODEL_HPP
#define SCOP_MODEL_HPP

#include "Face.hpp"
#include "Vertex.hpp"

// #include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Model
{
private:
	std::vector<Vertex> vertices;
	std::vector<Face> faces;

	std::string removeComment(std::string const & line);
	void loadInstruction(std::ifstream & file, std::vector<std::vector<std::string>> & instructions);
	std::vector<std::vector<std::string>> loadInstructions(std::string const & fileName);
	void assertParameterQuantity(std::vector<std::string> const & instruction, size_t min, size_t max);
	void parseVertex(std::vector<std::string> const & instruction);
	void parseFace(std::vector<std::string> const & instruction);
	Vector getCenter() const;
	void recenter();

public:
	class LoadError : public std::runtime_error
	{
	public:
		LoadError(std::string const & message);

	};

	std::vector<float> getVerticesAsArray() const;
	std::vector<unsigned int> getFacesAsArray() const;
	void load(std::string fileName);

	Model();
	Model(std::string fileName);
	~Model();

};

#endif
