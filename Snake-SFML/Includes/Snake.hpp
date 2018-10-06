#ifndef SNAKESFML_SNAKE_HPP
#define SNAKESFML_SNAKE_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Snake : public Entity
{
	public:
		enum Type
		{
			Head,
			Body,
			Tail,
		};

	public:
								Snake(Type type, const TextureHolder& textures);
		void					adaptSnakePosition(unsigned int sizeTile);
		bool					isChangingDirection() const;
		void					setIsChangingDirection(bool isChangingDirection);
		static bool				canChangeDirection(Direction direction_one, Direction direction_two);
		sf::Sprite				&getSprite();
		virtual unsigned int	getCategory() const;
		const unsigned int		getScore() const;
		void					setScore(const unsigned int score);

	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		bool					mIsChangingDirection;
		Type					mType;
		sf::Sprite				mSprite;
		unsigned int			mScore;
};

#endif // SNAKESFML_SNAKE_HPP
