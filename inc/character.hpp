#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <array>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Vector2.hpp>

namespace ld39 {
	class Character {
		public:
			Character(float offset_x = 500, float offset_y = 250);
			void move(float offset_x, float offset_y);
			void new_spawn(sf::Vector2<float> spawn);
			void jump();
			void rise();
			void glue();
			void fall();
			void gain_life();
			bool is_alive();
			bool is_still();
			void set_mannequin(bool lit);
			void render(sf::RenderWindow &window);
			float get_x() const;
			float get_y() const;
			float get_w() const;
			float get_h() const;
			sf::Rect<float> get_hitbox() const;
			void make_omelette();
		private:
			std::uint8_t lives;
			std::uint8_t max_lives;
			bool airborne;
			bool jumped;
			bool stands;
			float rising;
			sf::Vector2<float> last_position;
			sf::Vector2<float> spawn_point;
			std::uint8_t moving_frame;
			bool omelette;
			sf::Sprite sprite;
			std::array<sf::Texture, 3> still;
			std::array<sf::Texture, 3> jumping;
			std::array<sf::Texture, 3> falling;
			std::array<sf::Texture, 12> moving;
			std::array<sf::Texture, 2> hearts;
			std::array<sf::SoundBuffer, 5> sfx_buffers;
			std::array<sf::Sound, 5> sfx;
			sf::Sprite heart;
	};
}

#endif