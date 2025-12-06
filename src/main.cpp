#include <ylt/struct_pack.hpp>
#include <iostream>
#include <fstream>

#include "browser.h"

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
	Browser browser;

	std::ifstream in("ws.bin", std::ios::binary);
	if(in.is_open()){
		State state;
		struct_pack::err_code err = struct_pack::deserialize_to(state, in);
		in.close();
		if(!err) browser.setState(state);
	}

	browser.start();

	State state = browser.getState();
	std::ofstream out("ws.bin", std::ios::binary);
	struct_pack::serialize_to(out, state);
	out.close();
}
