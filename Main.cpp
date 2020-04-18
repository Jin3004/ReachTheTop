#include "definition.hpp"

void Main() {
	Pointer<Game> game_ptr = std::make_shared<Start>();

	const auto update = [&]() {

		while (core.exit_state) {
			core.exit_state = System::Update();
			core.update();
			auto res = game_ptr->update();
			if (res != nullptr)game_ptr = res;
		}

	};

	const auto draw = [&]() {
		
		while (core.exit_state) {
			game_ptr->draw();
		}

	};

	std::thread update_thread{ update };
	std::thread draw_thread{ draw };

	update_thread.join(); draw_thread.join();
}