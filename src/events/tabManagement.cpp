#include "../browser.h"

void Browser::newTab(){
	Tab* tab = new Tab;
	tab->title = "New tab";
	workspaces[activeWorkspace]->tabs.push_back(tab);
	lastTab();
}

void Browser::closeTab(){
	Workspace* ws = workspaces[activeWorkspace];
	if(ws->activeTab < 0) return;
	if(ws->activeTab < ws->pins.size()){
		ws->pins[ws->activeTab]->loaded = false;
		for(; ws->activeTab < ws->pins.size(); ws->activeTab++) if(ws->pins[ws->activeTab]->loaded) break;
	}else{
		int i = ws->activeTab - ws->pins.size();
		ws->tabs.erase(ws->tabs.begin() + i);
	}
	if(ws->activeTab < ws->size()) return;
	ws->activeTab = ws->size() - 1;
	if(ws->activeTab >= ws->pins.size()) return;
	for(ws->activeTab--; ws->activeTab >= 0; ws->activeTab--);
}

void Browser::refresh(){}
