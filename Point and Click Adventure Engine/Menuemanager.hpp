#pragma once
#include "Menue.hpp"
#include "Rendering.hpp"

#include <SFML\System\Clock.hpp>

#include <string>
#include <list>

namespace pc {
	namespace Lvleditor {
		class Menuemanager
		{
		public:
			Menuemanager();

			~Menuemanager();

			void open(std::string menue_id);
			void close(std::string menue_id);
			void draw(pc::Rendering& renderer);

		private:
			std::list<pc::Lvleditor::Menue*> active_menues;
			std::list<std::string> active_menues_id;
			sf::Clock clock;
		}; //class
	} //Lvleditor
} //pc