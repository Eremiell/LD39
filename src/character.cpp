#include "inc/character.hpp"

namespace ld39 {
	Character::Character(float offset_x = 500, float offset_y = 250) : airborne(false), walking(false), right(false), last_position(offset_x, offset_y), moving_frame(0) {
		this->still[0].loadFromFile("res/img/hero.png");
		this->still[1].loadFromFile("res/img/night_hero.png");
		this->jumping[0].loadFromFile("res/img/jump1.png");
		this->falling[0].loadFromFile("res/img/jump2.png");
		this->moving[0].loadFromFile("res/img/run1.png");
		this->moving[1].loadFromFile("res/img/run2.png");
		this->moving[2].loadFromFile("res/img/run3.png");
		this->moving[3].loadFromFile("res/img/run4.png");
		this->sprite.setTexture(this->still[0]);
		this->sprite.setOrigin(14, 44);
		this->sprite.setPosition(offset_x, offset_y);
	}
	void Character::move(float offset_x, float offset_y) {
		this->sprite.move(offset_x, offset_y);
		return;
	}
	void Character::set_mannequin() {
		if ((this->sprite.getPosition().x - this->last_position.x) > 0.0001f) {
			this->sprite.setScale(1.0f, 1.0f);
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				this->sprite.setTexture(this->falling[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				this->sprite.setTexture(this->jumping[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else {
				this->sprite.setTexture(this->moving[this->moving_frame], true);
				this->sprite.setOrigin(30, 42);
				if (this->moving_clock.getElapsedTime().asSeconds() > 0.1) {
					this->moving_clock.restart();
					if (++this->moving_frame >= 4) {
						this->moving_frame = 0;
					}
				}
			}
		}
		else if ((this->sprite.getPosition().x - this->last_position.x) < -0.0001f) {
			this->sprite.setScale(-1.0f, 1.0f);
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				this->sprite.setTexture(this->falling[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				this->sprite.setTexture(this->jumping[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else {
				this->sprite.setTexture(this->moving[this->moving_frame], true);
				this->sprite.setOrigin(30, 42);
				if (this->moving_clock.getElapsedTime().asSeconds() > 0.1) {
					this->moving_clock.restart();
					if (++this->moving_frame >= 4) {
						this->moving_frame = 0;
					}
				}
			}
		}
		else {
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				this->sprite.setTexture(this->falling[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				this->sprite.setTexture(this->jumping[0], true);
				this->sprite.setOrigin(29, 48);
			}
			else {
				this->sprite.setTexture(this->still[0], true);
				this->sprite.setOrigin(14, 44);
			}
		}
		this->last_position.x = this->sprite.getPosition().x;
		this->last_position.y = this->sprite.getPosition().y;
		return;
	}
	void Character::render(sf::RenderWindow &window) const {
		window.draw(this->sprite);
		return;
	}
	float Character::get_x() const {
		return this->sprite.getPosition().x - 14.0f;
	}
	float Character::get_y() const {
		return this->sprite.getPosition().y - 44.0f;
	}
	float Character::get_w() const {
		return 28.0f;
	}
	float Character::get_h() const {
		return 87.0f;
	}
	sf::Rect<float> Character::get_hitbox() const {
		return sf::Rect<float>(this->get_x(), this->get_y(), this->get_w(), this->get_h());
	}
}