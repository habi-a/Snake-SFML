#ifndef SNAKESFML_CATEGORY_HPP
#define SNAKESFML_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None			= 0,
		Scene			= 1 << 0,
		PlayerSnake		= 1 << 1,
		BodySnake		= 1 << 2,
		Apple			= 1 << 3
	};
}

#endif // SNAKESFML_CATEGORY_HPP
