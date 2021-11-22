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

#include "PathManager.h"

#include <fstream>
#include <string>

namespace misc
{
	bool PathManager::openFile(std::ifstream& file, RESOURCE_FILE t) {
		file.open(this->files[t]);
		return file.is_open();
	}

	bool PathManager::openFile(std::ofstream& file, RESOURCE_FILE t) {
		file.open(this->files[t]);
		return file.is_open();
	}

	bool PathManager::openSave(std::ifstream& file, std::string name) {
		file.open(this->paths[RESOURCE_PATH::SAVE] / name, std::ifstream::binary);
		return file.is_open();
	}

	bool PathManager::openSave(std::ofstream& file, std::string name) {
		file.open(this->paths[RESOURCE_PATH::SAVE] / name, std::ofstream::binary);
		return file.is_open();
	}

	std::filesystem::path PathManager::getSoundsPath() {
		return this->paths[RESOURCE_PATH::SOUNDS];
	}

	std::filesystem::path PathManager::getFontsPath() {
		return this->paths[RESOURCE_PATH::FONTS];
	}

	std::filesystem::path PathManager::getTexturesPath() {
		return this->paths[RESOURCE_PATH::GRAPHICS];
	}

	std::filesystem::path PathManager::getModelsPath() {
		return this->paths[RESOURCE_PATH::MODELS];
	}

	std::filesystem::path PathManager::getShadersPath() {
		return this->paths[RESOURCE_PATH::SHADERS];
	}

	PathManager::PathManager(std::string const& root_) {
		std::filesystem::path root = root_;
		this->paths[RESOURCE_PATH::CONFIG] = root / "config";
		this->paths[RESOURCE_PATH::GRAPHICS] = root / "graphics";
		this->paths[RESOURCE_PATH::SAVE] = root / "saves";
		this->files[RESOURCE_FILE::OPTIONS] = root / "config" / "options.txt";
		this->paths[RESOURCE_PATH::FONTS] = root / "graphics" / "fonts";
		this->paths[RESOURCE_PATH::SOUNDS] = root / "sound";
		this->paths[RESOURCE_PATH::MODELS] = root / "graphics" / "models";
		this->paths[RESOURCE_PATH::SHADERS] = root / "graphics" / "shaders";
	}

	PathManager::~PathManager() {
	}
}
