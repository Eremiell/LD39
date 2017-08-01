#include "inc/heart.hpp"

namespace ld39 {
	Heart::Heart(sf::Vector2<float> position, sf::Texture &texture) : position(position), sprite(texture) {
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.0f, this->sprite.getGlobalBounds().height / 2.0f);
		this->sprite.setScale(0.5f, 0.5f);
		this->sprite.setPosition(this->position);
	}
	void Heart::render(sf::RenderWindow &window) const {
		window.draw(this->sprite);
		return;
	}
	float Heart::get_x() const {
		return this->sprite.getGlobalBounds().left;
	}
	float Heart::get_y() const {
		return this->sprite.getGlobalBounds().top;
	}
	float Heart::get_w() const {
		return this->sprite.getGlobalBounds().width;
	}
	float Heart::get_h() const {
		return this->sprite.getGlobalBounds().height;
	}
	sf::Rect<float> Heart::get_hitbox() const {
		return this->sprite.getGlobalBounds();
	}
}