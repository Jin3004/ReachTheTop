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
	frame++;
}

Pointer<Game> Start::update() {
	return nullptr;
}

void Start::draw()const {
}

//------