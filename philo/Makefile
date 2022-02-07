# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 23:54:46 by nsierra-          #+#    #+#              #
#    Updated: 2022/02/07 21:02:47 by nsierra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
TEST_CMD = ./philo 5 800 200 200

SRC = src/minilibft/ft_atol.c \
	src/main.c \
	src/utils.c \
	src/utils_philo.c \
	src/utils_philo2.c \
	src/utils_forks.c \
	src/set_rules.c \
	src/philosopher.c \
	src/supervisor.c \
	src/game_init.c \
	src/game_start.c \
	src/game_destroy.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic -MMD \
			-I . \
			-I inc/ \

LDFLAGS = \

LDLIBS = -pthread \

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes \
	$(TEST_CMD)

gdb: all
	gdb --args $(TEST_CMD)

.PHONY: clean fclean re

-include $(OBJ:.o=.d)
