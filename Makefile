
HEADER =	cub3d.h 

NAME = cub3d

LIBFT = ./ary_libft

MLX = ./mlx	

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS =	-I $(HEADER) \
			-L $(LIBFT) -lft \
			-L $(MLX) -lmlx -framework OpenGL -framework AppKit \

SRCS =	main.c\
		settings_base.c\
		settings_color.c\
		settings_resolution.c\
		settings_textures.c\
		settings_utils.c\
		add_func.c\
		get_next_line.c\
		map_proc.c\
		map_utils.c\
		cub3d_base.c\
		cub3d_ray_cast.c\
		cub3d_bmp.c\
		inits.c\
		cub3d_draw.c\
		cub3d_controls.c\

OBJS = $(SRCS:.c=.o)

$(NAME): mlx libft
	$(CC) $(CFLAGS) $(OFLAGS) $(SRCS)

all:  $(NAME)

libft:
	make -C $(LIBFT)
mlx:
	make -C $(MLX)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY:			all clean fclean re