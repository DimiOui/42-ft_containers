define compiling
	@printf '$(shell tput setaf 69)Compiling$(shell tput sgr0) %s\n' $1
	@$(CC) $(CFLAGS) -c $1 -o $2
endef

define removing
	@printf '$(shell tput setaf 59)Removing$(shell tput sgr0) %s\n' $1
	@$(RM) $1 > /dev/null
endef

SRCS		=	srcs/main.cpp

OBJS		= $(SRCS:.cpp=.o)

INC			= includes/vector.hpp includes/iterator_traits.hpp includes/reverse_iterator.hpp includes/enable_if.hpp includes/equal.hpp includes/is_integral.hpp includes/lexicographical_compare.hpp includes/pair.hpp includes/map.hpp includes/map_binary_tree.hpp includes/map_iterator.hpp

NAME		= ft_containers

RM			= rm -f

CC			= c++

CFLAGS		=   -std=c++98 -Wall -Wextra -Werror -Iincludes -g3

%.o : %.cpp
			$(call compiling,$<,$(<:.cpp=.o),0)

${NAME}:	$(OBJS) $(INC)
			@printf '$(shell tput setaf 29)Finished Compiling √ %s\n$(shell tput sgr0)' $1
			@printf '$(shell tput setaf 69)Linking objs...\n$(shell tput sgr0)'
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS)
			@printf '$(shell tput setaf 29)Finished linking √ %s\n$(shell tput sgr0)' $1

all:		$(NAME)

clean:
			$(call removing,$(OBJS))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: re clean fclean
