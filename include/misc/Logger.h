#pragma once

#include <mem/LazyGlobal.h>
#include <mem/MutexedObject.h>

#include <cassert>
#include <chrono>
#include <format>
#include <iostream>
#include <shared_mutex>
#include <sstream>
#include <string>

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

	using log_function = std::function<void(Logger::Level, te::cstring_view)>;

	enum class Color
	{
		red,
		yellow,
		green,
		magenta,
		blue,
	};

	struct Writer
	{
		virtual Writer& write(std::string_view text) = 0;

		virtual void setColor(Color color) = 0;
		virtual void resetColor() = 0;

		Writer() = default;
		virtual ~Writer() = default;
	};

	struct ColorPimpl
	{
		virtual std::unique_ptr<Writer> newWriter(Logger::Level level) = 0;

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
			{
				auto writer = this->out->newWriter(l);

				writer->setColor(Color::green);
				writer->write("(info)    ");
				writer->resetColor();

				writer->write(timeString).write(": ").write(message);
			} break;
			case Logger::Level::status:
			{
				auto writer = this->out->newWriter(l);

				writer->setColor(Color::blue);
				writer->write("(status)  ");
				writer->resetColor();

				writer->write(timeString).write(": ").write(message);

			} break;
			case Logger::Level::warning:
			{
				auto writer = this->out->newWriter(l);

				writer->setColor(Color::yellow);
				writer->write("(warning) ");
				writer->resetColor();

				writer->write(timeString).write(": ").write(message);
			} break;
			case Logger::Level::error:
			{
				auto writer = this->error->newWriter(l);

				writer->setColor(Color::red);
				writer->write("(error)   ");
				writer->resetColor();

				writer->write(timeString).write(": ").write(message);

			} break;
			case Logger::Level::fatal:
			{
				auto writer = this->error->newWriter(l);

				writer->setColor(Color::magenta);
				writer->write("(fatal)   ");
				writer->resetColor();

				writer->write(timeString).write(": ").write(message);

			} break;
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

	std::shared_mutex mutex{};
	Logger logger{};

	void setLogFunctions(bool doColors, Logger::log_function out, Logger::log_function error);
};

constexpr auto logger = LazyGlobal<Logger2>;

#define LOGTYPE(type, ...) \
	do { \
		if (logger->level.load(std::memory_order_relaxed) >= Logger::Level::type) { \
			std::shared_lock lock(logger->mutex); \
			logger->logger.log2(Logger::Level::type, __VA_ARGS__); \
		} \
	} while (0)

#define LOGINFO(...) LOGTYPE(info, __VA_ARGS__)
#define LOGSTATUS(...) LOGTYPE(status, __VA_ARGS__)
#define LOGWARNING(...) LOGTYPE(warning, __VA_ARGS__)
#define LOGERROR(...) LOGTYPE(error, __VA_ARGS__)
#define LOGFATAL(...) LOGTYPE(fatal, __VA_ARGS__)
