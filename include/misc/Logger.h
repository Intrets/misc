#pragma once

#include <mem/LazyGlobal.h>
#include <mem/MutexedObject.h>
#include <string>

#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <sstream>

#include <tepp/temp_format.h>

struct LoggerOutputInterface
{
};

struct Logger
{
	enum class Level
	{
		info,
		status,
		warning,
		error,
		fatal
	};

	enum class Color
	{
		red,
		yellow,
		green,
		magenta,
		blue,
	};

	struct ColorPimpl
	{
		virtual void start() {
		}
		virtual void end() {
		}
		virtual ColorPimpl& write(std::string_view text) = 0;
		virtual void setColor(Color color) = 0;
		virtual void resetColor() = 0;

		ColorPimpl() = default;
		virtual ~ColorPimpl() = default;
	};

	std::unique_ptr<ColorPimpl> out;
	std::unique_ptr<ColorPimpl> error;

public:
	template<class... Args>
	void log(Level l, std::string_view str, Args&&... args);

	template<class... Args>
	void log2(Level l, std::format_string<Args...> const fmt, Args&&... args) {
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		auto epochTime = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		auto epochTimeSeconds = epochTime / 1000;
		auto epochTimeMillis = epochTime % 1000;

		std::string timeString = "";

		std::tm tm;
		std::stringstream ss;

		ss << std::format("{}.{:04d}", epochTimeSeconds, epochTimeMillis) << " ";

#ifndef ANDROID
		if (localtime_s(&tm, &time) == 0) {
			ss << std::put_time(&tm, "%c");
		}
#endif

		timeString = ss.str();
		auto message = te::temp_format(fmt, std::forward<Args>(args)...);

		switch (l) {
			case Logger::Level::info:
				this->out->start();

				this->out->setColor(Color::green);
				this->out->write("(info)    ");
				this->out->resetColor();

				this->out->write(timeString).write(": ").write(message);

				this->out->end();
				break;
			case Logger::Level::status:
				this->out->start();

				this->out->setColor(Color::blue);
				this->out->write("(status)  ");
				this->out->resetColor();

				this->out->write(timeString).write(": ").write(message);

				this->out->end();
				break;
			case Logger::Level::warning:
				this->out->start();

				this->out->setColor(Color::yellow);
				this->out->write("(warning) ");
				this->out->resetColor();

				this->out->write(timeString).write(": ").write(message);

				this->out->end();
				break;
			case Logger::Level::error:
				this->error->start();

				this->error->setColor(Color::red);
				this->error->write("(error)   ");
				this->error->resetColor();

				this->error->write(timeString).write(": ").write(message);

				this->error->end();
				break;
			case Logger::Level::fatal:
				this->error->start();

				this->error->setColor(Color::magenta);
				this->error->write("(fatal)   ");
				this->error->resetColor();

				this->error->write(timeString).write(": ").write(message);

				this->error->end();
				break;
			default:
				assert(0);
				break;
		}
	}

	Logger();
	~Logger() = default;
};

struct Logger2
{
	std::atomic<Logger::Level> level = Logger::Level::fatal;

	Logger logger;

	template<class... Args>
	void log(Logger::Level l, std::string_view str, Args&&... args);
	template<class... Args>
	void logInfo(std::string_view str, Args&&... args);
	template<class... Args>
	void logStatus(std::string_view str, Args&&... args);
	template<class... Args>
	void logWarning(std::string_view str, Args&&... args);
	template<class... Args>
	void logError(std::string_view str, Args&&... args);
	template<class... Args>
	void logFatal(std::string_view str, Args&&... args);
};

constexpr auto logger = LazyGlobal<Logger2>;

#define LOGTYPE(type, ...) \
	do { \
		if (logger->level.load(std::memory_order_relaxed) >= Logger::Level::type) { \
			logger->logger.log2(Logger::Level::type, __VA_ARGS__); \
		} \
	} while (0)

#define LOGINFO(...) LOGTYPE(info, __VA_ARGS__)
#define LOGSTATUS(...) LOGTYPE(status, __VA_ARGS__)
#define LOGWARNING(...) LOGTYPE(warning, __VA_ARGS__)
#define LOGERROR(...) LOGTYPE(error, __VA_ARGS__)
#define LOGFATAL(...) LOGTYPE(fatal, __VA_ARGS__)


template<class... Args>
void Logger::log(Level l, std::string_view str, Args&&... args) {
	auto now = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(now);
	auto epochTime = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	auto epochTimeSeconds = epochTime / 1000;
	auto epochTimeMillis = epochTime % 1000;

	std::string timeString = "";

	std::tm tm;
	std::stringstream ss;

	ss << std::format("{}.{:04d}", epochTimeSeconds, epochTimeMillis) << " ";

#ifndef ANDROID
	if (localtime_s(&tm, &time) == 0) {
		ss << std::put_time(&tm, "%c");
	}
#endif

	timeString = ss.str();

	switch (l) {
		case Logger::Level::info:
			this->out->setColor(Color::green);
			std::cout << "(info)    ";
			this->out->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::status:
			this->out->setColor(Color::blue);
			std::cout << "(status)  ";
			this->out->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::warning:
			this->out->setColor(Color::yellow);
			std::cout << "(warning) ";
			this->out->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::error:
			this->error->setColor(Color::red);
			std::cerr << "(error)   ";
			this->error->resetColor();

			std::cerr << timeString << ": ";
			std::cerr << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::fatal:
			this->error->setColor(Color::magenta);
			std::cerr << "(fatal)   ";
			this->error->resetColor();

			std::cerr << timeString << ": ";
			std::cerr << std::vformat(str, std::make_format_args(args...));
			break;
		default:
			assert(0);
			break;
	}
}

template<class... Args>
inline void Logger2::log(Logger::Level l, std::string_view str, Args&&... args) {
	if (this->level.load(std::memory_order_relaxed) >= l) {
		// this->logger.acquire()->log(l, str, std::forward<Args>(args)...);
	}
}

template<class... Args>
inline void Logger2::logInfo(std::string_view str, Args&&... args) {
	this->log(Logger::Level::info, str, std::forward<Args>(args)...);
}

template<class... Args>
inline void Logger2::logWarning(std::string_view str, Args&&... args) {
	this->log(Logger::Level::warning, str, std::forward<Args>(args)...);
}

template<class... Args>
inline void Logger2::logStatus(std::string_view str, Args&&... args) {
	this->log(Logger::Level::status, str, std::forward<Args>(args)...);
}

template<class... Args>
inline void Logger2::logError(std::string_view str, Args&&... args) {
	this->log(Logger::Level::error, str, std::forward<Args>(args)...);
}

template<class... Args>
inline void Logger2::logFatal(std::string_view str, Args&&... args) {
	this->log(Logger::Level::fatal, str, std::forward<Args>(args)...);
	assert(0);
}
