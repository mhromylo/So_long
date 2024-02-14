# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 17:21:53 by mhromylo          #+#    #+#              #
#    Updated: 2024/02/13 18:39:01 by mhromylo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = *.c

OBJECTS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra# -fsanitize=address

NAME = so_long

LIBRARY := -Lminilibx -lmlx -framework OpenGL -framework AppKit

MINILIBX := minilibx/

LIBFTDIR = ./libft/

LIBFT = ./libft/libft.a

GETNEXTLINE = gnl/*.c

all:
	make -C $(MINILIBX)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(GETNEXTLINE) $(LIBRARY) -o $(NAME)

clean :
		rm -f *.o
		rm -f $(MINILIBX)*.o
		rm -f $(LIBFTDIR)*.o
		rm -f $(GETNEXTLINE)*.o
fclean: clean
		rm -f $(NAME)
		rm -f $(MINILIBX)*.o $(MINILIBX)*.a
		rm -f $(LIBFTDIR)*.o $(LIBFT)
		rm -f $(GETNEXTLINE)*.o
re: fclean all
