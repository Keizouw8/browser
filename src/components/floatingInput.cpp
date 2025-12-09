#include "floatingInput.h"
#include "SFML/Graphics/Text.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/System/String.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

#include <iostream>
#include <string>

#ifdef __APPLE__
	#define MOD1(e) (e->system || e->control)
	#define MOD2(e) e->option
#else
#define MOD1(e) e->control
	#define MOD2(e) e->option
#endif

FloatingInput::FloatingInput(){
	visible = false;
	placeholder = "";
	content = "";
	cursorPosition = 0;
	displacement = 0;
	callback = NULL;
}

bool FloatingInput::active(){
	return visible;
}

void FloatingInput::handleEvent(sf::Event event){
	if(const sf::Event::KeyPressed* e = event.getIf<sf::Event::KeyPressed>()){
		if(e->code == sf::Keyboard::Key::Escape) return cancel();
		if(MOD1(e)){
			if(e->code == sf::Keyboard::Key::Left) cursorPosition = 0;
			if(e->code == sf::Keyboard::Key::Right) cursorPosition = content.size();
		}else{
			if(e->code == sf::Keyboard::Key::Left) cursorPosition--;
			if(e->code == sf::Keyboard::Key::Right) cursorPosition++;
		}
		if(cursorPosition < 0) cursorPosition = 0;
		if(cursorPosition > content.size()) cursorPosition = content.size();
	}
	if(const sf::Event::TextEntered* e = event.getIf<sf::Event::TextEntered>()){
		if(e->unicode < 128){
			char key = e->unicode;
			if(key == '\b'){
                if(cursorPosition > 0 && content.size() >= cursorPosition){
                	content.erase(--cursorPosition, 1);
                }
            }else if(key == '\n'){
            	std::cout << "pressed enter!" << std::endl;
            }else{
           		content.insert(content.begin() + cursorPosition++, key);
            }
		}
	}
}

void FloatingInput::draw(sf::RenderWindow& window, Styles& styles){
	if(!visible) return;

	sf::Vector2u winSize = window.getSize();

	float paddedHeight = styles.ui.fontSize + 2 * styles.ui.padding;

	sf::RectangleShape background({ winSize.x * 0.8f, paddedHeight });
	background.setPosition({ winSize.x * 0.1f, (winSize.y - paddedHeight) * 0.5f });
	background.setFillColor(styles.colors.secondary);
	background.setOutlineColor(styles.colors.primary);
	background.setOutlineThickness(2);

	window.draw(background);

	sf::Text text(styles.fonts.regular, "", styles.ui.inputSize);
	text.setPosition({ winSize.x * 0.1f + 10, (winSize.y - styles.ui.inputSize) * 0.5f });

	if(content.empty()){
		text.setString(placeholder);
		text.setFillColor(styles.colors.tertiary);
		return window.draw(text);
	}

	std::string caret = "█";
	std::string displayString(content);
	displayString += ' ';
	displayString.replace(cursorPosition, 1, caret);

	text.setString(sf::String::fromUtf8(displayString.begin(), displayString.end()));
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
