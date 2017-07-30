#include "inc/cave_scene.hpp"
#include "inc/utility.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::uint16_t level) : Scene(window), level(level) {
		this->background_texture.loadFromFile("res/img/background.png");
		this->background.setTexture(this->background_texture);
		this->character_texture.loadFromFile("res/img/hero.png");
		this->character.setTexture(this->character_texture);
		this->character.setOrigin(14, 44);
		this->character.setPosition(500, 250);
	}

	void CaveScene::integrate(std::uint8_t controls) {
		if (controls & static_cast<std::uint8_t>(Controls::Up) && !(controls & static_cast<std::uint8_t>(Controls::Down))) {
			this->character.move(0.0f, -3.0f);
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Down) && !(controls & static_cast<std::uint8_t>(Controls::Up))) {
			this->character.move(0.0f, 3.0f);
		}
		if (controls & static_cast<std::uint8_t>(Controls::Left) && !(controls & static_cast<std::uint8_t>(Controls::Right))) {
			this->character.setScale(-1.0f, 1.0f);
			this->character.move(-2.0f, 0.0f);
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Right) && !(controls & static_cast<std::uint8_t>(Controls::Left))) {
			this->character.setScale(1.0f, 1.0f);
			this->character.move(2.0f, 0.0f);
		}
		return;
	}

	void CaveScene::render() {
		this->window.draw(this->background);
		this->window.draw(this->character);
		return;
	}
}