// misc - A C++ library with many bad things
// Copyright (C) 2022 intrets

#include "include/misc/Logger.h"

#ifdef HAS_WINDOWS_PIMPL
#error HAS_WINDOWS_PIMPL already defined.
#endif

#if (defined(WIN32) || defined(_WIN32) || defined (_WIN64)|| defined(__WIN32__) || defined(__WINDOWS__)) && !defined(__CYGWIN__)
#define HAS_WINDOWS_PIMPL
#include <Windows.h>
#endif

#ifdef HAS_WINDOWS_PIMPL
struct WindowsPimpl : Logger::ColorPimpl
{
	HANDLE handle;

	std::optional<WORD> attributes;

	void setColor(Logger::Color color) override {
		if (!this->attributes.has_value()) {
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(this->handle, &info);
			this->attributes = info.wAttributes;
		}

		WORD c = 0;
		switch (color) {
			case Logger::Color::red:
				c = FOREGROUND_RED;
				break;
			case Logger::Color::yellow:
				c = FOREGROUND_GREEN | FOREGROUND_RED;
				break;
			case Logger::Color::green:
				c = FOREGROUND_GREEN;
				break;
			case Logger::Color::magenta:
				c = FOREGROUND_RED | FOREGROUND_BLUE;
				break;
			case Logger::Color::blue:
				c = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				break;
			default:
				assert(0);
				break;
		}
		SetConsoleTextAttribute(this->handle, c);
	}

	void resetColor() override {
		if (this->attributes.has_value()) {
			SetConsoleTextAttribute(this->handle, this->attributes.value());
			this->attributes = std::nullopt;
		}
	}

	WindowsPimpl(DWORD type) {
		this->handle = GetStdHandle(type);
	}

	~WindowsPimpl() = default;
};
#endif

struct ANSIPimpl : Logger::ColorPimpl
{
	std::ostream& stream;

	void setColor(Logger::Color color) override {
		switch (color) {
			case Logger::Color::red:
				this->stream << "\033[31m";
				break;
			case Logger::Color::yellow:
				this->stream << "\033[33m";
				break;
			case Logger::Color::green:
				this->stream << "\033[32m";
				break;
			case Logger::Color::magenta:
				this->stream << "\033[35m";
				break;
			case Logger::Color::blue:
				this->stream << "\033[36m";
				break;
			default:
				assert(0);
				break;
		}
	}

	void resetColor() override {
		this->stream << "\033[0m";
	}

	ANSIPimpl(std::ostream& stream_) : stream(stream_) {
	}
	~ANSIPimpl() = default;
};

Logger::Logger() {
#ifdef HAS_WINDOWS_PIMPL
	this->outColoringPimpl = std::make_unique<WindowsPimpl>(STD_OUTPUT_HANDLE);
	this->errorColoringPimpl = std::make_unique<WindowsPimpl>(STD_ERROR_HANDLE);
#else
	this->outColoringPimpl = std::make_unique<ANSIPimpl>(std::cout);
	this->errorColoringPimpl = std::make_unique<ANSIPimpl>(std::cerr);
#endif
}

#undef HAS_WINDOWS_PIMPL
