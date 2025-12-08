#ifndef FLOATINGINPUT
#define FLOATINGINPUT

#include <SFML/Graphics.hpp>
#include <string>
#include "../appearance/styles.h"

class FloatingInput{
	private:
		bool visible;
		std::string placeholder;
		std::string content;
		int cursorPosition;
		int displacement;
		void (*callback)();
		void reset();
	public:
		FloatingInput();
		void setPlaceholder(std::string placeholder);
		void setCallback(void (*callback)());
		void draw(sf::RenderWindow& window, Styles& styles);
		void reveal();
		void cancel();
};

#endif
