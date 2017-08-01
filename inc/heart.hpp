#ifndef HEART_HPP
#define HEART_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace ld39 {
	class Heart {
		public:
			Heart(sf::Vector2<float> position, sf::Texture &texture);
			void render(sf::RenderWindow &window) const;
			float get_x() const;
			float get_y() const;
			float get_w() const;
			float get_h() const;
			sf::Rect<float> get_hitbox() const;
		private:
			sf::Vector2<float> position;
			sf::Sprite sprite;
	};
}

#endif