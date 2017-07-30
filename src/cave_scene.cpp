#include "inc/cave_scene.hpp"
#include "inc/utility.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::uint16_t level) : Scene(window), level(level), character(500, 250) {
		this->background_texture.loadFromFile("res/img/background.png");
		this->background.setTexture(this->background_texture);
		this->music.openFromFile("res/mus/ld1.ogg");
		this->music.setLoop(true);
		this->music.setVolume(20);
		this->music.play();
	}

	void CaveScene::integrate(std::uint8_t controls) {
		if (controls & static_cast<std::uint8_t>(Controls::Left) && !(controls & static_cast<std::uint8_t>(Controls::Right))) {
			this->character.move(-3.0f, 0.0f);
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Right) && !(controls & static_cast<std::uint8_t>(Controls::Left))) {
			this->character.move(3.0f, 0.0f);
		}
		if (controls & static_cast<std::uint8_t>(Controls::Up) && !(controls & static_cast<std::uint8_t>(Controls::Down))) {
			this->character.move(0.0f, -3.0f);
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Down) && !(controls & static_cast<std::uint8_t>(Controls::Up))) {
			this->character.move(0.0f, 3.0f);
		}
		if (!controls) {
			this->character.move(0.0f, 0.0f);
		}
		return;
	}

	void CaveScene::render() {
		this->window.draw(this->background);
		this->character.render(this->window);
		return;
	}
}