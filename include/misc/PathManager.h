#pragma once

#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace render
{
	namespace bwo
	{
		class Texture2D;
	}
}

typedef unsigned int GLuint;

namespace misc
{
	enum class RESOURCE_PATH
	{
		CONFIG,
		GRAPHICS,
		SHADERS,
		MODELS,
		SAVE,
		FONTS,
		SOUNDS,
	};

	enum class RESOURCE_FILE
	{
		OPTIONS,
	};

	class PathManager
	{
	private:
		std::unordered_map<RESOURCE_PATH, std::filesystem::path> paths;
		std::unordered_map<RESOURCE_FILE, std::filesystem::path> files;

	public:
		bool openFile(std::ifstream& file, RESOURCE_FILE t);
		bool openFile(std::ofstream& file, RESOURCE_FILE t);
		bool openSave(std::ifstream& file, std::string name);
		bool openSave(std::ofstream& file, std::string name);
		std::filesystem::path getSoundsPath();
		std::filesystem::path getFontsPath();
		std::filesystem::path getTexturesPath();
		std::filesystem::path getModelsPath();
		std::filesystem::path getShadersPath();

		PathManager(std::string const& root);
		~PathManager();
	};
}
