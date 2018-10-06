#ifndef SNAKESFML_BONUS_HPP
#define SNAKESFML_BONUS_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Bonus : public Entity
{
	public:
		enum Type
		{
			Apple
		};
	public:
								Bonus(Type mType, const TextureHolder& textures);
		virtual unsigned int	getCategory() const;
		void					teleportBonus(const sf::Vector2u &windowSize, const sf::FloatRect &worldBounds, unsigned int sizeTile);

	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Type					mType;
		sf::Sprite				mSprite;
	};

#endif // SNAKESFML_BONUS_SFML
