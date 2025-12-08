#include "floatingInput.h"
#include "SFML/Graphics/Text.hpp"
#include <SFML/Graphics.hpp>

FloatingInput::FloatingInput(){
	visible = false;
	placeholder = "";
	content = "";
	cursorPosition = 0;
	displacement = 0;
	callback = NULL;
}

void FloatingInput::draw(sf::RenderWindow& window, Styles& styles){
	sf::Vector2u winSize = window.getSize();

	sf::RectangleShape background({ winSize.x * 0.8f, 40 });
	background.setPosition({ winSize.x * 0.1f, (winSize.y - 40) * 0.5f });
	background.setFillColor(styles.colors.secondary);
	background.setOutlineColor(styles.colors.primary);
	background.setOutlineThickness(2);

	window.draw(background);

	sf::Text text(styles.fonts.regular, "", 20);
	text.setPosition({ winSize.x * 0.1f + 10, (winSize.y - 25) * 0.5f });

	if(content.empty()){
		text.setString(placeholder);
		text.setFillColor(styles.colors.tertiary);
		return window.draw(text);
	}

	text.setString(content);
	text.setFillColor(styles.colors.primary);

	window.draw(text);
}

void FloatingInput::setPlaceholder(std::string ph){
	placeholder = ph;
}

void FloatingInput::setCallback(void (*cb)()){
	callback = cb;
}

void FloatingInput::reveal(){
	content = "";
	cursorPosition = 0;
	displacement = 0;
	visible = true;
}

void FloatingInput::cancel(){
	reset();
	visible = false;
}

void FloatingInput::reset(){
	placeholder = "";
	content = "";
	cursorPosition = 0;
	displacement = 0;
	callback = NULL;
}
