# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 15:32:23 by thorker           #+#    #+#              #
#    Updated: 2020/01/28 10:00:31 by sleonia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft, libtojson, all, clean, fclean, re

NAME = RT
FLAGS = -g
HEADERS =														\
			includes/rt.h										\
			includes/rt_error.h									\

SRC_DIR = src
OBJ_DIR = objects
LIB_DIR = libft
FRWR_DIR = framework
JSON_LIB_DIR = libtojson
SDL_AUDIO_PATH = ./Simple-SDL2-Audio/

SRC =															\
		realloc_img.c											\
		move.c													\
		vector.c												\
		cam_calc.c												\
		sdl.c													\
		light.c													\
		main.c													\
		init_opencl.c											\
		read_kernel.c											\
		errors_for_opencl.c										\
		music_manager.c											\

INC =															\
		-I $(LIB_DIR)/includes/									\
		-I ./includes 											\
		-I framework/SDL2.framework/Versions/A/Headers 			\
		-I framework/SDL2_image.framework/Versions/A/Headers 	\
		-I framework/SDL2_ttf.framework/Versions/A/Headers 		\
		-I framework/SDL2_mixer.framework/Versions/A/Headers/ 	\
		-F framework/											\
		-I $(JSON_LIB_DIR)/includes/							\

LIB =															\
		-L $(LIB_DIR)/ -lft										\
		-L $(JSON_LIB_DIR)/ -ltojson							\
		-L $(SDL_AUDIO_PATH) -lsdl_audio 						\

FRWR =															\
		-F framework/ -framework OpenCL							\
		-framework SDL2 -framework SDL2_image 					\
		-framework SDL2_ttf -framework SDL2_mixer				\
		-rpath frameworks/										\

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make lib_refresh
	$(CC) $(FLAGS) $(OBJ) $(INC) $(LIB) $(FRWR) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

lib_refresh:
	@make -C $(LIB_DIR)
	@make -C $(JSON_LIB_DIR)
	@make -C $(SDL_AUDIO_PATH)

clean:
	@make clean -C $(LIB_DIR)
	@make clean -C $(JSON_LIB_DIR)
	@make clean -C $(SDL_AUDIO_PATH)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(JSON_LIB_DIR)
	@make fclean -C $(SDL_AUDIO_PATH)
	rm -f $(NAME)
					
re: fclean all
