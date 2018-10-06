#ifndef SNAKESFML_RESOURCEIDENTIFIERS_HPP
#define SNAKESFML_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		HeadSnakeUp,
		HeadSnakeDown,
		HeadSnakeLeft,
		HeadSnakeRight,
		BodySnakeHori,
		BodySnakeVerti,
		BodySnakeTopLeft,
		BodySnakeTopRight,
		BodySnakeBottomLeft,
		BodySnakeBottomRight,
		TailSnakeUp,
		TailSnakeDown,
		TailSnakeLeft,
		TailSnakeRight, 
		Apple,
		Desert,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif // SNAKESFML_RESOURCEIDENTIFIERS_HPP
