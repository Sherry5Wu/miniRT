# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 10:50:10 by arissane          #+#    #+#              #
#    Updated: 2024/12/12 14:52:03 by arissane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
LIBS = -lXext -lX11 -lm

SRCS = main.c \
       scene.c \
       render.c \
       free.c \
       vector_math.c\

OFILES = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./minilibx-linux
	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(MLX) $(LIBS) -o $(NAME)

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME) ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re
