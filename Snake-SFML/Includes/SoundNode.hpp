#ifndef SNAKESFML_SOUNDNODE_HPP
#define SNAKESFML_SOUNDNODE_HPP

#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"


class SoundPlayer;

class SoundNode : public SceneNode
{
    public:
        explicit                SoundNode(SoundPlayer& player);
        void                    playSound(Sounds::ID sound, sf::Vector2f position);
        virtual unsigned int    getCategory() const;

    private:
        SoundPlayer             &mSounds;
};

#endif // SNAKESFML_SOUNDNODE_HPP