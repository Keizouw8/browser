#include <SFML/Graphics.hpp>

#ifndef STYLES
#define STYLES

struct Fonts{
	sf::Font regular;
	sf::Font bold;
	sf::Font italic;
	sf::Font bold_italic;
};

struct Colors{
	sf::Color primary;
	sf::Color secondary;
	sf::Color tertiary;
};

struct Styles{
	int sidebarWidth;
	Fonts fonts;
	Colors colors;
};

struct _S_Fonts{
	std::string regular;
	std::string bold;
	std::string italic;
	std::string bold_italic;
};

struct _S_Colors{
	std::string primary;
	std::string secondary;
	std::string tertiary;
};

struct _S_Styles{
	int sidebarWidth;
	_S_Fonts fonts;
	_S_Colors colors;
};

#endif
