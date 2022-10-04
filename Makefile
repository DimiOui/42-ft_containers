define compiling
	@printf '$(shell tput setaf 69)Compiling$(shell tput sgr0) %s\n' $1
	@$(CC) $(CFLAGS) -c $1 -o $2
endef

define removing
	@printf '$(shell tput setaf 59)Removing$(shell tput sgr0) %s\n' $1
	@$(RM) $1 > /dev/null
endef

SRCS		=	srcs/main_42.cpp

OBJS		= $(SRCS:.cpp=.o)

INC			=	includes/containers/vector.hpp \
				includes/iterators/iterator_traits.hpp \
				includes/iterators/reverse_iterator.hpp \
				includes/utils/enable_if.hpp \
				includes/utils/equal.hpp \
				includes/utils/is_integral.hpp \
				includes/utils/lexicographical_compare.hpp \
				includes/utils/pair.hpp \
				includes/containers/map.hpp \
				includes/containers/stack.hpp \
				includes/utils/map_binary_tree.hpp \
				includes/iterators/map_iterator.hpp

NAME		= ft_containers

RM			= rm -f

CC			= c++

CFLAGS		=   -std=c++98 -Wall -Wextra -Werror -Iincludes/containers -g3

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
			$(RM) $(NAME) timestamps.txt

re:			fclean all

fullclean:	clean
			$(RM) $(NAME) FT STD FT_TESTS STD_TESTS timestamps.txt

.PHONY: re clean fclean
