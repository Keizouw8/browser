#include "browser.h"
#include <iostream>
#include <vector>

Browser::Browser(){
	window = sf::RenderWindow(sf::VideoMode({800, 600}), "browser");
	viewPort = sf::FloatRect({0, 0}, {800, 600});
	activeWorkspace = 0;

	styles = {
		.sidebarWidth = 300,
		.fonts = {
			.regular = sf::Font("assets/fonts/regular.ttf"),
			.bold = sf::Font("assets/fonts/bold.ttf"),
			.italic = sf::Font("assets/fonts/italic.ttf"),
			.bold_italic = sf::Font("assets/fonts/bold_italic.ttf")
		},
		.colors = {
			.primary = sf::Color::White,
			.secondary = sf::Color::Black,
			.tertiary = sf::Color(150, 150, 150)
		}
	};

	workspaces = {};
}

void Browser::start(){
	if(!workspaces.size()){
		Workspace* ws = new Workspace;
		workspaces.push_back(ws);
		ws->activeTab = -1;
	}
	while(window.isOpen()){
		const std::optional event = window.pollEvent();
		if(event) eventHandler(event);

		window.setView(sf::View(viewPort));
		window.clear();
		drawTabs();

		window.display();
	}
}

void Browser::eventHandler(std::optional<sf::Event> event){
	if(event->is<sf::Event::Closed>()) window.close();
	if(const auto* resized = event->getIf<sf::Event::Resized>()) viewPort = sf::FloatRect({0, 0}, sf::Vector2f(resized->size));
}

void Browser::drawTabs(){
	int i = 0;

	for (; i < workspaces[activeWorkspace]->pins.size(); i++){
		sf::Text text(workspaces[activeWorkspace]->activeTab == i ? styles.fonts.bold_italic : styles.fonts.bold, std::format("{} {}", i + 1, workspaces[activeWorkspace]->pins[i]->title), 14);
		text.setFillColor(workspaces[activeWorkspace]->pins[i]->loaded ? styles.colors.primary : styles.colors.tertiary);
		text.setPosition({ 10, 5 + 20.f * i });
		window.draw(text);
	}

	for (int j = 0; j < workspaces[activeWorkspace]->tabs.size(); j++, i++){
		sf::Text text(workspaces[activeWorkspace]->activeTab == i ? styles.fonts.italic : styles.fonts.regular, std::format("{} {}", i + 1, workspaces[activeWorkspace]->tabs[j]->title), 14);
		text.setFillColor(styles.colors.primary);
		text.setPosition({ 10, 5 + 20.f * i });
		window.draw(text);
	}

	sf::RectangleShape cover({ viewPort.size.x - styles.sidebarWidth, viewPort.size.y });
	cover.setFillColor(sf::Color::Red);
	cover.setPosition({ static_cast<float>(styles.sidebarWidth), 0 });
	window.draw(cover);
}

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
