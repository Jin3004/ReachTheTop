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

template<typename T>
class ResourceManager {
private:
public:
	std::string base_path = "sources/"s;
	std::unordered_map<std::string, Pointer<T>> resource_data; //(ファイル名, リソースオブジェクトのポインタ)の集合

	ResourceManager() {
		static_assert(std::is_same_v<T, s3d::Texture> || std::is_same_v<T, s3d::Audio>, "Template arg is not s3d::Texture, not");
	}

	//operator[]
	T operator[](std::string filename) {

		if (resource_data.find(filename) == resource_data.end()) {
			resource_data[filename] = std::make_shared<T>(Unicode::Widen(base_path + filename));
		}

		return *(resource_data[filename]);

	}

};

struct Label {
	int32_t x, y;
	std::string str;
	void draw(Font& font, s3d::Color color) {
		font(Unicode::Widen(str)).drawAt(x, y, color);
	}
};

struct Buttons {
	std::vector<Label> labels;
	std::vector<bool> is_clicked; //どこのボタンがクリックされたか
	std::vector<bool> is_active;
	Font& font; //描画用のフォント
	int32_t focused_index = 0;
	const size_t size;

	Buttons(size_t size, Font& font) : labels(size), is_clicked(size, false), is_active(size), font(font), size(size) {}
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
	int32_t cnt = 0;

	Pointer<Game> update()override;
	void draw()const override;

};

//------



//------(グローバルオブジェクト)

Core core;
ResourceManager<Texture> textures;

//------



//------(関数・メソッドの定義)

void Core::update() {
	exit_state = System::Update();
	frame++;
}

Pointer<Game> Start::update() {
	return nullptr;
}

void Start::draw()const {

}

void Buttons::update() {

	//------(is_clickedの初期化(前フレームの状態が残っているので))

	for (size_t i = 0; i < size; ++i)is_clicked[i] = false;

	//

	//------(focus_indexの更新)

	if (DownInput.down()) {
		focused_index = (focused_index + 1) % size;
	}
	if (UpInput.down()) {
		focused_index--;
		if (focused_index == -1)focused_index = size - 1;
	}

	//------

	//------(キーの監視)

	if (EnterInput.down())is_clicked[focused_index] = true;

	//------

	//------(ボタンの描画)

	for (size_t i = 0; i < size; ++i) {
		auto& label = labels[i];
		
		//------(枠の描画)

		Rect rect{ label.x - BUTTON_WIDTH / 2, label.y - BUTTON_HEIGHT - 2, BUTTON_WIDTH, BUTTON_HEIGHT };

		{
			Transformer2D t{ Mat3x2::Rotate(2_deg, rect.pos) };
			rect.stretched(-2, 1, 1, -4).drawShadow(Vec2(0, 0), 12, 0, ColorF(0.0, 0.4));
		}

		if (i == focused_index)rect.draw(HSV(0, 0.46, 1.0));
		else

		//------

	}

	//------

}

//------