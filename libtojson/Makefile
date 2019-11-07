# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deladia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 20:57:04 by deladia           #+#    #+#              #
#    Updated: 2019/11/07 23:00:25 by deladia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libtojson.a
INC = -I ./includes/ \
	  -I ../libft/includes/
SRC_DIR = src
OBJ_DIR = object
LIB_DIR	= ../libft
LIB = -L $(LIBFT_DIR)/ -lft
SRC = parser.c ft_return.c ft_print.c creation_token_list.c
FLAGS = -Wall -Wextra -Werror
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(NAME): cr_obj_dir $(OBJ_DIR) $(OBJ)
		make lib_ft
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@$(CC) $(FLAG) $(INC) -c $^ -o $@

lib_ft:
		make -C ../libft

cr_obj_dir:
		mkdir -p $(OBJ_DIR)

clean:
		make -C $(LIB_DIR)/ clean
		rm -rf $(OBJ_DIR)
		
fclean: clean
		rm -f $(OBJ)
		make -C $(LIB_DIR)/ fclean
		rm -f $(NAME)

re: fclean $(NAME)
