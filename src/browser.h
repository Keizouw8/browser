#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "styles.h"

struct Tab{
	std::string title;
};

struct Pin : Tab{
	bool loaded;
	std::string url;
};

struct Workspace{
	int activeTab = -1;
	std::vector<Pin*> pins;
	std::vector<Tab*> tabs;
};

struct _S_Pin{
	std::string title;
	std::string url;
};

using State = std::vector<std::vector<_S_Pin>>;

class Browser{
	private:
		sf::RenderWindow window;
		sf::FloatRect viewPort;
		std::vector<Workspace*> workspaces;
		Styles styles;
		int activeWorkspace;
		void eventHandler(std::optional<sf::Event> event);
		void drawTabs();

	public:
		Browser();
		void setState(State state);
		State getState();
		void start();
};
