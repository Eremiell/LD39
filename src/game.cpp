#include "inc/game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include "inc/cave_scene.hpp"

namespace ld39 {
	Game::Game() : window(sf::VideoMode(1000, 500), "LD39", sf::Style::Titlebar | sf::Style::Close), scene(new CaveScene(this->window, 0)) {}

	void Game::run() {
		double t = 0.0;
		const double dt = 1.0 / 60;
		double accumulator = 0.0;
		sf::Clock timer;
		while (window.isOpen()) {
			accumulator += timer.getElapsedTime().asSeconds();
			timer.restart();
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			while (accumulator >= dt) {
				this->scene->integrate();
				accumulator -= dt;
				t += dt;
			}
			window.clear(sf::Color::Magenta);
			this->scene->render();
			window.display();
		}
		return;
	}
}