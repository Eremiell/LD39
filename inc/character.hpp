#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <array>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace ld39 {
	class Character {
		public:
			Character(float offset_x, float offset_y);
			void move(float offset_x, float offset_y);
			void set_mannequin();
			void render(sf::RenderWindow &window) const;
			float get_x() const;
			float get_y() const;
			float get_w() const;
			float get_h() const;
			sf::Rect<float> get_hitbox() const;
		private:
			bool airborne;
			bool walking;
			bool right;
			sf::Vector2<float> last_position;
			std::uint8_t moving_frame;
			sf::Sprite sprite;
			std::array<sf::Texture, 2> still;
			std::array<sf::Texture, 2> jumping;
			std::array<sf::Texture, 2> falling;
			std::array<sf::Texture, 8> moving;
			sf::Clock moving_clock;
	};
}

#endif