#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace ld39 {
	class Wall {
		public:
			Wall(float offset_x, float offset_y, float x, float y, float w, float h, sf::Texture &texture, bool mirrored = false);
			Wall(float offset_x, float offset_y, sf::Rect<float> &hitbox, sf::Texture &texture, bool mirrored = false);
			void render(sf::RenderWindow &window) const;
			float get_x() const;
			float get_y() const;
			float get_w() const;
			float get_h() const;
			sf::Rect<float> get_hitbox() const;
		private:
			sf::Rect<float> hitbox;
			sf::Sprite sprite;
	};
}

#endif