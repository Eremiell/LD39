#include "inc/cave_scene.hpp"
#include <SFML/Graphics/Text.hpp>
#include "inc/utility.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::array<sf::Texture, 8> &background_textures) : Scene(window), lit(true), character(500, 250), background_textures(background_textures), level(this->character, this->background_textures, this->font) {
		this->music.openFromFile("res/mus/themesong.wav");
		this->music.setLoop(true);
		this->music.setVolume(20);
		this->music.play();
		this->font.loadFromFile("res/fon/bpdots.squares-bold.otf");
		this->flashlight_textures[0].loadFromFile("res/img/flash.png");
		this->flashlight_textures[1].loadFromFile("res/img/flash2.png");
		this->flashlight.setTexture(this->flashlight_textures[1]);
		this->flashlight.setScale(0.25f, 0.25f);
		this->flashlight.setOrigin(242.0f, 206.0f);
		this->flashlight.setPosition(990.0f, 490.0f);
	}
	void CaveScene::init() {
		this->level.init();
		return;
	}
	void CaveScene::integrate(std::uint8_t controls) {
		if (controls & static_cast<std::uint8_t>(Controls::Space)) {
			this->lit = this->level.light_switch();
		}
		float x = 0.0f, y = 0.0f;
		if (controls & static_cast<std::uint8_t>(Controls::Left) && !(controls & static_cast<std::uint8_t>(Controls::Right))) {
			x -= 3.0f;
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Right) && !(controls & static_cast<std::uint8_t>(Controls::Left))) {
			x += 3.0f;
		}
		if (controls & static_cast<std::uint8_t>(Controls::Up) && !(controls & static_cast<std::uint8_t>(Controls::Down))) {
			this->character.jump();
		}
		else if (controls & static_cast<std::uint8_t>(Controls::Down) && !(controls & static_cast<std::uint8_t>(Controls::Up))) {
			y += 5.0f;
		}
		this->character.move(x, y);
		this->character.rise();
		this->gravity();
		this->level.collision_resolution();
		if (this->character.get_hitbox().intersects(sf::Rect<float>(-10.0f, 500.0f, 1020.0f, 10.0f))) {
			this->character.fall();
		}
		this->character.set_mannequin(lit);
		return;
	}
	void CaveScene::render() {
		this->level.render(this->window);
		if (this->lit) {
			this->flashlight.setTexture(this->flashlight_textures[1]);
		}
		else {
			this->flashlight.setTexture(this->flashlight_textures[0]);
		}
		if (this->character.is_alive()) {
			this->character.render(this->window);
			this->window.draw(this->flashlight);
		}
		else {
			this->character.new_spawn(sf::Vector2<float>(1200.0f, 600.0f));
			sf::Text text("GAME OVER", this->font);
			text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
			text.setPosition(500.0f, 250.0f);
			this->window.draw(text);
		}
		return;
	}
	void CaveScene::gravity() {
		this->character.move(0.0f, 5.0f);
		return;
	}
}