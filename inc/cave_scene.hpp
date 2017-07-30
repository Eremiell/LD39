#ifndef CAVE_SCENE_HPP
#define CAVE_SCENE_HPP

#include "inc/scene.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ld39 {
	class CaveScene : public Scene {
		public:
			CaveScene(sf::RenderWindow &window, std::uint16_t level);
			virtual void integrate(std::uint8_t controls) override;
			virtual void render() override;
		private:
			std::uint16_t level;
			sf::Sprite background;
			sf::Texture background_texture;
			sf::Sprite character;
			sf::Texture character_texture;
	};
}

#endif