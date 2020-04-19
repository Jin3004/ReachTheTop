#include <Siv3D.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <type_traits>



//------(エイリアス宣言)

template<typename T>
using Pointer = std::shared_ptr<T>;

//------



//------(前方宣言)

class Core;

template<typename T>
class ResourceManager;

class Game;

class Start;

//------



//------(ユーティリティ関係)

//------