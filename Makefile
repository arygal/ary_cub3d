
HEADER = cub3d.h

NAME = a.out

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS = -I $(HEADER)

SRCS =	main.c\
		settings_base.c\
		settings_color.c\
		settings_resolution.c\
		settings_textures.c\
		settings_utils.c\
		func_head.c\
		get_next_line.c\

OBJS = $(SRCS:.c=.o)

$(NAME): libft
	$(CC) $(CFLAGS) $(OFLAGS) $(SRCS)

all: libft $(NAME)

libft:
	make -C ary_libft/

clean:
	$(RM) $(OBJS)
	make -C ary_libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ary_libft/ fclean

re: fclean all

.PHONY:			all clean fclean re