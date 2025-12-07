#include "../browser.h"

void Browser::selectWorkspace(int i){
	if(i >= workspaces.size()) return lastWorkspace();
	activeWorkspace = i;
}

void Browser::nextWorkspace(){
	activeWorkspace++;
	if(activeWorkspace >= workspaces.size()) activeWorkspace = 0;
}

void Browser::prevWorkspace(){
	activeWorkspace--;
	if(activeWorkspace < 0) lastTab();
}

void Browser::lastWorkspace(){
	activeWorkspace = workspaces.size() - 1;
}
