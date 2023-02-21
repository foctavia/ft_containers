# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 12:22:12 by foctavia          #+#    #+#              #
#    Updated: 2023/02/21 10:35:40 by foctavia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
BLUE		= "\033[1;34m"
RESET		= "\033[m"
END			= "\e[0m"

# Variables
NAME		= ft_containers

STD			= std_containers

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

CONTDIR		= headers/containers/ 
UTILDIR		= headers/utils/
TESTDIR		= tests/
OBJDIR		= obj/

TEST		= mainTest.cpp \
				mapTest.cpp \
				vectorTest.cpp \
				setTest.cpp \
				utils.cpp \
				# stackTest.cpp \
				
OBJ			= $(addprefix ${OBJDIR}, ${TEST:%.cpp=%.o})
INC			= -I./$(CONTDIR) -I./$(UTILDIR)

ifeq ($(REAL),1)
CXXFLAGS 	+= -DREAL=1
endif

ifeq ($(DMEM),1)
CXXFLAGS 	+= -fsanitize=address -fno-omit-frame-pointer -g
endif

# Rules
all			: $(NAME)

diff		: 
	make re
	make re NAME=std_containers REAL=1
	@echo "Checking diff between ft and std"
	@./$(NAME) 5 2>/dev/null 1>ft
	@./$(STD) 5 2>/dev/null 1>std
	@DIFF=$$(diff ft std >/dev/null 2>&1; echo $$?) ; \
	export DIFF ; \
	$(MAKE) check_diff

check_diff	:
ifeq ($(DIFF),0)
	@echo $(GREEN)"OK - ft and std output are the same"$(RESET)
else
	@echo $(RED)"KO - ft and std differ"$(RESET)
endif

$(OBJDIR)%.o: $(TESTDIR)%.cpp
			@mkdir -p ${@D}
			@$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(NAME)		: $(OBJ)
			$(CXX) $(CXXFLAGS) $(INC) $(OBJ) -o $@
			@echo "Compiling ft_containers"$(GREEN)"\tOK"$(RESET)

clean		:
			@rm -rf $(OBJDIR)

fclean		: clean
			@rm -f $(NAME)
			@rm -f std_containers
			@rm -f ft
			@rm -f std
			@echo "Delete binary files"

re			: fclean
			make all

.PHONY		: all clean fclean re
