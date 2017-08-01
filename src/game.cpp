#include "inc/game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include "inc/cave_scene.hpp"
#include "inc/utility.hpp"

namespace ld39 {
	Game::Game() : window(sf::VideoMode(1000, 500), "LD39", sf::Style::Titlebar | sf::Style::Close), scene(new CaveScene(this->window, this->background_textures)) {
		this->background_textures[0].loadFromFile("res/img/firststage.png");
		this->background_textures[1].loadFromFile("res/img/nudebackround.png");
		this->background_textures[2].loadFromFile("res/img/bluebackground.png");
		this->background_textures[3].loadFromFile("res/img/redbackground.png");
		this->background_textures[4].loadFromFile("res/img/yellowbackground.png");
		this->background_textures[5].loadFromFile("res/img/greenbackround.png");
		this->background_textures[6].loadFromFile("res/img/night_firststage.png");
		this->background_textures[7].loadFromFile("res/img/night_background-1.png");
		this->scene->init();
	}

	void Game::run() {
		bool running = true;
		double t = 0.0;
		const double dt = 1.0 / 60;
		double accumulator = 0.0;
		sf::Clock timer;
		std::uint8_t controls = 0u;
		std::uint8_t eggs = 0u;
		while (running) {
			accumulator += timer.getElapsedTime().asSeconds();
			timer.restart();
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					running = false;
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Space) {
						controls |= static_cast<std::uint8_t>(Controls::Space);
						eggs = 0;
					}
					else if (event.key.code == sf::Keyboard::Up) {
						if (!eggs || eggs == 1) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::Down) {
						if (eggs == 2 || eggs == 3) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::Left) {
						if (eggs == 4 || eggs == 6) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::Right) {
						if (eggs == 5 || eggs == 7) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::A) {
						if (eggs == 9) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::B) {
						if (eggs == 8) {
							++eggs;
						}
						else {
							eggs = 0;
						}
					}
					else if (event.key.code == sf::Keyboard::Return) {
						if (eggs == 10) {
							this->scene->make_omelette();
						}
						else {
							eggs = 0;
						}
					}
					else {
						eggs = 0;
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				running = false;
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
				controls &= 0u;
				accumulator -= dt;
				t += dt;
			}
			this->window.clear(sf::Color::Magenta);
			this->scene->render();
			this->window.display();
			if (!running) {
				this->window.close();
			}
		}
		return;
	}
}