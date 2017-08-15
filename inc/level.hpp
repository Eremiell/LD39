#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/wall.hpp"
#include "inc/heart.hpp"
#include "inc/character.hpp"

namespace ld39 {
	class Level {
		public:
			Level(Character &character, std::array<sf::Texture, 9> &background_textures, sf::Font &font, std::int64_t layer = 0);
			void init();
			void render(sf::RenderWindow &window);
			void collision_resolution();
			bool light_switch();
			void rebuild();
			std::uint64_t get_layer();
		private:
			void build();
			std::uint64_t layer;
			Character &character;
			bool lit;
			float entry_level;
			std::array<sf::Texture, 9> &background_textures;
			sf::Font &font;
			sf::Sprite background;
			bool l2r;
			std::array<sf::Texture, 11> wall_textures;
			std::array<sf::Rect<float>, 14> wall_hitboxes;
			std::vector<Wall> walls;
			std::uint8_t colour;
			std::vector<Heart> hearts;
			sf::Vector2<float> spawn;
			sf::SoundBuffer sfx_buffer;
			sf::Sound sfx;
			sf::Texture heart_texture;
	};
}

#endif