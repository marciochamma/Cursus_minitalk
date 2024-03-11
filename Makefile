# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 08:25:13 by mchamma           #+#    #+#              #
#    Updated: 2023/12/14 14:11:39 by mchamma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Werror -Wextra -Wall -g

SRC_DIR = src/
OBJ_DIR = obj/

SERVER = server
CLIENT = client

SRC_FILES_SERVER = server.c
SRC_FILES_CLIENT = client.c

SRC_SERVER = $(addprefix $(SRC_DIR), $(SRC_FILES_SERVER))
SRC_CLIENT = $(addprefix $(SRC_DIR), $(SRC_FILES_CLIENT))

OBJ_SERVER = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_SERVER))
OBJ_CLIENT = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_CLIENT))

INC = -I inc -I lib/libft/inc/
LIB = -L lib/libft/ -lft

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	cc $(OBJ_SERVER) $(INC) $(LIB) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	cc $(OBJ_CLIENT) $(INC) $(LIB) -o $(CLIENT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	clear

re: fclean all
	make clean

.PHONY: all clean fclean re