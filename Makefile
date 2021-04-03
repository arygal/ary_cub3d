
HEADER = cub3d.h

NAME = cub3d

LIBFT = ./ary_libft

MLX = ./mlx

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS =	-I $(HEADER) \
			-L $(LIBFT) -lft \
			-L $(MLX) -lmlx -framework OpenGL -framework AppKit

SRCS =	main.c\
		settings_base.c\
		settings_color.c\
		settings_resolution.c\
		settings_textures.c\
		settings_utils.c\
		func_head.c\
		get_next_line.c\
		map_proc.c\
		map_utils.c\
		cub3d_base.c\
		cub3d_sprite.c\

OBJS = $(SRCS:.c=.o)

$(NAME): libft mlx
	$(CC) $(CFLAGS) $(OFLAGS) $(SRCS)

all: libft $(NAME)

libft:
	make -C $(LIBFT)

mlx:
	make -C $(MLX)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(MLX) clean

re: fclean all

.PHONY:			all clean fclean re