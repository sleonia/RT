# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deladia <deladia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 15:32:23 by thorker           #+#    #+#              #
#    Updated: 2019/12/07 18:58:34 by deladia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
FLAG = -g 
SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = ./libft
FRWR_DIR = ./framework
SRC = sdl.c helps.c light.c main.c normals.c get_intersect.c init_opencl.c read_kernel.c errors_for_opencl.c
INC = -I ./libft/includes/ \
	  -I ./includes \
	  -I $(FRWR_DIR)/SDL2.framework/Versions/A/Headers
LIB = -L $(LIB_DIR)/ -lft
FRWR = -framework SDL2 -F ./framework -framework OpenCL
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
