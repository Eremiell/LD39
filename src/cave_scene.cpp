#include "inc/cave_scene.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::int16_t level) : Scene(window), level(level) {
		this->background_texture.loadFromFile("res/img/background.png");
		this->background.setTexture(this->background_texture);
		this->character_texture.loadFromFile("res/img/hero.png");
		this->character.setTexture(this->character_texture);
		this->character.setOrigin(14, 44);
		this->character.setPosition(500, 250);
	}

	void CaveScene::integrate() {
		return;
	}

	void CaveScene::render() {
		this->window.draw(this->background);
		this->window.draw(this->character);
		return;
	}
}