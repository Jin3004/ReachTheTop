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