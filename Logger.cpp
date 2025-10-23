// misc - A C++ library with many bad things
// Copyright (C) 2022 intrets

#include "misc/Logger.h"

#ifdef HAS_WINDOWS_PIMPL
#error HAS_WINDOWS_PIMPL already defined.
#endif

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)) && !defined(__CYGWIN__)
#define HAS_WINDOWS_PIMPL
#include <Windows.h>
#endif

#ifdef HAS_WINDOWS_PIMPL
struct WindowsWriter;

struct WindowsPimpl : Logger::ColorPimpl
{
	std::mutex mutex{};

	HANDLE handle;
	std::ostream& stream;

	std::optional<WORD> attributes;

	WindowsPimpl(DWORD type, std::ostream& stream_)
	    : stream(stream_) {
		this->handle = GetStdHandle(type);
	}

	~WindowsPimpl() = default;

	std::unique_ptr<Logger::Writer> newWriter(Logger::Level level) override;
};

struct WindowsWriter : Logger::Writer
{
	WindowsPimpl& windowsPimpl;

	Writer& write(std::string_view text) override {
		this->windowsPimpl.stream << text;
		return *this;
	}

	void setColor(Logger::Color color) override {
		if (!this->windowsPimpl.attributes.has_value()) {
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo(this->windowsPimpl.handle, &info);
			this->windowsPimpl.attributes = info.wAttributes;
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
				tassert(0);
				break;
		}

		SetConsoleTextAttribute(this->windowsPimpl.handle, c);
	}

	void resetColor() override {
		if (this->windowsPimpl.attributes.has_value()) {
			SetConsoleTextAttribute(this->windowsPimpl.handle, this->windowsPimpl.attributes.value());
			this->windowsPimpl.attributes = std::nullopt;
		}
	}

	NO_COPY(WindowsWriter);
	DEFAULT_MOVE(WindowsWriter);

	WindowsWriter(WindowsPimpl& windowsPimpl_)
	    : windowsPimpl(windowsPimpl_) {
		this->windowsPimpl.mutex.lock();
	}
	WindowsWriter() = delete;
	virtual ~WindowsWriter() {
		this->write("\n");
		this->windowsPimpl.stream.flush();
		this->windowsPimpl.mutex.unlock();
	}
};

std::unique_ptr<Logger::Writer> WindowsPimpl::newWriter(Logger::Level level) {
	return std::make_unique<WindowsWriter>(*this);
}
#endif

struct ANSIPimpl : Logger::ColorPimpl
{
	Logger::log_function out{};
	bool doColors = true;

	ANSIPimpl(Logger::log_function out_)
	    : out(std::move(out_)) {
	}
	ANSIPimpl(std::ostream& stream_) {
		this->out = [stream = &stream_](Logger::Level level, te::cstring_view str) {
			stream->write(str.getData(), str.string_view().size());
		};
	}
	~ANSIPimpl() = default;

	std::unique_ptr<Logger::Writer> newWriter(Logger::Level level) override;
};

struct ANSIWriter : Logger::Writer
{
	ANSIPimpl& ansi;
	Logger::Level level;
	te::temp_format_buffer::BufferAccess bufferAccess;

	Writer& write(std::string_view text) override {
		this->bufferAccess.append(text);
		return *this;
	}

	void setColor(Logger::Color color) override {
		if (!this->ansi.doColors) {
			return;
		}

		switch (color) {
			case Logger::Color::red:
				this->write("\033[31m");
				break;
			case Logger::Color::yellow:
				this->write("\033[33m");
				break;
			case Logger::Color::green:
				this->write("\033[32m");
				break;
			case Logger::Color::magenta:
				this->write("\033[35m");
				break;
			case Logger::Color::blue:
				this->write("\033[36m");
				break;
			default:
				tassert(0);
				break;
		}
	}

	void resetColor() override {
		if (!this->ansi.doColors) {
			return;
		}

		this->write("\033[0m");
	}

	ANSIWriter(Logger::Level level_, ANSIPimpl& ansi_, te::temp_format_buffer::BufferAccess&& bufferAccess_)
	    : ansi(ansi_),
	      level(level_),
	      bufferAccess(std::move(bufferAccess_)) {
	}

	NO_COPY(ANSIWriter);
	DEFAULT_MOVE(ANSIWriter);

	ANSIWriter() = delete;
	~ANSIWriter() {
		this->bufferAccess.append("\n");
		this->bufferAccess.append("\n");
		this->ansi.out(this->level, this->bufferAccess.sv());
	}
};

std::unique_ptr<Logger::Writer> ANSIPimpl::newWriter(Logger::Level level) {
	return std::make_unique<ANSIWriter>(level, *this, te::temp_format_buffer::getBuffer());
}
void Logger2::setLogFunctions(bool doColors, Logger::log_function out, Logger::log_function error) {
	std::unique_lock lock(this->mutex);

	auto outPimpl = std::make_unique<ANSIPimpl>(std::move(out));
	outPimpl->doColors = doColors;
	this->logger.out.push_back(std::move(outPimpl));

	auto errorPimpl = std::make_unique<ANSIPimpl>(std::move(error));
	errorPimpl->doColors = doColors;
	this->logger.error.push_back(std::move(errorPimpl));
}

Logger::Logger() {
#ifdef HAS_WINDOWS_PIMPL
	this->out.push_back(std::make_unique<WindowsPimpl>(STD_OUTPUT_HANDLE, std::cout));
	this->error.push_back(std::make_unique<WindowsPimpl>(STD_ERROR_HANDLE, std::cerr));
#else
	this->out.push_back(std::make_unique<ANSIPimpl>(std::cout));
	this->error.push_back(std::make_unique<ANSIPimpl>(std::cerr));
#endif
}

#undef HAS_WINDOWS_PIMPL
