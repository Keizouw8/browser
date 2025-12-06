#include "../browser.h"
#include <vector>

void Browser::setState(State state){
	workspaces.resize(state.size());
	for(int i = 0; i < state.size(); i++){
		Workspace* ws = new Workspace;
		ws->pins.resize(state[i].size());
		workspaces[i] = ws;

		for(int j = 0; j < state[i].size(); j++){
			Pin* pin = new Pin;
			workspaces[i]->pins[j] = pin;
			workspaces[i]->pins[j]->title = state[i][j].title;
			workspaces[i]->pins[j]->url = state[i][j].url;
		}
	}
}

State Browser::getState(){
	State state;
	state.resize(workspaces.size());

	for(int i = 0; i < workspaces.size(); i++){
		state[i].resize(workspaces[i]->pins.size());
		for(int j = 0; j < workspaces[i]->pins.size(); j++) state[i][j] = {
			.title = workspaces[i]->pins[j]->title,
			.url = workspaces[i]->pins[j]->url
		};
	}

	return state;
}
