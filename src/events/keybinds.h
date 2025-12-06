#include <string>
#include <unordered_map>
#include <ylt/struct_yaml/yaml_reader.h>
#include <ylt/struct_yaml/yaml_writer.h>

#ifndef Keybinds
#define Keybinds

enum BindPoints{
	NEXTTAB, PREVTAB, TAB1, TAB2, TAB3, TAB4, TAB5, TAB6, TAB7, TAB8, LASTTAB,
	NEXTWS, PREVWS, WS1, WS2, WS3, WS4, WS5, WS6, WS7, WS8, WS9, LASTWS,
	REFRESH, NEWTAB, CLOSETAB
};

struct KeyBind{
	bool meta;
	bool control;
	bool alt;
	bool shift;
	std::string description = "===UNDEFINED===";
	bool operator==(const KeyBind& other) const{
        return meta == other.meta &&
               control == other.control &&
               alt == other.alt &&
               shift == other.shift &&
               description == other.description;
    }
};

struct KeyBindHash {
    std::size_t operator()(const KeyBind& k) const {
        std::size_t h1 = std::hash<std::string>{}(k.description);
        std::size_t h2 = (static_cast<std::size_t>(k.meta)    << 0) |
                         (static_cast<std::size_t>(k.control) << 1) |
                         (static_cast<std::size_t>(k.alt)     << 2) |
                         (static_cast<std::size_t>(k.shift)   << 3);
        return h1 ^ (h2 << 1);
    }
};

struct TabBinds{
	std::string nextTab;
	std::string previousTab;
	std::string selectTab1;
	std::string selectTab2;
	std::string selectTab3;
	std::string selectTab4;
	std::string selectTab5;
	std::string selectTab6;
	std::string selectTab7;
	std::string selectTab8;
	std::string selectLastTab;
};

struct WorkspaceBinds{
	std::string nextWorkspace;
	std::string previousWorkspace;
	std::string selectWorkspace1;
	std::string selectWorkspace2;
	std::string selectWorkspace3;
	std::string selectWorkspace4;
	std::string selectWorkspace5;
	std::string selectWorkspace6;
	std::string selectWorkspace7;
	std::string selectWorkspace8;
	std::string selectWorkspace9;
	std::string selectLastWorkspace;
};

struct TabManagementBinds{
	std::string refresh;
	std::string newTab;
	std::string closeTab;
};

struct _S_KeyBinds{
	std::string toggleCompact;
	std::string settings;
	TabBinds tabs;
	WorkspaceBinds workspaces;
	TabManagementBinds tabManagement;
};

using KeyBinds = std::unordered_map<KeyBind, BindPoints, KeyBindHash>;

_S_KeyBinds defaultKeybinds();

#endif
