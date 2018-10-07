#include "../Includes/Snake.hpp"
#include "../Includes/ResourceHolder.hpp"
#include "../Includes/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Textures::ID toTextureID(Snake::Type type)
{
    switch (type)
    {
        case Snake::Head:
            return Textures::HeadSnakeRight;

        case Snake::Tail:
            return Textures::TailSnakeLeft;

        default:
        case Snake::Body:
            return Textures::BodySnakeHori;
    }
    return Textures::BodySnakeHori;
}

Snake::Snake(Type type, const TextureHolder& textures)
: mType(type)
, mScore(0)
, mSprite(textures.get(toTextureID(type)))
{
}

sf::Sprite &Snake::getSprite()
{
    return mSprite;
}

const unsigned int Snake::getScore() const
{
    return mScore;
}

void Snake::setScore(const unsigned int score)
{
    mScore = score;
}

bool Snake::isChangingDirection() const
{
    return mIsChangingDirection;
}

void Snake::setIsChangingDirection(bool isChangingDirection)
{
    mIsChangingDirection = isChangingDirection;
}

void Snake::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Snake::getCategory() const
{
    switch (mType)
    {
        case Head:
            return Category::PlayerSnake;

        default:
            return Category::BodySnake;
    }
}

void Snake::adaptSnakePosition(unsigned int sizeTile)
{
    setPosition((float)Entity::roundPosition(getPosition().x, sizeTile), (float)Entity::roundPosition(getPosition().y, sizeTile));
}

bool Snake::canChangeDirection(Direction current_direction, Direction new_direction)
{
    if (new_direction == None)
        return false;
    else if (current_direction == None && new_direction == West)
        return false;
    else if (current_direction == East && new_direction == West)
        return false;
    else if (current_direction == West && new_direction == East)
        return false;
    else if (current_direction == North && new_direction == South)
        return false;
    else if (current_direction == South && new_direction == North)
        return false;
    return true;
}
