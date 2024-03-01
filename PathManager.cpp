// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

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

	std::filesystem::path const& PathManager::getSoundsPath() {
		return this->paths[RESOURCE_PATH::SOUNDS];
	}

	std::filesystem::path const& PathManager::getFontsPath() {
		return this->paths[RESOURCE_PATH::FONTS];
	}

	std::filesystem::path const& PathManager::getTexturesPath() {
		return this->paths[RESOURCE_PATH::GRAPHICS];
	}

	std::filesystem::path const& PathManager::getModelsPath() {
		return this->paths[RESOURCE_PATH::MODELS];
	}

	std::filesystem::path const& PathManager::getShadersPath() {
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
