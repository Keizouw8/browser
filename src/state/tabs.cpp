#include "../browser.h"

void Browser::selectTab(int i){
	if(i >= workspaces[activeWorkspace]->size()) return lastTab();
	workspaces[activeWorkspace]->activeTab = i;
}

void Browser::nextTab(){
	workspaces[activeWorkspace]->activeTab++;
	if(workspaces[activeWorkspace]->activeTab >= workspaces[activeWorkspace]->size()) workspaces[activeWorkspace]->activeTab = 0;
}

void Browser::prevTab(){
	workspaces[activeWorkspace]->activeTab--;
	if(workspaces[activeWorkspace]->activeTab < 0) lastTab();
}

void Browser::lastTab(){
	workspaces[activeWorkspace]->activeTab = workspaces[activeWorkspace]->size() - 1;
}
