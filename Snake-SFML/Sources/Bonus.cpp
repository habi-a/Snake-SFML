#include "../Includes/Bonus.hpp"

#include "../Includes/ResourceHolder.hpp"
#include "../Includes/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Textures::ID toTextureID(Bonus::Type type)
{
    switch (type)
    {
    case Bonus::Apple:
        return Textures::Apple;

    default:
        return Textures::Apple;
    }
    return Textures::Apple;
}

Bonus::Bonus(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
}

void Bonus::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Bonus::getCategory() const
{
    switch (mType)
    {
    case Apple:
        return Category::Apple;

    default:
        return Category::Apple;
    }
}

void Bonus::teleportBonus(const sf::Vector2u &windowSize, const sf::FloatRect &worldBounds, unsigned int sizeTile)
{
    setPosition((float)Entity::roundPosition(rand() % windowSize.x, sizeTile), (float)Entity::roundPosition(rand() % windowSize.y, sizeTile));
    while (!worldBounds.contains(getPosition()))
        setPosition((float)Entity::roundPosition(rand() % windowSize.x, sizeTile), (float)Entity::roundPosition(rand() % windowSize.y, sizeTile));
}
