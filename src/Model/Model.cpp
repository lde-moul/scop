#include "Model.hpp"
#include "../Util.hpp"
#include "../Vector.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>

std::vector<float> Model::getVerticesAsArray() const
{
	std::vector<float> array;

	for (auto const & vertex : vertices)
	{
		Vector pos = vertex.getPosition();
		array.push_back(pos.x);
		array.push_back(pos.y);
		array.push_back(pos.z);

		Vector texCoord = vertex.getTextureCoordinates();
		array.push_back(texCoord.x);
		array.push_back(texCoord.y);
	}

	return array;
}

std::vector<unsigned int> Model::getFacesAsArray() const
{
	std::vector<unsigned int> array;

	for (auto const & face : faces)
	{
		for (auto const & id : face.getVertexIDs())
		{
			array.push_back(id - 1);
		}
	}

	return array;
}

Vector Model::getCenter() const
{
	constexpr float floatMin = std::numeric_limits<float>::min();
	constexpr float floatMax = std::numeric_limits<float>::max();
	auto corner1 = Vector(floatMax, floatMax, floatMax);
	auto corner2 = Vector(floatMin, floatMin, floatMin);

	for (auto const & vertex : vertices)
	{
		Vector pos1 = vertex.getPosition();
		float x1 = std::min(pos1.x, corner1.x);
		float y1 = std::min(pos1.y, corner1.y);
		float z1 = std::min(pos1.z, corner1.z);
		corner1 = Vector(x1, y1, z1, pos1.w);

		Vector pos2 = vertex.getPosition();
		float x2 = std::max(pos2.x, corner2.x);
		float y2 = std::max(pos2.y, corner2.y);
		float z2 = std::max(pos2.z, corner2.z);
		corner2 = Vector(x2, y2, z2, pos2.w);
	}

	return (corner1 + corner2) / 2;
}

std::string Model::removeComment(std::string const & line)
{
	std::vector<std::string> && parts = Util::splitString(line, '#');
	if (parts.size() > 0)
	{
		return parts[0];
	}
	else
	{
		return "";
	}
}

void Model::loadInstruction(std::ifstream & file, std::vector<std::vector<std::string>> & instructions)
{
	std::string line;
	std::getline(file, line);

	if (file.eof())
	{
		return;
	}
	else if (file.fail())
	{
		throw Model::LoadError("cannot read file");
	}

	std::string && uncommentedLine = removeComment(line);
	std::vector<std::string> && params = Util::splitString(std::move(uncommentedLine), ' ');
	instructions.push_back(std::move(params));
}

std::vector<std::vector<std::string>> Model::loadInstructions(std::string const & fileName)
{
	std::ifstream file(fileName);
	if (file.fail())
	{
		throw Model::LoadError("cannot open file");
	}

	std::vector<std::vector<std::string>> instructions;
	while (!file.eof())
	{
		loadInstruction(file, instructions);
	}

	return instructions;
}

void Model::assertParameterQuantity(std::vector<std::string> const & instruction, size_t min, size_t max)
{
	size_t numParams = instruction.size() - 1;

	if (min == max && numParams != min)
	{
		throw Model::LoadError("expected " + std::to_string(min) + " parameters but got " + std::to_string(numParams));
	}
	else if (numParams < min)
	{
		throw Model::LoadError("expected at least " + std::to_string(min) + " parameters but got " + std::to_string(numParams));
	}
	else if (numParams > max)
	{
		throw Model::LoadError("expected at most " + std::to_string(max) + " parameters but got " + std::to_string(numParams));
	}
}

void Model::parseVertex(std::vector<std::string> const & instruction)
{
	assertParameterQuantity(instruction, 3, 3);

	float x = std::stof(instruction[1]);
	float y = std::stof(instruction[2]);
	float z = std::stof(instruction[3]);

	vertices.emplace_back(Vertex(Vector(x, y, z)));
}

void Model::parseFace(std::vector<std::string> const & instruction)
{
	assertParameterQuantity(instruction, 3, 4);

	Face face;
	for (auto param = instruction.begin() + 1; param != instruction.end(); param++)
	{
		face.addVertex(std::stoul(*param));
	}

	std::vector<Face> subFaces = face.getTriangulatedFaces();
	for (auto const & subFace : subFaces)
	{
		faces.push_back(std::move(subFace));
	}
}

void Model::recenter()
{
	Vector center = getCenter();
	for (auto & vertex : vertices)
	{
		vertex.setPosition(vertex.getPosition() - center);
	}
}

void Model::calculateTextureCoordinates()
{
	Vector center = getCenter();
	for (auto & vertex : vertices)
	{
		Vector normal = (vertex.getPosition() - center).normalize();
		float s = std::asin(normal.x) / Util::PI + 0.5f;
		float t = std::asin(normal.y) / Util::PI + 0.5f;
		vertex.setTextureCoordinates(Vector(s, t));
	}
}

void Model::load(std::string fileName)
{
	std::vector<std::vector<std::string>> && instructions = loadInstructions(fileName);

	for (auto const & instruction : instructions)
	{
		if (instruction.size() == 0 || instruction[0] == "o")
		{
			continue;
		}
		else if (instruction[0] == "v")
		{
			parseVertex(instruction);
		}
		else if (instruction[0] == "f")
		{
			parseFace(instruction);
		}
	}

	recenter();
	calculateTextureCoordinates();
}

Model::Model() {}

Model::Model(std::string fileName)
{
	load(fileName);
}

Model::~Model() {}

Model::LoadError::LoadError(std::string const & message) : std::runtime_error("failed to load model: " + message) {}
