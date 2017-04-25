#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkhlopov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 15:20:54 by dkhlopov          #+#    #+#              #
#    Updated: 2017/01/22 18:53:00 by dkhlopov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

SRC = mainfdf.c putline.c addfunctions.c read.c buildmap.c events.c \
	  	  events_rotate.c events_size.c putcolors.c

LIB = libft.a

OBJ = $(SRC:.c=.o)
	    FLG = -Wall -Wextra -Werror

all:    $(NAME)

$(NAME): $(OBJ) $(LIB)
	    gcc $(FLG) $(OBJ) -o $(NAME) libft/$(LIB) \
			    -O3 -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	    gcc $(FLG) -c -o $@ $<

$(LIB):
	    make -C libft/

cleanlib:
	    make -C libft/ clean

fcleanlib:
	    make -C libft/ fclean

clean: cleanlib
	    rm -f $(OBJ)

fclean: clean fcleanlib
	    rm -f $(NAME)

re: fclean all
