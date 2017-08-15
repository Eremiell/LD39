#include "inc/character.hpp"

namespace ld39 {
	Character::Character(float offset_x, float offset_y) : lives(5), max_lives(5), airborne(false), jumped(false), stands(true), rising(0.0f), last_position(offset_x, offset_y), spawn_point(offset_x, offset_y), moving_frame(0), omelette(false) {
		this->still[0].loadFromFile("res/img/hero.png");
		this->still[1].loadFromFile("res/img/night_hero.png");
		this->still[2].loadFromFile("res/img/eehero.png");
		this->jumping[0].loadFromFile("res/img/jump1.png");
		this->jumping[1].loadFromFile("res/img/night_jump1.png");
		this->jumping[2].loadFromFile("res/img/eejump1.png");
		this->falling[0].loadFromFile("res/img/jump2.png");
		this->falling[1].loadFromFile("res/img/night_jump2.png");
		this->falling[2].loadFromFile("res/img/eejump2.png");
		this->moving[0].loadFromFile("res/img/run1.png");
		this->moving[1].loadFromFile("res/img/run2.png");
		this->moving[2].loadFromFile("res/img/run3.png");
		this->moving[3].loadFromFile("res/img/run4.png");
		this->moving[4].loadFromFile("res/img/night_run1.png");
		this->moving[5].loadFromFile("res/img/night_run2.png");
		this->moving[6].loadFromFile("res/img/night_run3.png");
		this->moving[7].loadFromFile("res/img/night_run4.png");
		this->moving[8].loadFromFile("res/img/eerun1.png");
		this->moving[9].loadFromFile("res/img/eerun2.png");
		this->moving[10].loadFromFile("res/img/eerun3.png");
		this->moving[11].loadFromFile("res/img/eerun4.png");
		this->sprite.setTexture(this->still[0]);
		this->sprite.setOrigin(14, 44);
		this->sprite.setPosition(offset_x, offset_y);
		this->hearts[0].loadFromFile("res/img/heart.png");
		this->hearts[1].loadFromFile("res/img/heartblack.png");
		this->sfx_buffers[0].loadFromFile("res/sfx/walk.wav");
		this->sfx_buffers[1].loadFromFile("res/sfx/jump.wav");
		this->sfx_buffers[2].loadFromFile("res/sfx/Land.wav");
		this->sfx_buffers[3].loadFromFile("res/sfx/Fall.wav");
		this->sfx_buffers[4].loadFromFile("res/sfx/life.wav");
		this->sfx[0].setBuffer(this->sfx_buffers[0]);
		this->sfx[1].setBuffer(this->sfx_buffers[1]);
		this->sfx[2].setBuffer(this->sfx_buffers[2]);
		this->sfx[3].setBuffer(this->sfx_buffers[3]);
		this->sfx[4].setBuffer(this->sfx_buffers[4]);
		for (auto &sound : this->sfx) {
			sound.setVolume(30.0f);
		}
	}
	void Character::move(float offset_x, float offset_y) {
		this->sprite.move(offset_x, offset_y);
		return;
	}
	void Character::new_spawn(sf::Vector2<float> spawn) {
		this->spawn_point = spawn;
		this->last_position = spawn;
		this->sprite.setPosition(spawn);
		return;
	}
	void Character::jump() {
		if (this->lives > 0 && !this->jumped) {
			this->rising = 10.0f;
			this->sfx[1].play();
			if (this->airborne) {
				this->jumped = true;
			}
		}
		return;
	}
	void Character::rise() {
		this->move(0.0f, -this->rising);
		this->rising -= 0.25f;
		return;
	}
	void Character::glue() {
		if (this->airborne) {
			this->sfx[2].play();
		}
		this->airborne = false;
		this->jumped = false;
		this->rising = 0.0f;
		this->stands = true;
		return;
	}
	void Character::fall() {
		this->sfx[3].play();
		this->sprite.setPosition(this->spawn_point);
		this->last_position = this->spawn_point;
		this->glue();
		if (this->lives > 0) {
			--this->lives;
		}
		return;
	}
	void Character::gain_life() {
		this->sfx[4].play();
		if (this->lives < this->max_lives) {
			++this->lives;
		}
	}
	bool Character::is_alive() {
		return static_cast<bool>(this->lives);
	}
	bool Character::is_still() {
		return this->stands && this->rising < 0.0001f;
	}
	void Character::set_mannequin(bool lit) {
		static sf::Clock moving_clock;
		this->stands = false;
		if ((this->sprite.getPosition().x - this->last_position.x) > 0.0001f) {
			this->sprite.setScale(1.0f, 1.0f);
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->falling[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->falling[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->falling[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->jumping[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->jumping[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->jumping[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else {
				if (lit) {
					this->sprite.setTexture(this->moving[this->moving_frame], true);
					if (this->omelette) {
						this->sprite.setTexture(this->moving[this->moving_frame + 8], true);
					}
				}
				else {
					this->sprite.setTexture(this->moving[this->moving_frame + 4], true);
				}
				this->sprite.setOrigin(30, 42);
				if (moving_clock.getElapsedTime().asSeconds() > 0.1) {
					moving_clock.restart();
					if (++this->moving_frame >= 4) {
						this->moving_frame = 0;
					}
				}
				if (!this->moving_frame) {
					this->sfx[0].play();
				}
			}
		}
		else if ((this->sprite.getPosition().x - this->last_position.x) < -0.0001f) {
			this->sprite.setScale(-1.0f, 1.0f);
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->falling[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->falling[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->falling[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->jumping[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->jumping[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->jumping[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else {
				if (lit) {
					this->sprite.setTexture(this->moving[this->moving_frame], true);
					if (this->omelette) {
						this->sprite.setTexture(this->moving[this->moving_frame + 8], true);
					}
				}
				else {
					this->sprite.setTexture(this->moving[this->moving_frame + 4], true);
				}
				this->sprite.setOrigin(30, 42);
				if (moving_clock.getElapsedTime().asSeconds() > 0.1) {
					moving_clock.restart();
					if (++this->moving_frame >= 4) {
						this->moving_frame = 0;
					}
				}
				if (!this->moving_frame) {
					this->sfx[0].play();
				}
			}
		}
		else {
			if ((this->sprite.getPosition().y - this->last_position.y) > 0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->falling[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->falling[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->falling[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else if ((this->sprite.getPosition().y - this->last_position.y) < -0.0001f) {
				if (lit) {
					this->sprite.setTexture(this->jumping[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->jumping[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->jumping[1], true);
				}
				this->sprite.setOrigin(29, 48);
				this->airborne = true;
			}
			else {
				if (lit) {
					this->sprite.setTexture(this->still[0], true);
					if (this->omelette) {
						this->sprite.setTexture(this->still[2], true);
					}
				}
				else {
					this->sprite.setTexture(this->still[1], true);
				}
				this->sprite.setOrigin(14, 44);
				this->stands = true;
			}
		}
		this->last_position.x = this->sprite.getPosition().x;
		this->last_position.y = this->sprite.getPosition().y;
		return;
	}
	void Character::render(sf::RenderWindow &window) {
		window.draw(this->sprite);
		for (std::uint8_t i = 0; i < this->max_lives; ++i) {
			if (this->lives > i) {
				this->heart.setTexture(this->hearts[0], true);
			}
			else {
				this->heart.setTexture(this->hearts[1], true);
			}
			this->heart.setPosition(10.0f + i * 60.0f, 10.0f);
			window.draw(this->heart);
		}
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
	void Character::make_omelette() {
		this->omelette = true;
		return;
	}
}