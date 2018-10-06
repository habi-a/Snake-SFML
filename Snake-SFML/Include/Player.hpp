#ifndef SNAKESFML_PLAYER_HPP
#define SNAKESFML_PLAYER_HPP

#include "Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			ActionCount
		};

	public:
								Player();
		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);
		void					assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(Action action) const;
		const unsigned int		getScore() const;
		void					setScore(const unsigned int score);

	private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);

	private:
		unsigned int							mScore;
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
};

#endif // SNAKESFML_PLAYER_HPP
