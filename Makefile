# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 15:32:23 by thorker           #+#    #+#              #
#    Updated: 2020/01/30 21:57:36 by sleonia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft, libtojson, all, clean, fclean, re

# =========== #
#	HOOKS	  #
# =========== #

HOOKS_FILES =							\
			events_processing.c			\
			key_events.c				\
			mouse_events.c				\
			move.c						\
			rotation.c					\

HOOKS_DIR = ./src/hooks/

OBJ_HOOKS_FILES = $(addprefix $(OBJ_DIR), $(HOOKS_FILES:.c=.o))

# =========== #
#	INIT	  #
# =========== #

INIT_FILES =							\
			init_cl_arg.c				\
			init_cl_files.c				\
			init_cl.c					\
			init_objects.c				\
			init_lights.c				\
			init_rt.c					\
			init_scene.c				\
			init_sdl.c					\
			init_texture.c				\

INIT_DIR = ./src/init/

OBJ_INIT_FILES = $(addprefix $(OBJ_DIR), $(INIT_FILES:.c=.o))

# =========== #
#  MATH_UTILS #
# =========== #

MATH_UTILS_FILES =						\
			cam_calc.c					\
			cl_vectors_1.c				\
			cl_vectors_2.c				\

MATH_UTILS_DIR = ./src/math_utils/

OBJ_MATH_UTILS_FILES = $(addprefix $(OBJ_DIR), $(MATH_UTILS_FILES:.c=.o))

# =========== #
#    PARSE 	  #
# =========== #

PARSE_FILES =							\
			parse_assets.c				\
			parse_cam.c					\
			parse_objects.c				\
			parse_objects_2.c			\
			parse_lights.c				\
			parse_skybox.c				\

PARSE_DIR = ./src/parse/

OBJ_PARSE_FILES = $(addprefix $(OBJ_DIR), $(PARSE_FILES:.c=.o))

# =========== #
#  SDL_UTILS  #
# =========== #

SDL_UTILS_FILES =						\
			music_manager.c				\
			sdl_loop.c					\
			sdl_quit.c					\
			sdl_update.c				\

SDL_UTILS_DIR = ./src/sdl_utils/

OBJ_SDL_UTILS_FILES = $(addprefix $(OBJ_DIR), $(SDL_UTILS_FILES:.c=.o))

# =========== #
#    UTILS    #
# =========== #

UTILS_FILES =							\
			ft_error.c					\
			ft_len_arr.c				\
			get_next_name.c				\
			int_to_rgb.c				\
			put_pixel.c					\
			read_kernel.c				\
			realloc_img.c				\

UTILS_DIR = ./src/utils/

OBJ_UTILS_FILES = $(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o))

# =========== #
#	MAIN	  #
# =========== #

MAIN_FILES =							\
			main.c						\

MAIN_DIR = ./src/

OBJ_MAIN_FILES = $(addprefix $(OBJ_DIR), $(MAIN_FILES:.c=.o))


# =========== #
#	INCLUDES  #
# =========== #

INCLUDES_FILES_LIST =					\
			kernel.h					\
			rt.h						\
			rt_error.h					\
			stb_image.h					\
			stb_image_write.h			\

INCLUDES_DIR = 	./includes/

INCLUDES_FILES = $(addprefix $(INCLUDES_DIR), $(INCLUDES_FILES_LIST))

# =========== #
#	BUILD	  #
# =========== #

NAME = RT

OBJ = 									\
		$(OBJ_HOOKS_FILES)				\
		$(OBJ_INIT_FILES)				\
		$(OBJ_MATH_UTILS_FILES)			\
		$(OBJ_SDL_UTILS_FILES)			\
		$(OBJ_PARSE_FILES)				\
		$(OBJ_UTILS_FILES)				\
		$(OBJ_MAIN_FILES)				\

OBJ_DIR = ./objects/

SRC_DIR = ./src/

SDL2_AUDIO = ./Simple-SDL2-Audio/libsdl_audio.a

INC_SDL = 	-I framework/SDL2.framework/Versions/A/Headers 			\
			-I framework/SDL2_image.framework/Versions/A/Headers 	\
			-I framework/SDL2_ttf.framework/Versions/A/Headers 		\
			-I framework/SDL2_mixer.framework/Versions/A/Headers/ 	\
			-F framework/

FRAME = 	-F framework/ -framework SDL2 -framework SDL2_image 	\
            -framework SDL2_ttf -framework SDL2_mixer				\
			-rpath framework/ -framework OpenCL

COMPILE_FLAGS = -g
# COMPILE_FLAGS = -Wall -Werror -Wextra -Ofast -g

COMPILE = gcc $(COMPILE_FLAGS) -I $(INCLUDES_DIR) $(INC_SDL) -I $(LIBFT_INC) -I $(LIBTOJSON_INC) -I $(SDL2_AUDIO_INC) $(INC_SDL)

RT_LIBS = -L $(LIBFT_DIR) -lft -L $(SDL2_AUDIO_DIR) -lsdl_audio -L $(LIBTOJSON_DIR) -ltojson

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INCLUDES_FILES)
	@make lib_refresh
	@$(COMPILE) $(RT_LIBS) $(OBJ) -o $(NAME) $(FRAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(HOOKS_DIR)%.c $(INCLUDES_FILES)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(INIT_DIR)%.c $(INCLUDES_FILES)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(MATH_UTILS_DIR)%.c $(INCLUDES_FILES)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSE_DIR)%.c $(INCLUDES_FILES)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(SDL_UTILS_DIR)%.c $(INCLUDES_FILES)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSE_DIR)%.c $(INCLUDES_FI)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c $(INCLUDES_FI)
	@$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o: $(MAIN_DIR)%.c $(INCLUDES_FI)
	@$(COMPILE) -c $< -o $@

lib_refresh:
	@make -C $(LIBFT_DIR)
	@make -C $(LIBTOJSON_DIR)
	@make -C $(SDL2_AUDIO_DIR)

clean:
	@clear
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(SDL2_AUDIO_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make clean -C $(LIBFT_DIR)
	@make fclean -C $(SDL2_AUDIO_DIR)

re: fclean $(NAME)

# =========== #
# 	COLORS	  #
# =========== #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
AQUA = \033[36m
GREY = \033[37m
UNDERLINE = \033[4m
NORMAL = \033[0m

# =========== #
# 	LIBFT	  #
# =========== #

LIBFT_DIR =					\
	./libft/				\

LIBFT_INC = 				\
	./libft/includes/		\

$(LIBFT):
	@make -C $(LIBFT_DIR)

# =========== #
#  LIBTOJSON  #
# =========== #

LIBTOJSON_DIR =					\
	./libtojson/				\

LIBTOJSON_INC = 				\
	./libtojson/includes/		\

$(LIBTOJSON):
	@make -C $(LIBTOJSON_DIR)

# ======================= #
#     SIMPLE_SDL2_AUDIO	  #
# ======================= #

SDL2_AUDIO_DIR =			\
	./Simple-SDL2-Audio/	\

SDL2_AUDIO_INC = 			\
	./Simple-SDL2-Audio/	\

$(SDL2_AUDIO):
	@make -C $(SDL2_AUDIO_DIR)
