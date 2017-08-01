#ifndef CAVE_SCENE_HPP
#define CAVE_SCENE_HPP

#include "inc/scene.hpp"
#include <array>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include "inc/character.hpp"
#include "inc/level.hpp"

namespace ld39 {
	class CaveScene : public Scene {
		public:
			CaveScene(sf::RenderWindow &window, std::array<sf::Texture, 8> &background_textures);
			virtual void init() override;
			virtual void integrate(std::uint8_t controls) override;
			virtual void render() override;
			virtual void make_omelette() override;
		private:
			void gravity();
			bool lit;
			Character character;
			std::array<sf::Texture, 8> &background_textures;
			Level level;
			sf::Music music;
			sf::Font font;
			std::array<sf::Texture, 2> flashlight_textures;
			sf::Sprite flashlight;
	};
}

#endif