# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 20:10:01 by tbeguin           #+#    #+#              #
#    Updated: 2019/09/23 23:01:46 by nicktor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
OS = $(shell uname)

CC = gcc
CFLAGS = -Wall -Werror -Wextra 

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

LIB_FT = ./libft
FT_LNK = -L $(LIB_FT) -l ft

SRC =  main.c	\
	   init.c	\
	   ray.c	\
	   draw.c	\
	   event.c	\
	   parser.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

ifeq ($(OS), Linux)
	MLX_DIR = ./miniLibX_X11
	MLX_LNK = -l mlx -lXext -lX11 -pthread
else
	MLX_DIR = ./minilibX
	MLX_LNK = -l mlx -framework OpenGL -framework AppKit
endif

MLX_LNK += -L $(MLX_DIR)
MLX_INC = -I $(MLX_DIR)
MLX_LIB = $(addprefix $(MLX_DIR)/,mlx.a)

all :
	@mkdir -p $(OBJ_DIR)
	@make -C $(LIB_FT)
	@make $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -c $(CFLAGS) $(MLX_INC) -I $(LIB_FT) -I $(INC_DIR) $< -o $@
	@echo "\033[36m$(CC) $(CFLAGS) -c $< -o $@\033[0m"

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "\033[32mLet's play Wolf3d\033[0m"

clean : 
	@rm -Rf $(OBJ_DIR)
	@echo "\033[31mRemoved obj files\033[0m"

fclean : clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_FT)
	@echo "\033[31mRemoved $(NAME)\033[0m"

re : fclean 
	@make all

.PHONY : all clean fclean re
