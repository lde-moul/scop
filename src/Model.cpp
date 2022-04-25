#include "Model.hpp"
#include "Util.hpp"

#include <fstream>
#include <vector>

#include <iostream> // !!!

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
		throw Model::LoadError();
	}

	std::vector<std::string> && params = Util::splitString(line, ' ');
	instructions.push_back(std::move(params));
}

std::vector<std::vector<std::string>> Model::loadInstructions(std::string const & fileName)
{
	std::ifstream file(fileName);
	if (file.fail())
	{
		throw Model::LoadError();
	}

	std::vector<std::vector<std::string>> instructions;
	while (!file.eof())
	{
		loadInstruction(file, instructions);
	}

	return instructions;
}

void Model::load(std::string fileName)
{
	std::vector<std::vector<std::string>> && instructions = loadInstructions(fileName);

	// for (auto & instruction : instructions)
	// {
	// 	for (auto & param : instruction)
	// 		std::cout << param << ' ';
	// 	std::cout << std::endl;
	// }

	auto poop = Util::splitString("aa bb cc", ' ');
	for (auto & pee : poop)
		std::cout << pee << ' ';
}

Model::Model() {}

Model::Model(std::string fileName)
{
	load(fileName);
}

Model::~Model()
{
}

Model::LoadError::LoadError() : std::runtime_error("failed to load model") {}
