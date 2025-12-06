#include "../browser.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include <iostream>

sf::Color hexToColor(std::string hexColor) {
    if (hexColor[0] == '#') hexColor.erase(0, 1);

    if (hexColor.length() != 6 && hexColor.length() != 8) {
        std::cerr << "Error: Invalid hex color string length: " << hexColor << std::endl;
        return sf::Color::Black;
    }

    if (hexColor.length() == 6) hexColor += "FF";

    unsigned int combinedValue;
    std::stringstream ss;
    ss << std::hex << hexColor;
    ss >> combinedValue;

    uint8_t r = static_cast<uint8_t>((combinedValue >> 24) & 0xFF);
    uint8_t g = static_cast<uint8_t>((combinedValue >> 16) & 0xFF);
    uint8_t b = static_cast<uint8_t>((combinedValue >> 8) & 0xFF);
    uint8_t a = static_cast<uint8_t>(combinedValue & 0xFF);

    return sf::Color(r, g, b, a);
}

void Browser::setStyles(_S_Styles in){
	styles.sidebarWidth = in.sidebarWidth;
	styles.fonts = {
		.regular = sf::Font(in.fonts.regular),
		.bold = sf::Font(in.fonts.bold),
		.italic = sf::Font(in.fonts.italic),
		.bold_italic = sf::Font(in.fonts.bold_italic)
	};
	styles.colors = {
		.primary = hexToColor(in.colors.primary),
		.secondary = hexToColor(in.colors.secondary),
		.tertiary = hexToColor(in.colors.tertiary)
	};
}
