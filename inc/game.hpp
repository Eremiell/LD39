#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace ld39 {

	class Game {
		public:
			Game() : window(sf::VideoMode(1000, 500), "LD39", sf::Style::Titlebar | sf::Style::Close) {}
			void run();
		private:
			sf::RenderWindow window;
	};

}

#endif