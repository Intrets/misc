// misc - A C++ library with many bad things
// Copyright (C) 2021  Intrets
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
