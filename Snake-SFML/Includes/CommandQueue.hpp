#ifndef SNAKESFML_COMMANDQUEUE_HPP
#define SNAKESFML_COMMANDQUEUE_HPP

#include "Command.hpp"

#include <queue>


class CommandQueue
{
	public:
		void						push(const Command& command);
		Command						pop();
		bool						isEmpty() const;

		
	private:
		std::queue<Command>			mQueue;
};

#endif // SNAKESFML_COMMANDQUEUE_HPP
