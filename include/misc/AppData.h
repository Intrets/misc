#pragma once

#include <filesystem>
#include <optional>

namespace misc
{
	inline std::optional<std::filesystem::path> getAppDataFolder(std::filesystem::path subPath) {
		char* buffer = nullptr;
		size_t size;
		auto err = _dupenv_s(&buffer, &size, "AppData");
		if (err || size == 0) {
			return std::nullopt;
		}

		if (buffer == nullptr) {
			return std::nullopt;
		}

		std::string pathString(buffer, size - 1);
		free(buffer);

		std::filesystem::path path = pathString / subPath;

		std::filesystem::create_directories(path);

		return path;
	}
}