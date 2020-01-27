# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deladia <deladia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 15:32:23 by thorker           #+#    #+#              #
#    Updated: 2020/01/27 04:06:40 by thorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
FLAG = -g -O3
HEADERS = includes/rt.h
SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = libft
FRWR_DIR = framework
JSON_LIB_DIR = libtojson
SRC = vector.c cam_calc.c sdl.c light.c main.c init_opencl.c read_kernel.c errors_for_opencl.c
INC = -I $(LIB_DIR)/includes/ \
	  -I ./includes \
	  -I $(FRWR_DIR)/SDL2.framework/Versions/A/Headers \
	  -I $(FRWR_DIR)/SDL2_image.framework/Versions/A/Headers \
	  -I $(JSON_LIB_DIR)/includes/
LIB = -L $(LIB_DIR)/ -lft -L $(JSON_LIB_DIR)/ -ltojson
FRWR = -framework SDL2 -F ./framework -framework OpenCL \
	   -framework SDL2_image
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
