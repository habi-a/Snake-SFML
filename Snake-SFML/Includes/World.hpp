#ifndef SNAKESFML_WORLD_HPP
#define SNAKESFML_WORLD_HPP

#include "Bonus.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Snake.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include "SoundPlayer.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
    public:
        explicit                            World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds);
        void                                update(sf::Time dt);
        void                                draw();        
        unsigned int                        getSnakeScore() const;
        CommandQueue                        &getCommandQueue();
        bool                                snakeLoose() const;

    private:
        void                                updateSnakeHead();
        void                                updateSnakeBody();
        void                                updateSnakeTail();
        void                                updateSnakeSprite();
        void                                snakeBodyFollowHead();
        void                                pushSnakeBody(Snake::Type type, sf::Vector2f spawnPosition);
        void                                pushSnakeBody(Snake::Type type, float positionX, float postionY);
        void                                loadTextures();
        void                                buildScene();
        bool                                snakeEatApple() const;
        bool                                snakeEatItself() const;
        bool                                snakeIsOutWorld() const;

    private:
        enum Layer
        {
            Background,
            Ground,
            LayerCount
        };

    private:
        sf::RenderWindow                    &mWindow;
        unsigned int                        mTileSize;
        TextureHolder                       mTextures;
        FontHolder                          &mFonts;
        SoundPlayer                         &mSounds;
        SceneNode                           mSceneGraph;
        std::array<SceneNode*, LayerCount>  mSceneLayers;
        CommandQueue                        mCommandQueue;
        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        Snake                               *mPlayerSnake;
        std::vector<Snake *>                mBodySnake;
        Bonus                               *mBonus;
};

#endif // SNAKESFML_WORLD_HPP
