# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/03 13:03:20 by sleonia           #+#    #+#              #
#    Updated: 2020/01/28 10:05:59 by sleonia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re

NAME = libsdl_audio.a

INC = audio.h
SRC = audio.c
OBJ = $(SRC:.c=.o)

INC_SDL = 		-I ../framework/SDL2.framework/Versions/A/Headers 			\
				-I ../framework/SDL2_image.framework/Versions/A/Headers 	\
				-I ../framework/SDL2_ttf.framework/Versions/A/Headers 		\
				-I ../framework/SDL2_mixer.framework/Versions/A/Headers/ 	\
				-F ../framework/

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c $(INC)
	@gcc -Wall -Werror -Wextra -c $(INC_SDL) $<

clean: 
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
