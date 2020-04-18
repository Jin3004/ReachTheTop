#include <Siv3D.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <type_traits>



//------(エイリアス宣言)

template<typename T>
using Pointer = std::shared_ptr<T>;

//------


//------(コンセプト)

template<typename T>
concept ResourceClass = std::is_same_v<T, s3d::Texture> || std::is_same_v<T, s3d::Audio>;

//------



//------(前方宣言)

class Core;

template<typename T>
class ResourceManager;

class Game;

class Start;

//------