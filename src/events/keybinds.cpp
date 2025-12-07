#include "keybinds.h"
#include <format>
#include <iostream>

#define SHIFT(e) std::format("shift {}", e)
#ifdef __APPLE__
	#define MOD1(e) std::format("meta {}", e)
	#define MOD2(e) std::format("control {}", e)
#else
	#define MOD1(e) std::format("control {}", e)
	#define MOD2(e) std::format("alt {}", e)
#endif

_S_KeyBinds defaultKeybinds(){
	TabBinds tabBinds = {
		.selectTab1 = MOD1("1"),
		.selectTab2 = MOD1("2"),
		.selectTab3 = MOD1("3"),
		.selectTab4 = MOD1("4"),
		.selectTab5 = MOD1("5"),
		.selectTab6 = MOD1("6"),
		.selectTab7 = MOD1("7"),
		.selectTab8 = MOD1("8"),
		.selectLastTab = MOD1("9")
	};

	WorkspaceBinds workspaceBinds = {
		.selectWorkspace1 = MOD2("1"),
		.selectWorkspace2 = MOD2("2"),
		.selectWorkspace3 = MOD2("3"),
		.selectWorkspace4 = MOD2("4"),
		.selectWorkspace5 = MOD2("5"),
		.selectWorkspace6 = MOD2("6"),
		.selectWorkspace7 = MOD2("7"),
		.selectWorkspace8 = MOD2("8"),
		.selectWorkspace9 = MOD2("9"),
		.selectLastWorkspace = MOD2("0")
	};

	TabManagementBinds tabManagementBinds = {
		.refresh = MOD1("r"),
		.newTab = MOD1("t"),
		.closeTab = MOD1("w")
	};

	return {
		.toggleCompact = MOD1(SHIFT("s")),
		.settings = MOD1(","),
		.tabs = tabBinds,
		.workspaces = workspaceBinds,
		.tabManagement = tabManagementBinds
	};
}
