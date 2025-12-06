#include "../browser.h"
#include "SFML/Window/Keyboard.hpp"
#include "keybinds.h"
#include <vector>

void Browser::eventHandler(std::optional<sf::Event> event){
	if(event->is<sf::Event::Closed>()) window.close();
	if(const auto* resized = event->getIf<sf::Event::Resized>()) viewPort = sf::FloatRect({0, 0}, sf::Vector2f(resized->size));
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
		KeyBind key = {
			.meta = keyPressed->system,
			.control = keyPressed->control,
			.alt = keyPressed->alt,
			.shift = keyPressed->shift,
			.description = sf::Keyboard::getDescription(keyPressed->scancode)
		};

		// if(MOD1){
		// 	if(isDigit){
		// 		if(digit == 0 || digit > workspaces[activeWorkspace]->size()){
		// 			workspaces[activeWorkspace]->activeTab = workspaces[activeWorkspace]->size() - 1;
		// 		}else if(digit){
		// 			workspaces[activeWorkspace]->activeTab = digit - 1;
		// 		}
		// 	}
		// }
		// if(MOD2){
		// 	if(isDigit){
		// 		if(digit == 0 || digit > workspaces.size()){
		// 			activeWorkspace = workspaces.size() - 1;
		// 		}else if(digit){
		// 			activeWorkspace = digit - 1;
		// 		}
		// 	}
		// }
	}
}
