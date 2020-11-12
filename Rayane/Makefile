SRC = main.cpp Joueur.cpp Action.cpp Plateau.cpp
OBJ = $(SRC:%.cpp=%.o)
NAME = exec
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++14
RM = rm -f
all: $(NAME)
$(NAME):	$(OBJ)
		$(CXX)	$(OBJ) -o $(NAME)
		
clean:
	$(RM)	$(OBJ)
fclean:	clean
	$(RM)	$(NAME)
	
re:	fclean all
.PHONY: all clean flean re
