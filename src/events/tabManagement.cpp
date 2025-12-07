#include "../browser.h"

void Browser::newTab(){
	Tab* tab = new Tab;
	tab->title = "New tab";
	workspaces[activeWorkspace]->tabs.push_back(tab);
	lastTab();
}

void Browser::closeTab(){}
void Browser::refresh(){}
