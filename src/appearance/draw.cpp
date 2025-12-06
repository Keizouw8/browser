#include "../browser.h"
#include "SFML/Graphics/Color.hpp"
#include <vector>

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
