// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

#pragma once

#ifdef LIB_MEM

#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <array>
#include <optional>

#include "IOWrapped.h"

#include <mem/Global.h>

namespace misc
{
	class _OptionValueBase;

	enum class OPTION
	{
		LO_TICKSPERSECOND,
		GR_RENDERTHREAD,
		GR_FRAMESYNCMODE,
		GR_DEBUG,
		GR_FRAMERATE,
		CL_VIEWPORTSCALE,
		UI_SCALE,
		OPTIONS2_MAX
	};


	class OptionManager
	{
	private:
		std::array<std::unique_ptr<_OptionValueBase>, static_cast<size_t>(OPTION::OPTIONS2_MAX)> data;
		std::unordered_map<std::string, OPTION> nameMap;

		void defaultValues();

		template<class T>
		void initVal(OPTION option, T val, std::string name, std::string description);

	public:
		template<class T>
		T getVal(OPTION option);

		template<class T>
		void setVal(OPTION option, T val);

		void toggle(OPTION option);

		void readFromFile();
		void writeToFile();

		OptionManager();
		~OptionManager();
	};

	template<OPTION A, class T>
	class Option
	{
	public:
		static T getVal();
		static void setVal(T val);
		static void toggle();
	};

	template<OPTION A, class T>
	inline T Option<A, T>::getVal() {
		return Global<OptionManager>->getVal<T>(A);
	}

	template<OPTION A, class T>
	inline void Option<A, T>::setVal(T val) {
		Global<OptionManager>->setVal(A, val);
	}

	template<OPTION A, class T>
	inline void Option<A, T>::toggle() {
		static_assert(std::is_same_v<T, bool>);
		Global<OptionManager>->toggle(A);
	}

	class _OptionValueBase
	{
	private:
		std::string name;
		std::string description;

		friend class OptionManager;

	public:
		std::string getName();
		std::string getDescription();
		std::string toString();
		virtual std::ostream& toStream(std::ostream& out) = 0;

		virtual std::string set(std::string) {
			return "read only";
		};

		_OptionValueBase(std::string name_, std::string description_) : name(name_), description(description_) {
		};

		virtual ~_OptionValueBase() = default;
	};

	template <typename T>
	class OptionValue : public _OptionValueBase
	{
	private:
		T val;

		friend class OptionManager;

	public:
		OptionValue(T val_, std::string name, std::string description) : _OptionValueBase(name, description),
			val(val_) {
		};

		T getVal() {
			return this->val;
		};
		void setVal(T val_) {
			this->val = val_;
		};

		void toggle() {
			static_assert(std::is_same_v<T, bool>);
			this->val = !this->val;
		}

		virtual std::string set(std::string) override;
		std::string type();

		virtual std::ostream& toStream(std::ostream& out) override {
			out << *this;
			return out;
		}
	};

	template<typename T>
	inline std::ostream& operator<< (std::ostream& out, OptionValue<T>& D) {
		out << D.getName() << " " << D.type() << " " << D.getVal();
		return out;
	}

	template<class T>
	inline T OptionManager::getVal(OPTION option) {
		return static_cast<OptionValue<T>*>(this->data[static_cast<size_t>(option)].get())->val;
	}

	template<class T>
	inline void OptionManager::setVal(OPTION option, T val) {
		static_cast<OptionValue<T>*>(this->data[static_cast<size_t>(option)].get())->setVal(val);
	}

	template<class T>
	inline void OptionManager::initVal(OPTION option, T val, std::string name, std::string description) {
		this->data[static_cast<size_t>(option)] = std::make_unique<OptionValue<T>>(val, name, description);
		this->nameMap[name] = option;
	}

	template<typename T>
	inline std::string OptionValue<T>::set(std::string str) {
		std::stringstream in(str);
		try {
			in >> this->val;
			std::stringstream out;
			out << this->val;
			return "set value to: " + out.str();
		}
		catch (std::exception) {
			return "failed to parse input";
		}
	}

	template<typename T>
	inline std::string OptionValue<T>::type() {
		return "type info not implemented";
	}
}
#endif
