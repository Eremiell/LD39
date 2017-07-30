#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ld39 {
	class Character {
		public:
			Character(float offsetX, float offsetY);
			void move(float offsetX, float offsetY);
			void render(sf::RenderWindow &window);
		private:
			enum class State {
				Still,
				Moving,
				Jumping,
				Falling
			};
			enum class Orientation {
				Left,
				Right
			};
			State state;
			Orientation orientation;
			std::uint8_t moving_frame;
			sf::Sprite sprite;
			sf::Texture still;
			sf::Texture jumping;
			sf::Texture falling;
			std::array<sf::Texture, 4> moving;
			sf::Clock moving_clock;
	};
}

#endif