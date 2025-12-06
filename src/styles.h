#include <SFML/Graphics.hpp>

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
