#include "inc/cave_scene.hpp"
#include <SFML/Graphics/Text.hpp>
#include "inc/utility.hpp"

namespace ld39 {
	CaveScene::CaveScene(sf::RenderWindow &window, std::uint64_t level = 0) : Scene(window), lit(true), level(level), character(500, 250) {
		this->background_textures[0].loadFromFile("res/img/firststage.png");
		this->background_textures[1].loadFromFile("res/img/nudebackround.png");
		this->background_textures[2].loadFromFile("res/img/bluebackground.png");
		this->background_textures[3].loadFromFile("res/img/redbackground.png");
		this->background_textures[4].loadFromFile("res/img/yellowbackground.png");
		this->background_textures[5].loadFromFile("res/img/night_background.png");
		this->background.setTexture(this->background_textures[1]);
		this->music.openFromFile("res/mus/ld12.ogg");
		this->music.setLoop(true);
		this->music.setVolume(20);
		this->music.play();
		this->wall_textures[0].loadFromFile("res/img/bottomentrence.png");
		this->wall_textures[1].loadFromFile("res/img/topentrence.png");
		this->wall_textures[2].loadFromFile("res/img/plateform1.png");
		this->wall_textures[3].loadFromFile("res/img/plateform2.png");
		this->wall_textures[4].loadFromFile("res/img/plateform3.png");
		this->wall_textures[5].loadFromFile("res/img/plateform4.png");
		this->wall_textures[6].loadFromFile("res/img/long_plateform.png");
		this->wall_textures[7].loadFromFile("res/img/long_plateform2.png");
		this->wall_textures[8].loadFromFile("res/img/fall_plateform.png");
		this->wall_textures[9].loadFromFile("res/img/fall_plateform2.png");
		this->wall_hitboxes[0].width = 115;
		this->wall_hitboxes[0].height = 450;
		this->wall_hitboxes[0].left = 0;
		this->wall_hitboxes[0].top = 10;
		this->wall_hitboxes[1].width = 111;
		this->wall_hitboxes[1].height = 427;
		this->wall_hitboxes[1].left = 0;
		this->wall_hitboxes[1].top = 10;
		this->wall_hitboxes[2].width = 61;
		this->wall_hitboxes[2].height = 98;
		this->wall_hitboxes[2].left = 6;
		this->wall_hitboxes[2].top = 10;
		this->wall_hitboxes[3].width = 61;
		this->wall_hitboxes[3].height = 150;
		this->wall_hitboxes[3].left = 9;
		this->wall_hitboxes[3].top = 10;
		this->wall_hitboxes[4].width = 61;
		this->wall_hitboxes[4].height = 110;
		this->wall_hitboxes[4].left = 6;
		this->wall_hitboxes[4].top = 10;
		this->wall_hitboxes[5].width = 61;
		this->wall_hitboxes[5].height = 69;
		this->wall_hitboxes[5].left = 9;
		this->wall_hitboxes[5].top = 10;
		this->wall_hitboxes[6].width = 289;
		this->wall_hitboxes[6].height = 52;
		this->wall_hitboxes[6].left = 0;
		this->wall_hitboxes[6].top = 10;
		this->wall_hitboxes[7].width = 289;
		this->wall_hitboxes[7].height = 54;
		this->wall_hitboxes[7].left = 0;
		this->wall_hitboxes[7].top = 10;
		this->wall_hitboxes[8].width = 84;
		this->wall_hitboxes[8].height = 408;
		this->wall_hitboxes[8].left = 84;
		this->wall_hitboxes[8].top = 10;
		this->wall_hitboxes[9].width = 97;
		this->wall_hitboxes[9].height = 411;
		this->wall_hitboxes[9].left = 36;
		this->wall_hitboxes[9].top = 10;
		this->walls.emplace_back(100.0f, 320.0f, this->wall_hitboxes[5], this->wall_textures[5]);
		this->walls.emplace_back(300.0f, 320.0f, this->wall_hitboxes[2], this->wall_textures[2]);
		this->walls.emplace_back(700.0f, 320.0f, this->wall_hitboxes[3], this->wall_textures[3]);
		this->walls.emplace_back(900.0f, 320.0f, this->wall_hitboxes[4], this->wall_textures[4]);
		this->walls.emplace_back(500.0f, 320.0f, this->wall_hitboxes[6], this->wall_textures[6]);
		this->font.loadFromFile("res/fon/bpdots.squares-bold.otf");
		this->flashlight_textures[0].loadFromFile("res/img/flash.png");
		this->flashlight_textures[1].loadFromFile("res/img/flash2.png");
		this->flashlight.setTexture(this->flashlight_textures[1]);
		this->flashlight.setScale(0.25f, 0.25f);
		this->flashlight.setOrigin(242.0f, 206.0f);
		this->flashlight.setPosition(990.0f, 490.0f);
	}
	void CaveScene::integrate(std::uint8_t controls) {
		if (controls & static_cast<std::uint8_t>(Controls::Space)) {
			this->light_switch();
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
		this->collision_resolution();
		if (this->character.get_hitbox().intersects(sf::Rect<float>(-10.0f, 500.0f, 1020.0f, 10.0f))) {
			this->character.fall();
		}
		this->character.set_mannequin(lit);
		return;
	}
	void CaveScene::render() {
		this->window.draw(this->background);
		for (auto wall : this->walls) {
			wall.render(this->window);
		}
		if (this->character.is_alive()) {
			this->character.render(this->window);
			this->window.draw(this->flashlight);
		}
		else {
			sf::Text text("GAME OVER", this->font);
			text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
			text.setPosition(500.0f, 250.0f);
			this->window.draw(text);
		}
		return;
	}
	void CaveScene::collision_resolution() {
		sf::Rect<float> intersection;
		for (auto wall : this->walls) {
			if (this->character.get_hitbox().intersects(wall.get_hitbox(), intersection)) {
				if (intersection.width < intersection.height) {
					if (intersection.left == this->character.get_hitbox().left) {
						this->character.move(intersection.width, 0.0f);
					}
					else {
						this->character.move(-intersection.width, 0.0f);
					}
				}
				else {
					if (intersection.top == this->character.get_hitbox().top) {
						this->character.move(0.0f, intersection.height);
					}
					else {
						this->character.move(0.0f, -intersection.height);
						this->character.glue();
					}
				}
			}
		}
		if (this->character.get_hitbox().intersects(sf::Rect<float>(-20.0f, -20.0f, 1040.0f, 20.0f), intersection)) {
			this->character.move(0.0f, intersection.height);
		}
		return;
	}
	void CaveScene::gravity() {
		this->character.move(0.0f, 5.0f);
		return;
	}
	void CaveScene::light_switch() {
		static sf::Clock light_clock;
		if (light_clock.getElapsedTime().asSeconds() > 0.25f && this->character.is_alive() && this->character.is_still()) {
			light_clock.restart();
			if (this->lit) {
				this->flashlight.setTexture(this->flashlight_textures[0]);
				this->background.setTexture(this->background_textures[5]);
			}
			else {
				this->flashlight.setTexture(this->flashlight_textures[1]);
				this->background.setTexture(this->background_textures[1]);
			}
			this->lit = !this->lit;
		}
		return;
	}
}