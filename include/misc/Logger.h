// Crack-Synth - A modular software synth
// Copyright (C) 2022  Intrets
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

#include <string>
#include <mem/LazyGlobal.h>
#include <mem/MutexedObject.h>

#include <iostream>
#include <format>
#include <cassert>
#include <chrono>

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

private:
	Level level;

public:
	template<class... Args>
	void log(Level l, std::string_view str, Args&&... args);

	void setLevel(Level l);

	void setColorError();
	void resetColorError();
	void setColorOut();
	void resetColorOut();

	Logger();
	~Logger() = default;
};

constexpr auto logger = LazyGlobal<mem::MutexedObject<Logger>>;

template<class... Args>
void Logger::log(Level l, std::string_view str, Args&&... args) {
	if (l >= this->level) {
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		auto epochTime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

		std::string timeString = "";

		std::tm tm;
		std::stringstream ss;

		ss << epochTime << " ";

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
				std::cout << std::format(str, std::forward<Args>(args)...);
				break;
			case Logger::Level::status:
				this->outColoringPimpl->setColor(Color::blue);
				std::cout << "(status)  ";
				this->outColoringPimpl->resetColor();

				std::cout << timeString << ": ";
				std::cout << std::format(str, std::forward<Args>(args)...);
				break;
			case Logger::Level::warning:
				this->outColoringPimpl->setColor(Color::yellow);
				std::cout << "(warning) ";
				this->outColoringPimpl->resetColor();

				std::cout << timeString << ": ";
				std::cout << std::format(str, std::forward<Args>(args)...);
				break;
			case Logger::Level::error:
				this->outColoringPimpl->setColor(Color::red);
				std::cerr << "(error)   ";
				this->outColoringPimpl->resetColor();

				std::cout << timeString << ": ";
				std::cerr << std::format(str, std::forward<Args>(args)...);
				break;
			case Logger::Level::fatal:
				this->outColoringPimpl->setColor(Color::magenta);
				std::cerr << "(fatal)   ";
				this->outColoringPimpl->resetColor();

				std::cerr << timeString << ": ";
				std::cerr << std::format(str, std::forward<Args>(args)...);
				break;
			default:
				assert(0);
				break;
		}
	}
}

