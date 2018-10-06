#include "../Includes/World.hpp"
#include "../Includes/SoundNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds)
: mWindow(window)
, mTileSize(32)
, mTextures()
, mFonts(fonts)
, mSounds(sounds)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, (float)mWindow.getSize().x, (float)mWindow.getSize().y)
, mSpawnPosition((float)Entity::roundPosition(mWindow.getSize().x / 5.f, mTileSize), (float)Entity::roundPosition(mWorldBounds.height - mWindow.getSize().y / 2.f, mTileSize))
, mPlayerSnake(nullptr)
, mBonus(nullptr)
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	// Forward commands to scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	// Check if Snake is changing of direction
	if (mPlayerSnake->isChangingDirection())
	{
		mSounds.play(Sounds::SnakeMove);
		mPlayerSnake->setIsChangingDirection(false);
	}

	// Check if Snake is eating the Apple
	if (snakeEatApple())
	{
		mSounds.play(Sounds::SnakeEatApple);
		mBonus->teleportBonus(mWindow.getSize(), mWorldBounds, mTileSize);
		mPlayerSnake->setScore(mPlayerSnake->getScore() + 1);
		pushSnakeBody(Snake::Body, mPlayerSnake->getPosition());
	}
	else if (mPlayerSnake->getDirection())
		snakeBodyFollowHead();

	// Update Sprite
	updateSnakeSprite();

	// Regular update step
	mSceneGraph.update(dt);
}

void World::updateSnakeSprite()
{
	updateSnakeBody();
	updateSnakeHead();
	updateSnakeTail();
}

void World::updateSnakeHead()
{
	switch (mPlayerSnake->getDirection())
	{
		case Snake::North:
			mPlayerSnake->getSprite().setTexture(mTextures.get(Textures::HeadSnakeUp));
			break;
		case Snake::South:
			mPlayerSnake->getSprite().setTexture(mTextures.get(Textures::HeadSnakeDown));
			break;
		case Snake::West:
			mPlayerSnake->getSprite().setTexture(mTextures.get(Textures::HeadSnakeLeft));
			break;
		case Snake::East:
			mPlayerSnake->getSprite().setTexture(mTextures.get(Textures::HeadSnakeRight));
			break;
	}
}
void World::updateSnakeBody()
{
	size_t i = 1;

	while (i < mBodySnake.size())
	{
		Snake *next		= nullptr;
		Snake *current	= mBodySnake[i];
		Snake *previous = mBodySnake[i - 1];

		if (i + 1 == mBodySnake.size())
			next = mPlayerSnake;
		else
			next = mBodySnake[i + 1];

		// Horizontal Texture
		if (previous->getPosition().y == next->getPosition().y)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeHori));

		// Vertical Texture
		else if (previous->getPosition().x == next->getPosition().x)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeVerti));

		// Top Left Texture
		else if (previous->getPosition().y > current->getPosition().y
			&& next->getPosition().x > current->getPosition().x)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeTopLeft));
		else if (previous->getPosition().x > current->getPosition().x
			&& next->getPosition().y > current->getPosition().y)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeTopLeft));

		// Top Right Texture
		else if (previous->getPosition().y > current->getPosition().y
			&& next->getPosition().x < current->getPosition().x)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeTopRight));
		else if (previous->getPosition().x < current->getPosition().x
			&& next->getPosition().y > current->getPosition().y)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeTopRight));

		// Bottom Left Texture
		else if (previous->getPosition().y < current->getPosition().y
			&& next->getPosition().x > current->getPosition().x)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeBottomLeft));
		else if (previous->getPosition().x > current->getPosition().x
			&& next->getPosition().y < current->getPosition().y)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeBottomLeft));

		// Bottom Right Texture
		else if (previous->getPosition().y < current->getPosition().y
			&& next->getPosition().x < current->getPosition().x)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeBottomRight));
		else if (previous->getPosition().x < current->getPosition().x
			&& next->getPosition().y < current->getPosition().y)
			current->getSprite().setTexture(mTextures.get(Textures::BodySnakeBottomRight));

		i++;
	}
}

void World::updateSnakeTail()
{
	Snake *tail = mBodySnake.front();

	if (tail->getPosition().x < mBodySnake[1]->getPosition().x)
		tail->getSprite().setTexture(mTextures.get(Textures::TailSnakeLeft));
	else if (tail->getPosition().x > mBodySnake[1]->getPosition().x)
		tail->getSprite().setTexture(mTextures.get(Textures::TailSnakeRight));
	else if (tail->getPosition().y < mBodySnake[1]->getPosition().y)
		tail->getSprite().setTexture(mTextures.get(Textures::TailSnakeUp));
	else
		tail->getSprite().setTexture(mTextures.get(Textures::TailSnakeDown));
}

void World::draw()
{
	mWindow.draw(mSceneGraph);
}

unsigned int World::getSnakeScore() const
{
	return mPlayerSnake->getScore();
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::HeadSnakeUp,			"Ressources/Textures/Snake/Head/Up.png");
	mTextures.load(Textures::HeadSnakeDown,			"Ressources/Textures/Snake/Head/Down.png");
	mTextures.load(Textures::HeadSnakeLeft,			"Ressources/Textures/Snake/Head/Left.png");
	mTextures.load(Textures::HeadSnakeRight,		"Ressources/Textures/Snake/Head/Right.png");
	mTextures.load(Textures::BodySnakeHori,			"Ressources/Textures/Snake/Body/Horizontal.png");
	mTextures.load(Textures::BodySnakeVerti,		"Ressources/Textures/Snake/Body/Vertical.png");
	mTextures.load(Textures::BodySnakeTopLeft,		"Ressources/Textures/Snake/Body/TopLeft.png");
	mTextures.load(Textures::BodySnakeTopRight,		"Ressources/Textures/Snake/Body/TopRight.png");
	mTextures.load(Textures::BodySnakeBottomLeft,	"Ressources/Textures/Snake/Body/BottomLeft.png");
	mTextures.load(Textures::BodySnakeBottomRight,	"Ressources/Textures/Snake/Body/BottomRight.png");
	mTextures.load(Textures::TailSnakeUp,			"Ressources/Textures/Snake/Tail/Up.png");
	mTextures.load(Textures::TailSnakeDown,			"Ressources/Textures/Snake/Tail/Down.png");
	mTextures.load(Textures::TailSnakeLeft,			"Ressources/Textures/Snake/Tail/Left.png");
	mTextures.load(Textures::TailSnakeRight,		"Ressources/Textures/Snake/Tail/Right.png");
	mTextures.load(Textures::Apple,					"Ressources/Textures/Bonus/Apple.png");
	mTextures.load(Textures::Desert,				"Ressources/Textures/Backgrounds/GameState/Background.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add Apple
	std::unique_ptr<Bonus> Apple(new Bonus(Bonus::Apple, mTextures));
	mBonus = Apple.get();
	mBonus->teleportBonus(mWindow.getSize(), mWorldBounds, mTileSize);
	mSceneLayers[Ground]->attachChild(std::move(Apple));

	// Add player's snake head
	std::unique_ptr<Snake> leader(new Snake(Snake::Head, mTextures));
	mPlayerSnake = leader.get();
	mPlayerSnake->setPosition(mSpawnPosition);
	mSceneLayers[Ground]->attachChild(std::move(leader));
	
	// Add tail of the Snake
	pushSnakeBody(Snake::Tail, mSpawnPosition.x - mTileSize * 3, mSpawnPosition.y);

	// Add body of the Snake
	pushSnakeBody(Snake::Body, mSpawnPosition.x - mTileSize * 2, mSpawnPosition.y);
	pushSnakeBody(Snake::Body, mSpawnPosition.x - mTileSize * 1, mSpawnPosition.y);
}

void World::pushSnakeBody(Snake::Type type, sf::Vector2f spawnPosition)
{
	std::unique_ptr<Snake> body(new Snake(type, mTextures));
	mBodySnake.push_back(body.get());
	mBodySnake.back()->setPosition(spawnPosition);
	mSceneLayers[Ground]->attachChild(std::move(body));
}

void World::pushSnakeBody(Snake::Type type, float positionX, float postionY)
{
	std::unique_ptr<Snake> body(new Snake(type, mTextures));
	mBodySnake.push_back(body.get());
	mBodySnake.back()->setPosition(positionX, postionY);
	mSceneLayers[Ground]->attachChild(std::move(body));
}

void World::snakeBodyFollowHead()
{
	for (size_t i = 0; i != mBodySnake.size() - 1; i++)
	{
		mBodySnake[i]->setPosition(mBodySnake[i + 1]->getPosition());
		if (i + 1 == mBodySnake.size() - 1)
			mBodySnake[i + 1]->setPosition(mPlayerSnake->getPosition());
	}
}

bool World::snakeEatApple() const
{
	if (Entity::roundPosition(mPlayerSnake->getPosition().x, mTileSize) == mBonus->getPosition().x
		&& Entity::roundPosition(mPlayerSnake->getPosition().y, mTileSize) == mBonus->getPosition().y
		&& mBonus->getCategory() == Category::Apple)
		return true;
	return false;
}

bool World::snakeEatItself() const
{
	for (auto partOfBody : mBodySnake)
	{
		if (Entity::roundPosition(mPlayerSnake->getPosition().x, mTileSize) == Entity::roundPosition(partOfBody->getPosition().x, mTileSize)
			&& Entity::roundPosition(mPlayerSnake->getPosition().y, mTileSize) == Entity::roundPosition(partOfBody->getPosition().y, mTileSize))
		{
			mSounds.play(Sounds::SnakeEatApple);
			return true;
		}
	}
	return false;
}

bool World::snakeIsOutWorld() const
{
	if (!mWorldBounds.contains(mPlayerSnake->getPosition()))
	{
		mSounds.play(Sounds::SnakeCollision);
		return true;
	}
	return false;
}

bool World::snakeLoose() const
{
	return snakeIsOutWorld() || snakeEatItself();
}
