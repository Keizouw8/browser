#include "SFML/Graphics/Color.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ylt/struct_pack.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

#define WS_LIMIT 10
#define TAB_LIMIT 256

struct Tab{
	std::string title;
};

struct Pin : Tab{
	bool loaded;
	std::string url;
};

struct _S_Pin{
	std::string title;
	std::string url;
};

struct _S_Workspace{
	size_t length;
	_S_Pin pins[TAB_LIMIT];
};

struct State{
	size_t length;
	_S_Workspace workspaces[WS_LIMIT];
};

struct Workspace{
	int activeTab;
	std::vector<Pin*> pins;
	std::vector<Tab*> tabs;
};

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

class Browser{
	private:
		sf::RenderWindow window;
		sf::FloatRect viewPort;
		std::vector<Workspace*> workspaces;
		Styles styles;
		int activeWorkspace;

		void eventHandler(std::optional<sf::Event> event){
			if(event->is<sf::Event::Closed>()) window.close();
			if(const auto* resized = event->getIf<sf::Event::Resized>()) viewPort = sf::FloatRect({0, 0}, sf::Vector2f(resized->size));
		}

		void drawTabs(){
			int i = 0;

			for (; i < workspaces[activeWorkspace]->pins.size(); i++){
				sf::Text text(workspaces[activeWorkspace]->activeTab == i ? styles.fonts.bold_italic : styles.fonts.bold, std::format("{} {}", i + 1, workspaces[activeWorkspace]->pins[i]->title), 14);
				text.setFillColor(workspaces[activeWorkspace]->pins[i]->loaded ? styles.colors.primary : styles.colors.tertiary);
				text.setPosition({ 10, 5 + 20.f * i });
				window.draw(text);
			}

			for (int j = 0; j < workspaces[activeWorkspace]->tabs.size(); j++, i++){
				sf::Text text(workspaces[activeWorkspace]->activeTab == i ? styles.fonts.italic : styles.fonts.regular, std::format("{} {}", i + 1, workspaces[activeWorkspace]->tabs[j]->title), 14);
				text.setFillColor(styles.colors.primary);
				text.setPosition({ 10, 5 + 20.f * i });
				window.draw(text);
			}

			sf::RectangleShape cover({ viewPort.size.x - styles.sidebarWidth, viewPort.size.y });
			cover.setFillColor(sf::Color::Red);
			cover.setPosition({ static_cast<float>(styles.sidebarWidth), 0 });
			window.draw(cover);
		}

	public:
		Browser(){
			window = sf::RenderWindow(sf::VideoMode({800, 600}), "browser");
			viewPort = sf::FloatRect({0, 0}, {800, 600});
			activeWorkspace = 0;

			styles = {
				.sidebarWidth = 300,
				.fonts = {
					.regular = sf::Font("assets/fonts/regular.ttf"),
					.bold = sf::Font("assets/fonts/bold.ttf"),
					.italic = sf::Font("assets/fonts/italic.ttf"),
					.bold_italic = sf::Font("assets/fonts/bold_italic.ttf")
				},
				.colors = {
					.primary = sf::Color::White,
					.secondary = sf::Color::Black,
					.tertiary = sf::Color(150, 150, 150)
				}
			};

			workspaces = {};
		}

		void setState(State state){
			for(int i = 0; i < state.length; i++){
				Workspace* ws = new Workspace;
				workspaces.push_back(ws);
				ws->activeTab = -1;

				for(int j = 0; j < state.workspaces[i].length; j++){
					Pin* pin = new Pin;
					workspaces[i]->pins.push_back(pin);
					workspaces[i]->pins[j]->title = state.workspaces[i].pins[j].title;
					workspaces[i]->pins[j]->url = state.workspaces[i].pins[j].url;
				}
			}
		}

		State getState(){
			State state = { .length = workspaces.size() };

			for(int i = 0; i < state.length; i++){
				state.workspaces[i] = { .length = workspaces[i]->pins.size() };
				for(int j = 0; j < state.workspaces[i].length; j++) state.workspaces[i].pins[j] = {
					.title = workspaces[i]->pins[j]->title,
					.url = workspaces[i]->pins[j]->url
				};
			}

			return state;
		}

		void start(){
			if(!workspaces.size()){
				Workspace* ws = new Workspace;
				workspaces.push_back(ws);
				ws->activeTab = -1;
			}
			while(window.isOpen()){
				const std::optional event = window.pollEvent();
				if(event) eventHandler(event);

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

	std::ifstream in("ws.bin", std::ios::binary);
	if(in.is_open()){
		State state;
		struct_pack::err_code err = struct_pack::deserialize_to(state, in);
		in.close();
		if(!err) browser.setState(state);
	}

	browser.start();

	State state = browser.getState();
	std::ofstream out("ws.bin", std::ios::binary);
	struct_pack::serialize_to(out, state);
	out.close();
}
