default: 	all

NAME 		= snake-sfml.out

CC 			= g++
CPPFLAGS	+= -W -Wall -Wextra -Werror -O3 --std=c++14
LDFLAGS		+= -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

SRC_DIR		= ./Snake-SFML/Sources
SRC			= $(SRC_DIR)/Bonus.cpp \
			$(SRC_DIR)/Container.cpp \
			$(SRC_DIR)/Main.cpp \
			$(SRC_DIR)/SceneNode.cpp \
			$(SRC_DIR)/SpriteNode.cpp \
			$(SRC_DIR)/World.cpp \
			$(SRC_DIR)/Button.cpp \
			$(SRC_DIR)/Entity.cpp \
			$(SRC_DIR)/MenuState.cpp \
			$(SRC_DIR)/SettingsState.cpp \
			$(SRC_DIR)/State.cpp \
			$(SRC_DIR)/Command.cpp \
			$(SRC_DIR)/GameOverState.cpp \
			$(SRC_DIR)/MusicPlayer.cpp \
			$(SRC_DIR)/Snake.cpp \
			$(SRC_DIR)/StateStack.cpp \
			$(SRC_DIR)/CommandQueue.cpp \
			$(SRC_DIR)/GameState.cpp \
			$(SRC_DIR)/PauseState.cpp \
			$(SRC_DIR)/SoundNode.cpp \
			$(SRC_DIR)/TitleState.cpp

OBJ			= $(SRC:.cpp=.o)

RM			= rm -f


all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
