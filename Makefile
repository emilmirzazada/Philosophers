# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 16:30:00 by emirzaza          #+#    #+#              #
#    Updated: 2023/09/26 18:45:11 by emirzaza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ_DIR = obj/
SRC_DIR = src/

SRC =	main \
		init \
		tools \
		life \
		time \
		routine \
		forks \
		mutexes	\
		parser

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
		

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: ${NAME}

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	@${RM} ${OBJS}
	@echo "Cleaned"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re