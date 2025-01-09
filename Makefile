# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 10:50:10 by arissane          #+#    #+#              #
#    Updated: 2025/01/08 14:35:06 by arissane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Werror -Wextra

# miniLibX
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = ./minilibx-linux
MLX = -L ./$(MLX_DIR)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
LIBS = -lXext -lX11 -lm
HEADER = -I./include -I./libft -I ./$(MLX_DIR)

SRCS_DIR = src
SRCS_SUDIR = objects
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUDIR))
SRCS = main.c \
       read.c \
       render.c \
       camera_ray.c \
       light_diffusion.c \
       ambient_light.c \
       free.c \
       input.c \
       spherical_linear_interpolation.c \
       vector_math.c \
       vector4_math.c \
	   plane.c \
	   sphere.c \
	   cylinder.c \

OBJS_DIR = ./obj
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

all: clone $(NAME)

clone:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_URL); \
	fi

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./minilibx-linux
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LIBS) -o $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME) ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re
