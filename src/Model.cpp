#include "Model.hpp"
#include "Util.hpp"

#include <fstream>
#include <vector>

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

	double x = std::stod(instruction[1]);
	double y = std::stod(instruction[2]);
	double z = std::stod(instruction[3]);

	vertices.emplace_back(Vertex(x, y, z));
}

void Model::parseFace(std::vector<std::string> const & instruction)
{
	assertParameterQuantity(instruction, 3, 4);

	Face face;

	for (auto param = instruction.begin() + 1; param != instruction.end(); param++)
	{
		face.addVertex(std::stoul(*param));
	}

	faces.push_back(std::move(face));
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
}

Model::Model() {}

Model::Model(std::string fileName)
{
	load(fileName);
}

Model::~Model() {}

Model::LoadError::LoadError(std::string const & message) : std::runtime_error("failed to load model: " + message) {}
