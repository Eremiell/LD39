#ifndef CAVE_SCENE_HPP
#define CAVE_SCENE_HPP

#include "inc/scene.hpp"
#include <array>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Audio/Music.hpp>
#include "inc/character.hpp"
#include "inc/wall.hpp"

namespace ld39 {
	class CaveScene : public Scene {
		public:
			CaveScene(sf::RenderWindow &window, std::uint64_t level);
			virtual void integrate(std::uint8_t controls) override;
			virtual void render() const override;
		private:
			void collision_resolution();
			void gravity();
			std::uint64_t level;
			Character character;
			sf::Sprite background;
			std::array<sf::Texture, 6> background_textures;
			sf::Music music;
			std::array<sf::Texture, 10> wall_textures;
			std::array<sf::Rect<float>, 10> wall_hitboxes;
			std::vector<Wall> walls;
	};
}

#endif