# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 17:43:59 by deladia           #+#    #+#              #
#    Updated: 2020/01/24 17:18:41 by ccriston         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
FLAG = -Wall -Wextra -Werror 
SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = ./libft
LJSON_DIR = ./libtojson
FRWR_DIR = ./framework
SRC = helps.c init_object_param.c init_objects.c intersections.c light.c main.c \
	  normals.c print_error.c ray_trace.c scene_1.c scene_2.c scene_3.c scene_4.c \
	  sdl.c sdl_controls.c vector_operations_1.c vector_operations_2.c parse.c
INC = -I ./libft/includes/ \
	  -I ./libtojson/includes/ \
	  -I ./includes \
	  -I $(FRWR_DIR)/SDL2.framework/Versions/A/Headers
LIB = -L $(LIB_DIR)/ -lft
LJSON = -L $(LJSON_DIR)/ -lft
FRWR = -framework SDL2 -F ./framework
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): cr_obj_dir $(OBJ_DIR) $(OBJ)
	make lib_ft
	make lib_json
	$(CC) $(FLAG) $(OBJ) $(INC) ./libft/libft.a ./libtojson/libtojson.a $(LIB) $(LJSON) $(FRWR) -o $(NAME)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(FRWR_DIR)/SDL2.framework/Versions/A/SDL2 $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(FLAG) $(INC) -c $^ -o $@

lib_ft:
	make -C ./libft

lib_json:
	make -C ./libtojson

cr_obj_dir:
	mkdir -p $(OBJ_DIR)
clean:
	make -C $(LIB_DIR)/ clean
	make -C $(LIBJSON_DIR)/ clean
	rm -rf $(OBJ_DIR)

fclean:
	rm -f $(OBJ)
	make -C $(LIB_DIR)/ fclean
	make -C $(LIBJSON_DIR)/ fclean
	rm -f $(NAME)
					
re:
	make fclean
	make
