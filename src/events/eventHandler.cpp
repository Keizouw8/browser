#include "../browser.h"
#include "SFML/Window/Keyboard.hpp"
#include "keybinds.h"
#include <iostream>

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

		if(keyBinds.contains(key)){
			performCommand(keyBinds[key]);
		}
	}
}
