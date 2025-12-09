#include "../browser.h"
#include "SFML/Graphics/Color.hpp"
#include <vector>
#include <iostream>

void Browser::drawTabs(){
	int i = 0;
	Workspace* ws = workspaces[activeWorkspace];

	for (; i < ws->pins.size(); i++){
		if(ws->pins[i]->loaded) std::cout << "loaded!" << std::endl;
		sf::Text text(ws->activeTab == i ? styles.fonts.bold_italic : styles.fonts.bold, std::format("{} {}", i + 1, ws->pins[i]->title), styles.ui.fontSize);
		text.setFillColor(ws->pins[i]->loaded ? styles.colors.primary : styles.colors.tertiary);
		text.setPosition({ (float)styles.ui.padding, 0.5f * styles.ui.padding * (i + 1) + styles.ui.fontSize * i });
		window.draw(text);
	}

	for (int j = 0; j < ws->tabs.size(); j++, i++){
		sf::Text text(ws->activeTab == i ? styles.fonts.italic : styles.fonts.regular, std::format("{} {}", i + 1, ws->tabs[j]->title), styles.ui.fontSize);
		text.setFillColor(styles.colors.primary);
		text.setPosition({ (float)styles.ui.padding, 0.5f * styles.ui.padding * (i + 1) + styles.ui.fontSize * i });
		window.draw(text);
	}
}

void Browser::drawWorkspaces(){
	float paddedHeight = styles.ui.inputSize + styles.ui.padding;
	sf::RectangleShape cover({ (float)styles.sidebarWidth, paddedHeight });
	cover.setFillColor(styles.colors.secondary);
	cover.setPosition({ 0, viewPort.size.y - paddedHeight });
	window.draw(cover);

	size_t ws_length = workspaces.size();

	for (int i = 0; i < ws_length; i++){
		sf::Text text(styles.fonts.bold, std::format("{}", i + 1), styles.ui.fontSize);
		text.setFillColor(activeWorkspace == i ? styles.colors.primary : styles.colors.tertiary);
		text.setPosition({ 0.5f*(styles.sidebarWidth - paddedHeight * ws_length) + paddedHeight*i + styles.ui.padding, viewPort.size.y - styles.ui.inputSize - 0.5f * styles.ui.padding });
		window.draw(text);
	}
}
