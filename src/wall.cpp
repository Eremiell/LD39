#include "inc/wall.hpp"

namespace ld39 {
	Wall::Wall(float offset_x, float offset_y, float x, float y, float w, float h, sf::Texture &texture, bool mirrored) : hitbox(x, y, w, h), sprite(texture) {
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.0f, this->sprite.getGlobalBounds().height / 2.0f);
		this->sprite.setPosition(offset_x, offset_y);
		if (mirrored) {
			this->sprite.setScale(-1.0f, 1.0f);
			this->hitbox.left = this->sprite.getGlobalBounds().width - this->hitbox.left - this->hitbox.width;
		}
	}
	Wall::Wall(float offset_x, float offset_y, sf::Rect<float> &hitbox, sf::Texture &texture, bool mirrored) : hitbox(hitbox), sprite(texture) {
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.0f, this->sprite.getGlobalBounds().height / 2.0f);
		this->sprite.setPosition(offset_x, offset_y);
		if (mirrored) {
			this->sprite.setScale(-1.0f, 1.0f);
			this->hitbox.left = this->sprite.getGlobalBounds().width - this->hitbox.left - this->hitbox.width;
		}
	}
	void Wall::render(sf::RenderWindow &window) const {
		window.draw(this->sprite);
		return;
	}
	float Wall::get_x() const {
		return this->hitbox.left + this->sprite.getPosition().x - this->sprite.getOrigin().x;
	}
	float Wall::get_y() const {
		return this->hitbox.top + this->sprite.getPosition().y - this->sprite.getOrigin().y;
	}
	float Wall::get_w() const {
		return this->hitbox.width;
	}
	float Wall::get_h() const {
		return this->hitbox.height;
	}
	sf::Rect<float> Wall::get_hitbox() const {
		return sf::Rect<float>(this->get_x(), this->get_y(), this->get_w(), this->get_h());
	}
}