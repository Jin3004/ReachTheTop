#include "definition.hpp"

void Main() {
	Pointer<Game> game_ptr = std::make_shared<Start>();
	
	std::thread update_thread{ update, std::ref(game_ptr) };
	std::thread draw_thread{ draw, std::ref(game_ptr) };

	update_thread.join(); draw_thread.join();
}