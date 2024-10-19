#pragma once

#include <filesystem>
#include <optional>

#include <tepp/try_catch.h>

namespace misc
{
#ifdef ANDROID
	inline std::optional<std::filesystem::path> getAppDataFolder(std::initializer_list<std::filesystem::path> subPaths) noexcept {
		return std::nullopt;
	}
#else
	inline std::optional<std::filesystem::path> getAppDataFolder(std::initializer_list<std::filesystem::path> subPaths) noexcept {
		try {
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

			std::filesystem::path path = pathString;

			for (auto& subPath : subPaths) {
				path /= subPath;
			}

			std::filesystem::create_directories(path);

			return path;
		} catch (std::filesystem::filesystem_error const&) {
			return std::nullopt;
		}
	}
#endif

	inline std::optional<std::filesystem::path> getAppDataFile(std::initializer_list<std::filesystem::path> subPaths, std::filesystem::path file) noexcept {
		if (auto path = getAppDataFolder(subPaths)) {
			return TRY_CATCH(path.value() / file);
		}
		else {
			return std::nullopt;
		}
	}
}