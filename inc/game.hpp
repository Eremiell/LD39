#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <array>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/scene.hpp"

namespace ld39 {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
			std::unique_ptr<Scene> scene;
			std::array<sf::Texture, 8> background_textures;
	};
}

#endif