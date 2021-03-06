#ifndef BOOK_SOUNDPLAYER_HPP
#define BOOK_SOUNDPLAYER_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>


class SoundPlayer : private sf::NonCopyable
{
    public:
                                SoundPlayer();
        void                    play(Sounds::ID effect);
        void                    play(Sounds::ID effect, sf::Vector2f position);
        void                    removeStoppedSounds();
        void                    setListenerPosition(sf::Vector2f position);
        sf::Vector2f            getListenerPosition() const;

    private:
        SoundsHolder            mSoundBuffers;
        std::list<sf::Sound>    mSounds;
};

#endif // SNAKESFML_SOUNDPLAYER_HPP