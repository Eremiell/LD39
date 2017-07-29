#include "inc/game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

namespace ld39 {

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
				// integrate
				accumulator -= dt;
				t += dt;
			}
			// render
			window.clear(sf::Color::Magenta);
			window.display();
		}
		return;
	}

}