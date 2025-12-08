#include "browser.h"
#include <vector>

Browser::Browser(){
	window = sf::RenderWindow(sf::VideoMode({800, 600}), "browser");
	viewPort = sf::FloatRect({0, 0}, {800, 600});
	activeWorkspace = 0;
	workspaces = {};
}

void Browser::start(){
	if(!workspaces.size()){
		Workspace* ws = new Workspace;
		workspaces.push_back(ws);
		ws->activeTab = -1;
	}

	input.reveal();
	input.setPlaceholder("Placeholder");

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
		input.draw(window, styles);

		window.display();
	}
}
