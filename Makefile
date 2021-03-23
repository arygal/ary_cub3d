
HEADER = cub3d.h

NAME = cub3d

LIBFT = ./ary_libft

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS =	-I $(HEADER) \
			-L $(LIBFT) -lft

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

OBJS = $(SRCS:.c=.o)

$(NAME): libft
	$(CC) $(CFLAGS) $(OFLAGS) $(SRCS)

all: libft $(NAME)

libft:
	make -C $(LIBFT)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY:			all clean fclean re