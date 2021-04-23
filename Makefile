
# HEADER =	cub3d.h 

NAME = cub3d

LIBFT = ./libft

MLX = ./mlx	

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

OFLAGS = #-O2

DFLAGS = -g

LFLAGS =	-L $(LIBFT) -lft \
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

OBJS = $(patsubst %.c,%.o,$(SRCS))

DINF = $(patsubst %.c,%.d,$(SRCS))

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C $(MLX) all
	$(CC) $(CFLAGS)  $(LFLAGS) $(OFLAGS) $(OBJS) -o $(NAME)

all:  $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ -MD

include $(wildcard $(DINF))

debug: 
	make -C $(LIBFT)
	make -C $(MLX) all
	$(CC) $(CFLAGS) $(LFLAGS) $(DFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(DINF)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	$(RM) $(NAME) $(DINF)
	$(RM) img.bmp
	make -C $(LIBFT) fclean
	make -C $(MLX) clean

re: fclean all

.PHONY:			all clean fclean re