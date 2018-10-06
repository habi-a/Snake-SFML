#ifndef SNAKESFML_RESOURCEIDENTIFIERS_HPP
#define SNAKESFML_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
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

namespace Musics
{
	enum ID
	{
		TitleTheme
	};
}

namespace Sounds
{
	enum ID
	{
		Button,
		SnakeMove,
		SnakeEatApple,
		SnakeCollision
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID>		SoundsHolder;

#endif // SNAKESFML_RESOURCEIDENTIFIERS_HPP
