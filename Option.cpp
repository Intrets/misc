// misc - A C++ library with many bad things
// Copyright (C) 2021  Intrets
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

#include "Option.h"

#ifdef LIB_MEM

#include <mem/Global.h>

#include <fstream>

#include "StringHelpers.h"
#include "PathManager.h"

namespace misc
{
	void OptionManager::defaultValues() {
		initVal(OPTION::CL_VIEWPORTSCALE, 36.0f, "cl_viewportscale", "");
		initVal(OPTION::GR_DEBUG, true, "gr_debug", "");
		initVal<int32_t>(OPTION::GR_FRAMESYNCMODE, 0, "gr_framesyncmode", "");
		initVal(OPTION::UI_SCALE, 1.0f, "ui_scale", "");
		initVal(OPTION::GR_RENDERTHREAD, false, "gr_renderthread", "seperate render and game logic threads");
		initVal<int32_t>(OPTION::LO_TICKSPERSECOND, 60, "lo_tickspersecond", "logic ticks per second");
		initVal<int32_t>(OPTION::GR_FRAMERATE, 60, "gr_framerate", "target framerate");
	}

	void OptionManager::toggle(OPTION option) {
		static_cast<OptionValue<bool>*>(this->data[static_cast<size_t>(option)].get())->toggle();
	}

	void OptionManager::readFromFile() {
		std::ifstream file;

		if (Global<PathManager>->openFile(file, RESOURCE_FILE::OPTIONS)) {
			std::string line;
			while (std::getline(file, line)) {
				std::vector<std::string> parts;
				split(0, line, parts);

				if (parts.size() < 3) {
					continue;
				}

				std::string name = parts[0];
				auto f = nameMap.find(name);

				if (f == nameMap.end()) {
					continue;
				}

				OPTION optionIndex = f->second;

				data[static_cast<size_t>(optionIndex)]->set(parts[2]);
			}
			file.close();
		}
	}

	void OptionManager::writeToFile() {
		std::ofstream file;
		if (Global<PathManager>->openFile(file, RESOURCE_FILE::OPTIONS)) {
			for (auto& obj : data) {
				file << obj->toString() << "\n";
			}
			file.close();
		}
	}

	OptionManager::OptionManager() {
		defaultValues();
		readFromFile();
	}

	OptionManager::~OptionManager() {
	}

	std::string _OptionValueBase::getName() {
		return name;
	}

	std::string _OptionValueBase::getDescription() {
		return description;
	}

	std::string _OptionValueBase::toString() {
		std::stringstream out;
		toStream(out);
		return out.str();
	}
}
#endif
