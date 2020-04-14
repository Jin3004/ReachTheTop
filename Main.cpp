#include "definition.hpp"

Core core;

void Main() {
	Pointer<Game> game_ptr = std::make_shared<Start>();
	
	std::thread update_thread{ update, game_ptr };
	std::thread draw_thread{ draw, game_ptr };

	update_thread.join(); draw_thread.join();
}



//------(関数・メソッドの定義)

void update(Pointer<Game>& ptr) {
	while (core.exit_state) {
		core.exit_state = System::Update();
		core.update();
		auto res = ptr->update();
		if (res != nullptr)ptr = res;
	}
}

void draw(Pointer<Game>& ptr) {
	while (core.exit_state) {
		ptr->draw();
	}
}

void Core::update() {
	frame++;
}

Pointer<Game> Start::update() {
	return nullptr;
}

void Start::draw()const {
	Rect(0, 0, 400, 400).draw(Palette::Blue);
}

//------