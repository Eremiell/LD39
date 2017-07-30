#include "inc/game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include "inc/cave_scene.hpp"
#include "inc/utility.hpp"

namespace ld39 {
	Game::Game() : window(sf::VideoMode(1000, 500), "LD39", sf::Style::Titlebar | sf::Style::Close), scene(new CaveScene(this->window, 0)) {}

	void Game::run() {
		double t = 0.0;
		const double dt = 1.0 / 60;
		double accumulator = 0.0;
		sf::Clock timer;
		std::uint8_t controls = 0u;
		while (this->window.isOpen()) {
			controls &= 0u;
			accumulator += timer.getElapsedTime().asSeconds();
			timer.restart();
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					this->window.close();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				this->window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				controls |= static_cast<std::uint8_t>(Controls::Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				controls |= static_cast<std::uint8_t>(Controls::Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				controls |= static_cast<std::uint8_t>(Controls::Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				controls |= static_cast<std::uint8_t>(Controls::Right);
			}
			while (accumulator >= dt) {
				this->scene->integrate(controls);
				accumulator -= dt;
				t += dt;
			}
			this->window.clear(sf::Color::Magenta);
			this->scene->render();
			this->window.display();
		}
		return;
	}
}