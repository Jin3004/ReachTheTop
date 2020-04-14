#pragma once
#include "declaration.hpp"



//------(クラスの定義)

class Core {
public:
	//System::Update()の戻り値
	bool exit_state = true;
	//何フレームか
	uint64_t frame = 0;
	//ログ。アプリ終了時にテキストに書き込む
	std::string log = ""s;

	void update();

};

extern Core core;

class Game {
public:
	//初期化関数。Gameのインスタンスが変更した際に実行する
	virtual void initialize() {}
	//毎フレーム実行される
	virtual Pointer<Game> update() { return nullptr; }
	//毎フレーム実行される(update()とは別スレッドで)
	virtual void draw()const {}
};

class Start : public Game {
public:
	Pointer<Game> update()override;
	void draw()const override;
};

//------

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

//------(関数・メソッドの定義)