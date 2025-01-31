# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 10:50:10 by arissane          #+#    #+#              #
#    Updated: 2025/01/30 11:49:32 by arissane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Werror -Wextra -DWIN_WIDTH=$(WIN_WIDTH) -DWIN_HEIGHT=$(WIN_HEIGHT)
WIN_WIDTH ?= 300
WIN_HEIGHT ?= 300

# miniLibX
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = ./minilibx-linux
MLX = -L ./$(MLX_DIR)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a
LIBS = -lXext -lX11 -lm
HEADER = -I./include -I./libft -I ./$(MLX_DIR)

SRCS_DIR = src
SRCS_SUDIR = intersection render
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUDIR))
SRCS = main.c \
       read_rt_file.c \
       read_rt_lights_camera.c \
       read_rt_object_data.c \
       read_rt_add_values.c \
       validate_number_array.c \
       utils.c \
       render.c \
       calculate_colour.c \
       modify_colours.c \
       trace_ray.c \
       camera_ray.c \
       light_diffusion.c \
       free.c \
       input.c \
       object_controls.c \
       light_controls.c \
       camera_controls.c \
       vector3_math.c \
       vector3_math2.c \
       vector4_math.c \
       vector4_conversions.c \
       plane.c \
       sphere.c \
       cylinder.c \
       intersects_cylinder_side.c \
       set_camera_light_position_info_for_objects.c \
       read_rt_object_allocate_memory.c \
       camera_controls_matrix.c

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
