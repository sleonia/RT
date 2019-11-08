# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deladia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 17:43:59 by deladia           #+#    #+#              #
#    Updated: 2019/11/08 17:50:01 by deladia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
FLAG = -Wall -Wextra -Werror 
SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = ./libft
FRWR_DIR = ./framework
SRC = helps.c init_object_param.c init_objects.c intersections.c light.c main.c \
	  normals.c print_error.c ray_trace.c scene_1.c scene_2.c scene_3.c scene_4.c \
	  sdl.c sdl_controls.c vector_operations_1.c vector_operations_2.c
INC = -I ./libft/includes/ \
	  -I ./includes \
	  -I $(FRWR_DIR)/SDL2.framework/Versions/A/Headers
LIB = -L $(LIB_DIR)/ -lft
FRWR = -framework SDL2 -F ./framework
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): cr_obj_dir $(OBJ_DIR) $(OBJ)
	make lib_ft
	$(CC) $(FLAG) $(OBJ) $(INC) $(LIB) $(FRWR) -o $(NAME)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(FRWR_DIR)/SDL2.framework/Versions/A/SDL2 $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(FLAG) $(INC) -c $^ -o $@

lib_ft:
	make -C ./libft

cr_obj_dir:
	mkdir -p $(OBJ_DIR)
clean:
	make -C $(LIB_DIR)/ clean
	rm -rf $(OBJ_DIR)

fclean:
	rm -f $(OBJ)
	make -C $(LIB_DIR)/ fclean
	rm -f $(NAME)
					
re:
	make fclean
	make
