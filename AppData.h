#pragma once

#include <filesystem>
#include <optional>

namespace misc
{
	void setAppDataFolder(std::filesystem::path path) noexcept;
	std::optional<std::filesystem::path> getAppDataFolder(std::initializer_list<std::filesystem::path> subPaths) noexcept;
	std::optional<std::filesystem::path> getAppDataFile(std::initializer_list<std::filesystem::path> subPaths, std::filesystem::path file) noexcept;
}