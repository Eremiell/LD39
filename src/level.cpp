#include "inc/level.hpp"
#include <random>
#include <chrono>
#include <sstream>
#include <SFML/Graphics/Text.hpp>

namespace ld39 {
	Level::Level(Character &character, std::array<sf::Texture, 8> &background_textures, sf::Font &font, std::int64_t layer) : layer(layer), character(character), lit(true), entry_level(500.0f - 42.0f), background_textures(background_textures), font(font) {}
	void Level::init() {
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
		this->sfx_buffer.loadFromFile("res/sfx/level.wav");
		this->sfx.setBuffer(this->sfx_buffer);
		this->heart_texture.loadFromFile("res/img/heart.png");
		this->build();
		return;
	}
	void Level::render(sf::RenderWindow &window) {
		window.draw(this->background);
		for (auto wall : this->walls) {
			wall.render(window);
		}
		for (auto hea : this->hearts) {
			hea.render(window);
		}
		std::stringstream ss;
		ss << "Layer " << this->layer;
		sf::Text text(ss.str(), this->font);
		text.setOrigin(text.getGlobalBounds().width, 0.0f);
		text.setPosition(990.0f, 10.0f);
		window.draw(text);
		return;
	}
	void Level::collision_resolution() {
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
		for (auto it = this->hearts.begin(); it != this->hearts.end(); ++it) {
			if (this->character.get_hitbox().intersects((*it).get_hitbox())) {
				this->character.gain_life();
				this->hearts.erase(it);
				break;
			}
		}
		if (this->character.get_hitbox().intersects(sf::Rect<float>(-20.0f, -20.0f, 1040.0f, 20.0f), intersection)) {
			this->character.move(0.0f, intersection.height);
		}
		if (this->l2r) {
			if (this->character.get_hitbox().intersects(sf::Rect<float>(-20.0f, -20.0f, 20.0f, 540.0f), intersection)) {
				this->character.move(intersection.width, 0.0f);
			}
			else if (this->character.get_hitbox().intersects(sf::Rect<float>(1000.0f, -20.0f, 20.0f, 5400.0f), intersection)) {
				this->rebuild();
			}
		}
		else {
			if (this->character.get_hitbox().intersects(sf::Rect<float>(1000.0f, -20.0f, 20.0f, 5400.0f), intersection)) {
				this->character.move(-intersection.width, 0.0f);
			}
			else if (this->character.get_hitbox().intersects(sf::Rect<float>(-20.0f, -20.0f, 20.0f, 540.0f), intersection)) {
				this->rebuild();
			}
		}
		return;
	}
	bool Level::light_switch() {
		static sf::Clock light_clock;
		if (light_clock.getElapsedTime().asSeconds() > 0.25f && this->character.is_alive() && this->character.is_still()) {
			light_clock.restart();
			if (this->lit) {
				this->background.setTexture(this->background_textures[7]);
			}
			else {
				this->background.setTexture(this->background_textures[colour]);
			}
			this->lit = !this->lit;
		}
		return this->lit;
	}
	void Level::rebuild() {
		this->walls.clear();
		this->hearts.clear();
		this->build();
		++this->layer;
		this->sfx.play();
		return;
	}
	void Level::build() {
		std::mt19937_64 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<std::uint8_t> dist2(0, 1);
		std::uniform_int_distribution<std::uint8_t> dist3(0, 2);
		std::uniform_int_distribution<std::uint8_t> dist4(0, 3);
		std::uniform_int_distribution<std::uint8_t> dist5(0, 4);
		std::uniform_int_distribution<std::uint8_t> dist6(0, 5);
		std::uniform_int_distribution<std::uint8_t> dist15(0, 19);
		std::uniform_real_distribution<float> dist_f(0.0f, 1.0f);
		this->l2r = static_cast<bool>(dist2(mt));
		if (l2r) {
			this->walls.emplace_back(0.0f, this->entry_level + 10.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->walls.emplace_back(0.0f, this->entry_level - 140.0f - 450.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->spawn.x = 20.0f;
			this->spawn.y = this->entry_level - 43.0f;
		}
		else {
			this->walls.emplace_back(1000.0f, this->entry_level + 10.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->walls.emplace_back(1000.0f, this->entry_level - 140.0f - 450.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->spawn.x = 1000.0f - 20.0f;
			this->spawn.y = this->entry_level - 43.0f;
		}
		this->colour = dist5(mt) + 1;
		std::uint8_t num_platforms = dist3(mt) + 4;
		float plat_space = 850.0f / num_platforms;
		for (std::uint8_t i = 0; i < num_platforms; ++i) {
			std::uint8_t type = dist4(mt) + 2;
			bool mirrored = static_cast<bool>(dist2(mt));
			this->entry_level = 480.0f - (480.0f - (this->entry_level - 20.0f)) * dist_f(mt);
			this->walls.emplace_back(plat_space * dist_f(mt) / 3 + (i + 0.33f) * plat_space + 75.0f, this->entry_level, wall_hitboxes[type], wall_textures[type], mirrored);
			bool heart = !dist15(mt);
			if (heart) {
				this->hearts.emplace_back(sf::Vector2<float>(plat_space * (i + 0.5f) + 75.0f, this->entry_level - 90.0f), this->heart_texture);
			}
		}
		this->entry_level = 480.0f - (480.0f - (this->entry_level - 20.0f)) * dist_f(mt);
		if (!l2r) {
			this->walls.emplace_back(0.0f, this->entry_level + 10.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->walls.emplace_back(0.0f, this->entry_level - 140.0f - 450.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
		}
		else {
			this->walls.emplace_back(1000.0f, this->entry_level + 10.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
			this->walls.emplace_back(1000.0f, this->entry_level - 140.0f - 450.0f + 225.0f, wall_hitboxes[0], wall_textures[0]);
		}
		if (this->lit) {
			this->background.setTexture(this->background_textures[colour]);
		}
		else {
			this->background.setTexture(this->background_textures[7]);
		}
		this->character.new_spawn(this->spawn);
		return;
	}
}