#ifndef SCOP_MODEL_HPP
#define SCOP_MODEL_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Model
{
private:
	void loadInstruction(std::ifstream & file, std::vector<std::vector<std::string>> & instructions);
	std::vector<std::vector<std::string>> loadInstructions(std::string const & fileName);
	// std::vector<shared_ptr<Vertex>> vertices;

public:
	class LoadError : public std::runtime_error
	{
	public:
		LoadError();
	};

	void load(std::string fileName);

	Model();
	Model(std::string fileName);
	~Model();
};

#endif
