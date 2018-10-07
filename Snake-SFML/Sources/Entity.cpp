#include "../Includes/Entity.hpp"


void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::setDirection(Entity::Direction direction)
{
    mDirection = direction;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

Entity::Direction Entity::getDirection() const
{
    return mDirection;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::accelerate(float speed)
{
    switch (mDirection)
    {
    case Entity::North:
        mVelocity.x = 0.f;
        mVelocity.y = -speed;
        break;
    case Entity::East:
        mVelocity.x = speed;
        mVelocity.y = 0.f;
        break;
    case Entity::South:
        mVelocity.x = 0.f;
        mVelocity.y = speed;
        break;
    case Entity::West:
        mVelocity.x = -speed;
        mVelocity.y = 0.f;
        break;
    case Entity::None:
    default:
        break;
    }
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::updateCurrent(sf::Time dt)
{    
    move(mVelocity * dt.asSeconds());
}

unsigned int Entity::roundPosition(float position, int sizeTile)
{
    return (unsigned int)std::round(position / sizeTile) * sizeTile;
}
