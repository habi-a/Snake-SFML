#include "../Includes/Player.hpp"
#include "../Includes/CommandQueue.hpp"
#include "../Includes/Snake.hpp"

#include <map>
#include <string>
#include <algorithm>


struct SnakeMover
{
	SnakeMover(Snake::Direction direction, float speed)
	: mDirection(direction), mSpeed(speed)
	{
	}

	void operator() (Snake& snake, sf::Time) const
	{
		Snake::Direction oldDirection = snake.getDirection();

		if (Snake::canChangeDirection(snake.getDirection(), mDirection))
		{
			snake.setDirection(mDirection);
			if (oldDirection != snake.getDirection())
			{
				snake.setIsChangingDirection(true);
				snake.adaptSnakePosition(32);
			}
		}
		snake.accelerate(mSpeed);
	}

	float				mSpeed;
	Snake::Direction	mDirection;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's snake
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerSnake;
}

const unsigned int Player::getScore() const
{
	return mScore;
}

void Player::setScore(const unsigned int score)
{
	mScore = score;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 480.f;

	mActionBinding[MoveLeft].action	 = derivedAction<Snake>(SnakeMover(Entity::West, playerSpeed));
	mActionBinding[MoveRight].action = derivedAction<Snake>(SnakeMover(Entity::East, playerSpeed));
	mActionBinding[MoveUp].action    = derivedAction<Snake>(SnakeMover(Entity::North, playerSpeed));
	mActionBinding[MoveDown].action  = derivedAction<Snake>(SnakeMover(Entity::South, playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
			return true;

		default:
			return false;
	}
}
