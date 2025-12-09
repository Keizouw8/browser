#include <ylt/struct_pack.hpp>
#include <ylt/struct_yaml/yaml_reader.h>
#include <ylt/struct_yaml/yaml_writer.h>
#include <iostream>
#include <fstream>

#include "browser.h"
#include "events/keybinds.h"

#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <limits.h>
    #include <unistd.h>
#endif

void setWorkingDirectory() {
#ifdef __APPLE__
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::filesystem::path executable = path;
        std::filesystem::current_path(executable.parent_path());
    }
#endif
}

State defaultState = {
	{
		{ .title = "DAR Canvas", .url = "https://davidsongifted.instructure.com" },
		{ .title = "UNR Canvas", .url = "https://webcampus.unr.edu" },
		{ .title = "UNR Library", .url = "https://library.unr.edu" }
	},
	{
		{ .title = "Github", .url = "https://www.github.com" },
		{ .title = "Stack Overflow", .url = "https://www.stackoverflow.com" }
	},
	{
		{ .title = "Youtube", .url = "https://www.youtube.com" },
		{ .title = "Spotify", .url = "https://open.spotify.com" }
	}
};

int main(int argv, char* argc[]){
	setWorkingDirectory();

	Browser browser;

	std::ifstream ws_in("ws.bin", std::ios::binary);
	if(ws_in.is_open()){
		State state;
		struct_pack::err_code err = struct_pack::deserialize_to(state, ws_in);
		ws_in.close();
		if(!err) browser.setState(state);
	}

	std::ifstream styles_in("config/styles.yaml");
	if(styles_in.is_open()){
		_S_Styles styles;
		std::string stylesContent((std::istreambuf_iterator<char>(styles_in)), std::istreambuf_iterator<char>());
		struct_yaml::from_yaml(styles, stylesContent);
		browser.setStyles(styles);
	}

	std::ifstream keybinds_in("config/keybinds.yaml");
	if(keybinds_in.is_open()){
		_S_KeyBinds keybinds;
		std::string keybindsContent((std::istreambuf_iterator<char>(keybinds_in)), std::istreambuf_iterator<char>());
		struct_yaml::from_yaml(keybinds, keybindsContent);
		keybinds_in.close();
		browser.setKeybinds(keybinds);
	}else{
		_S_KeyBinds keybinds = defaultKeybinds();
		std::string ss;
		struct_yaml::to_yaml(keybinds, ss);
		std::ofstream keybinds_out("config/keybinds.yaml");
		keybinds_out << ss;
		keybinds_out.close();
		browser.setKeybinds(keybinds);
	}

	browser.start();

	State state = browser.getState();
	std::ofstream saveFile("ws.bin", std::ios::binary);
	struct_pack::serialize_to(saveFile, state);
	saveFile.close();
}
