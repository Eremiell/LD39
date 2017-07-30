#include "inc/character.hpp"

namespace ld39 {
	Character::Character(float offsetX = 500, float offsetY = 250) : state(State::Still), orientation(Orientation::Left), moving_frame(0) {
		this->still.loadFromFile("res/img/hero.png");
		this->jumping.loadFromFile("res/img/jump1.png");
		this->falling.loadFromFile("res/img/jump2.png");
		this->moving[0].loadFromFile("res/img/run1.png");
		this->moving[1].loadFromFile("res/img/run2.png");
		this->moving[2].loadFromFile("res/img/run3.png");
		this->moving[3].loadFromFile("res/img/run4.png");
		this->sprite.setTexture(this->still);
		this->sprite.setOrigin(14, 44);
		this->sprite.setPosition(offsetX, offsetY);
	}
	void Character::move(float offsetX, float offsetY) {
		this->sprite.move(offsetX, offsetY);
		if (offsetY > 0.0001f) {
			this->sprite.setTexture(this->falling, true);
			this->sprite.setOrigin(29, 46);
		}
		else if (offsetY < -0.0001f) {
			this->sprite.setTexture(this->jumping, true);
			this->sprite.setOrigin(29, 46);
		}
		if (offsetX > 0.0001f) {
			this->sprite.setTexture(this->moving[this->moving_frame], true);
			this->sprite.setOrigin(30, 43);
			if (this->moving_clock.getElapsedTime().asSeconds() > 0.1) {
				this->moving_clock.restart();
				if (++this->moving_frame >= 4) {
					this->moving_frame = 0;
				}
			}
			this->sprite.setOrigin(14, 44);
			this->sprite.setScale(1.0f, 1.0f);
		}
		else if (offsetX < -0.0001f) {
			this->sprite.setTexture(this->moving[this->moving_frame], true);
			this->sprite.setOrigin(30, 43);
			if (this->moving_clock.getElapsedTime().asSeconds() > 0.1) {
				this->moving_clock.restart();
				if (++this->moving_frame >= 4) {
					this->moving_frame = 0;
				}
			}
			this->sprite.setScale(-1.0f, 1.0f);
		}
		else {
			this->moving_frame = 0;
		}
		if (offsetY < 0.0001f && offsetY > -0.0001f && offsetX < 0.0001f && offsetX > -0.0001f) {
			this->sprite.setTexture(this->still, true);
			this->sprite.setOrigin(14, 44);
		}
		return;
	}
	void Character::render(sf::RenderWindow &window) {
		window.draw(this->sprite);
		return;
	}
}