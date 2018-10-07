#ifndef SNAKESFML_ENTITY_HPP
#define SNAKESFML_ENTITY_HPP

#include "SceneNode.hpp"


class Entity : public SceneNode
{
    public:
        enum Direction
        {
            None,
            North,
            East,
            South,
            West
        };

    public:
        void                setVelocity(sf::Vector2f velocity);
        void                setVelocity(float vx, float vy);
        void                setDirection(Direction direction);
        void                accelerate(sf::Vector2f velocity);
        void                accelerate(float vx, float vy);
        void                accelerate(float speed);
        sf::Vector2f        getVelocity() const;
        Direction           getDirection() const;
        static unsigned int roundPosition(float position, int sizeTile);

    private:
        virtual void        updateCurrent(sf::Time dt);

    private:
        Direction           mDirection;
        sf::Vector2f        mVelocity;
};

#endif // SNAKESFML_ENTITY_HPP
