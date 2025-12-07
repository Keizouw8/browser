#include "../browser.h"
#include "../events/keybinds.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

KeyBind strToKeybind(std::string str){
	std::stringstream ss(str);
	std::string token;

	KeyBind keybind;

	while(ss >> token){
		if(token == "control") keybind.control = true;
		else if(token == "alt") keybind.alt = true;
		else if(token == "meta") keybind.meta = true;
		else if(token == "shift") keybind.shift = true;
		else keybind.description = token;
	}

	return keybind;
}

void Browser::setKeybinds(_S_KeyBinds in){
	// Base
	keyBinds.insert({ strToKeybind(in.settings), SETTINGS });
	keyBinds.insert({ strToKeybind(in.toggleCompact), TOGGLECOMPACT });

	// Tab management
	keyBinds.insert({ strToKeybind(in.tabManagement.refresh), REFRESH });
	keyBinds.insert({ strToKeybind(in.tabManagement.newTab), NEWTAB });
	keyBinds.insert({ strToKeybind(in.tabManagement.closeTab), CLOSETAB });

	// Workspaces
	keyBinds.insert({ strToKeybind(in.workspaces.nextWorkspace), NEXTWS });
	keyBinds.insert({ strToKeybind(in.workspaces.previousWorkspace), PREVWS });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace1), WS1 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace2), WS2 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace3), WS3 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace4), WS4 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace5), WS5 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace6), WS6 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace7), WS7 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace8), WS8 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectWorkspace9), WS9 });
	keyBinds.insert({ strToKeybind(in.workspaces.selectLastWorkspace), LASTWS });

	// Tabs
	keyBinds.insert({ strToKeybind(in.tabs.nextTab), NEXTTAB });
	keyBinds.insert({ strToKeybind(in.tabs.previousTab), PREVTAB });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab1), TAB1 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab2), TAB2 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab3), TAB3 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab4), TAB4 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab5), TAB5 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab6), TAB6 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab7), TAB7 });
	keyBinds.insert({ strToKeybind(in.tabs.selectTab8), TAB8 });
	keyBinds.insert({ strToKeybind(in.tabs.selectLastTab), LASTTAB });
}
