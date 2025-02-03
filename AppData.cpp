#include "misc/AppData.h"

#include <mem/LazyGlobal.h>
#include <mem/MutexedObject.h>

#include <tepp/try_catch.h>

namespace misc
{
	struct AppDataFolder
	{
		std::optional<std::filesystem::path> pathOverride{};

		std::optional<std::filesystem::path> getPath() const;
		void setPath(std::filesystem::path path);
		void clearPath();
	};

	std::optional<std::filesystem::path> AppDataFolder::getPath() const {
		return this->pathOverride;
	}

	void AppDataFolder::setPath(std::filesystem::path path) {
		this->pathOverride = path;
	}

	void AppDataFolder::clearPath() {
		this->pathOverride.reset();
	}

	void setAppDataFolder(std::filesystem::path path) noexcept {
		LazyGlobal<mem::MutexedObject<AppDataFolder>>->acquire()->setPath(path);
	}

	std::optional<std::filesystem::path> getAppDataFolder(std::initializer_list<std::filesystem::path> subPaths) noexcept {
		auto appDataPath = LazyGlobal<mem::MutexedObject<AppDataFolder>>->acquire()->getPath();

		try {
			if (appDataPath.has_value()) {
				for (auto& subPath : subPaths) {
					appDataPath.value() /= subPath;
				}

				std::filesystem::create_directories(appDataPath.value());

				return appDataPath;
			}
			else {
#ifdef OS_WIN
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
#else
				return std::nullopt;
#endif
			}
		} catch (std::filesystem::filesystem_error const&) {
			return std::nullopt;
		}
	}

	std::optional<std::filesystem::path> getAppDataFile(std::initializer_list<std::filesystem::path> subPaths, std::filesystem::path file) noexcept {
		if (auto path = getAppDataFolder(subPaths)) {
			return TRY_CATCH(path.value() / file);
		}
		else {
			return std::nullopt;
		}
	}
}