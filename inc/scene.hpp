#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace ld39 {
	class Scene {
		public:
			Scene(sf::RenderWindow &window) : window(window) {}
			virtual void integrate() = 0;
			virtual void render() = 0;
		protected:
			sf::RenderWindow &window;
	};
}

#endif