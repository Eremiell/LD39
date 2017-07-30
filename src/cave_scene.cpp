#include "inc/cave_scene.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::int16_t level) : Scene(window), level(level) {
		this->background_texture.loadFromFile("res/img/background.png");
		this->background.setTexture(this->background_texture);
	}
	
	void CaveScene::integrate() {
		return;
	}

	void CaveScene::render() {
		this->window.draw(this->background);
		return;
	}
}