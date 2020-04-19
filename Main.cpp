#include "definition.hpp"

void Main() {
	
	Pointer<Game> game_ptr = std::make_shared<Start>();


	while (core.exit_state) {

		core.update();

		auto res = game_ptr->update();
		game_ptr->draw();

		if (res != nullptr)game_ptr = res;
	}

}