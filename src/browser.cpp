#include "browser.h"
#include "SFML/Graphics/Color.hpp"
#include <iostream>
#include <vector>

#ifdef __APPLE__
	#define MOD1 keyPressed->system
	#define MOD2 keyPressed->control
#else
	#define MOD1 keyPressed->control
	#define MOD2 keyPressed->alt
#endif

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

		sf::RectangleShape background({ viewPort.size.x, viewPort.size.y });
		background.setFillColor(styles.colors.secondary);
		window.draw(background);

		drawTabs();
		drawWorkspaces();

		window.display();
	}
}

void Browser::eventHandler(std::optional<sf::Event> event){
	if(event->is<sf::Event::Closed>()) window.close();
	if(const auto* resized = event->getIf<sf::Event::Resized>()) viewPort = sf::FloatRect({0, 0}, sf::Vector2f(resized->size));
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
		int code = static_cast<int>(keyPressed->code);
		int digit = code - 26;
		bool isDigit = code > 25 && code < 36;

		if(MOD1){
			if(isDigit){
				if(digit == 0 || digit > workspaces.size()){
					activeWorkspace = workspaces.size() - 1;
				}else if(digit){
					activeWorkspace = digit - 1;
				}
			}
		}
		if(MOD2){
			if(isDigit){
				if(digit == 0 || digit > workspaces[activeWorkspace]->size()){
					workspaces[activeWorkspace]->activeTab = workspaces[activeWorkspace]->size() - 1;
				}else if(digit){
					workspaces[activeWorkspace]->activeTab = digit - 1;
				}
			}
		}
	}
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

void Browser::drawWorkspaces(){
	sf::RectangleShape cover({ static_cast<float>(styles.sidebarWidth), 30 });
	cover.setFillColor(styles.colors.secondary);
	cover.setPosition({ 0, viewPort.size.y - 30 });
	window.draw(cover);

	size_t ws_length = workspaces.size();

	for (int i = 0; i < ws_length; i++){
		sf::Text text(styles.fonts.bold, std::format("{}", i + 1), 14);
		text.setFillColor(activeWorkspace == i ? styles.colors.primary : styles.colors.tertiary);
		text.setPosition({ 0.5f*(styles.sidebarWidth-24*ws_length)+24*i+8, viewPort.size.y - 22 });
		window.draw(text);
	}
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
