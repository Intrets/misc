#include "misc/OpenUrl.h"

namespace misc
{
	void openUrl(std::string path) {
#ifdef OS_WIN
		path = "start " + path;
#endif

#ifdef OS_OSX
		path = "open " + path;
#endif

#ifdef OS_UNIX
		path = "xdg-open " + path;
#endif

#ifndef ANDROID
		std::system(path.c_str());
#endif
	}
}
