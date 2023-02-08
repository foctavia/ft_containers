# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 12:22:12 by foctavia          #+#    #+#              #
#    Updated: 2023/02/08 16:41:10 by foctavia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		= "\033[1;32m"
RESET		= "\033[m"

# Variables
NAME		= ft_containers

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -g
REAL 		= 0

CONTDIR		= inc/containers/ 
UTILSDIR	= inc/utils/
SRCDIR		= src/
OBJDIR		= obj/

SRC			= test.cpp
				
OBJ			= $(addprefix ${OBJDIR}, ${SRC:%.cpp=%.o})
INC			= -I./$(CONTDIR) -I./$(UTILSDIR)

ifeq ($(REAL),1)
CXXFLAGS 	+= -DREAL=1
endif

ifeq ($(REAL),0)
CXXFLAGS 	+= -std=c++98
endif

ifeq ($(DMEM),1)
CXXFLAGS 	+= -fsanitize=address
endif

# Rules
all			: $(NAME)

diff:
	make re
	make re NAME=std_containers REAL=1
	./ft_containers 2>/dev/null 1>ft
	./std_containers 2>/dev/null 1>std
	diff ft std

$(OBJDIR)%.o: $(SRCDIR)%.cpp
			@mkdir -p ${@D}
			$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(NAME)		: $(OBJ)
			$(CXX) $(CXXFLAGS) $(INC) $(OBJ) -o $@
			@echo "Compiling ft_containers"$(GREEN)"\tOK"$(RESET)

clean		:
			rm -rf $(OBJDIR)

fclean		: clean
			@rm -f $(NAME)
			@rm -f std_containers
			@rm -f ft
			@rm -f std
			@echo "Delete binary files"

re			: fclean
			make all

.PHONY		: all clean fclean re
