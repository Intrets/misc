// misc - A C++ library with many bad things
// Copyright (C) 2022 intrets

#pragma once

#include <mem/LazyGlobal.h>
#include <mem/MutexedObject.h>
#include <string>

#include <cassert>
#include <chrono>
#include <format>
#include <iostream>

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
		virtual void setColor(Color color) = 0;
		virtual void resetColor() = 0;

		ColorPimpl() = default;
		virtual ~ColorPimpl() = default;
	};

	std::unique_ptr<ColorPimpl> outColoringPimpl;
	std::unique_ptr<ColorPimpl> errorColoringPimpl;

public:
	template<class... Args>
	void log(Level l, std::string_view str, Args&&... args);

	void setColorError();
	void resetColorError();
	void setColorOut();
	void resetColorOut();

	Logger();
	~Logger() = default;
};

struct Logger2
{
	std::atomic<Logger::Level> level = Logger::Level::fatal;

	mem::MutexedObject<Logger> logger;

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

	if (localtime_s(&tm, &time) == 0) {
		ss << std::put_time(&tm, "%c");
	}

	timeString = ss.str();

	switch (l) {
		case Logger::Level::info:
			this->outColoringPimpl->setColor(Color::green);
			std::cout << "(info)    ";
			this->outColoringPimpl->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::status:
			this->outColoringPimpl->setColor(Color::blue);
			std::cout << "(status)  ";
			this->outColoringPimpl->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::warning:
			this->outColoringPimpl->setColor(Color::yellow);
			std::cout << "(warning) ";
			this->outColoringPimpl->resetColor();

			std::cout << timeString << ": ";
			std::cout << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::error:
			this->errorColoringPimpl->setColor(Color::red);
			std::cerr << "(error)   ";
			this->errorColoringPimpl->resetColor();

			std::cerr << timeString << ": ";
			std::cerr << std::vformat(str, std::make_format_args(args...));
			break;
		case Logger::Level::fatal:
			this->errorColoringPimpl->setColor(Color::magenta);
			std::cerr << "(fatal)   ";
			this->errorColoringPimpl->resetColor();

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
		this->logger.acquire()->log(l, str, std::forward<Args>(args)...);
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
