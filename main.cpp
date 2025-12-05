#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <ranges>

#define WS_LIMIT 10
#define TAB_LIMIT 256

struct Tab{
	std::string title;
};

struct Pin : Tab{
	std::string url;
	bool loaded;
};

struct _S_Pin{
	std::string url;
	std::string title;
};

struct _S_Workspace{
	_S_Pin pins[TAB_LIMIT];
	size_t length;
};

struct State{
	_S_Workspace workspaces[WS_LIMIT];
	size_t length;
};

struct Workspace{
	std::vector<Pin*> pinnedTabs;
	std::vector<Tab*> tabs;
	int activeTab = 0;
};

struct Styles{
	int sidebarWidth;
	sf::Font font;
};

class Browser{
	private:
		sf::RenderWindow window;
		sf::FloatRect viewPort;
		std::vector<Workspace*> workspaces;
		Styles styles;
		int activeTab;

		void eventHandler(std::optional<sf::Event> event){
			if(event->is<sf::Event::Closed>()) window.close();
			if(const auto* resized = event->getIf<sf::Event::Resized>()) viewPort = sf::FloatRect({0, 0}, sf::Vector2f(resized->size));
		}

		void drawTabs(){
			// for (int i = 0; i < tabs.size(); i++){
			// 	sf::Text text(styles.font, std::format("{} {}", i + 1, tabs[i].title), 14);
			// 	text.setPosition({ 10, 5 + 20.f * i });
			// 	window.draw(text);
			// }

			sf::RectangleShape cover({ viewPort.size.x - styles.sidebarWidth, viewPort.size.y });
			cover.setFillColor(sf::Color::Red);
			cover.setPosition({ static_cast<float>(styles.sidebarWidth), 0 });
			window.draw(cover);
		}
	
	public:
		Browser(){
			window = sf::RenderWindow(sf::VideoMode({800, 600}), "browser");
			viewPort = sf::FloatRect({0, 0}, {800, 600});
			activeTab = 0;

			styles = {
				.sidebarWidth = 300,
				.font = sf::Font("regular.ttf")
			};

			workspaces = {};
		}

		void setState(State state){
			for(int i = 0; i < state.length; i++){
				std::cout << state.workspaces[i].length << std::endl;
				for(int j = 0; j < state.workspaces[i].length; j++){
					std::cout << state.workspaces[i].pins[j].title << ", " << state.workspaces[i].pins[j].url << std::endl;
				}
			}
		}
		
		State getState(){
			State state;
			return state;
		}

		void start(){
			while(window.isOpen()){
				const std::optional event = window.pollEvent();
				eventHandler(event);

				window.setView(sf::View(viewPort));
				window.clear();
				drawTabs();

				window.display();
			}
		}
};

State defaultState = {
	.length = 3,
	.workspaces = {
		{
			.length = 3,
			.pins = {
				{ .title = "DAR Canvas", .url = "https://davidsongifted.instructure.com" },
				{ .title = "UNR Canvas", .url = "https://webcampus.unr.edu" },
				{ .title = "UNR Library", .url = "https://library.unr.edu" }
			}
		},
		{
			.length = 2,
			.pins = {
				{ .title = "Github", .url = "https://www.github.com" },
				{ .title = "Stack Overflow", .url = "https://www.stackoverflow.com" },
			}
		},
		{
			.length = 2,
			.pins = {
				{ .title = "Youtube", .url = "https://www.youtube.com" },
				{ .title = "Spotify", .url = "https://open.spotify.com" },
			}
		}
	}
};

int main(int argv, char* argc[]){
	Browser browser;

	std::ifstream saveState("ws.bin", std::ios::binary);
	if(saveState.is_open()){
		std::cout << "file's there" << std::endl;
		State state;
		saveState.read(reinterpret_cast<char*>(&state), sizeof(state));
		saveState.close();
		std::cout << state.workspaces[0].pins[0].url << std::endl;
		browser.setState(state);
	}
	
	browser.start();

	State state = browser.getState();
	std::ofstream out("ws.bin", std::ios::binary);
	out.write(reinterpret_cast<char*>(&state), sizeof(state));
	out.close();
}