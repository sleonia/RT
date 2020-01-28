# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 15:32:23 by thorker           #+#    #+#              #
#    Updated: 2020/01/28 03:46:00 by thorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
FLAG = -g
HEADERS = includes/rt.h includes/rt_error.h
SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = libft
FRWR_DIR = framework
JSON_LIB_DIR = libtojson
SRC = realloc_img.c move.c vector.c cam_calc.c sdl.c light.c main.c init_opencl.c read_kernel.c errors_for_opencl.c music_manager.c
INC = -I $(LIB_DIR)/includes/ \
	  -I ./includes \
	  -I $(FRWR_DIR)/SDL2.framework/Versions/A/Headers 			\
	  -I $(FRWR_DIR)/SDL2_image.framework/Versions/A/Headers 	\
	  -I $(FRWR_DIR)/SDL2_mixer.framework/Versions/A/Headers 	\
	  -F $(FRWR_DIR)/											\
	  -I $(JSON_LIB_DIR)/includes/
LIB = -L $(LIB_DIR)/ -lft -L $(JSON_LIB_DIR)/ -ltojson
FRWR = -F ./framework -framework OpenCL \
	   -framework SDL2 -framework SDL2_image 	\
            -framework SDL2_ttf -framework SDL2_mixer -rpath frameworks/
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
.PHONY: libft libtojson all clean fclean re
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	make $(LIB_DIR)
	make $(JSON_LIB_DIR)
	$(CC) $(FLAG) $(OBJ) $(INC) $(LIB) $(FRWR) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(FLAG) $(INC) -c $< -o $@

$(LIB_DIR):
	make -C $(LIB_DIR)/

$(JSON_LIB_DIR):
	make -C $(JSON_LIB_DIR)/

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C $(LIB_DIR)/ clean
	make -C $(JSON_LIB_DIR)/ clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(JSON_LIB_DIR)/ fclean
	make -C $(LIB_DIR)/ fclean
	rm -f $(NAME)
					
re:
	make fclean
	make
