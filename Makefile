# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 20:10:01 by tbeguin           #+#    #+#              #
#    Updated: 2019/09/21 05:33:57 by tbeguin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

LIB_FT = ./libft
FT_LNK = -L $(LIB_FT) -l ft

SRC =  main.c
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))




all :
	@mkdir -p $(OBJ_DIR)
	@make -C $(LIB_FT)
	@make $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -c $(CFLAGS) -I $(LIB_FT) -I $(INC_DIR) $< -o $@
	@echo "\033[36m$(CC) $(CFLAGS) -c $< -o $@\033[0m"

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit \
		$(FT_LNK) $(OBJ) -o $(NAME)
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
