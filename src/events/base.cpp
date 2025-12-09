#include "../browser.h"
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
#endif

void Browser::openSettings(){
	#ifdef _WIN32
		HINSTANCE result = ShellExecute(NULL, "open", "config", NULL, NULL, SW_SHOWNORMAL);
		if(result <= 32) std::cerr << "Error opening config. Error code: " << (int)result << std::endl;
	#elif __APPLE__
		int result = std::system("open config");
		if(result == -1) std::cerr << "Error opening config." << std::endl;
	#else
		int result = std::system("xdg-open config");
		if(result == -1) std::cerr << "Error opening config." << std::endl;
	#endif
}

void Browser::toggleCompact(){
	compactMode = !compactMode;
}
