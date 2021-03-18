
HEADER = *.h

NAME = cub.a

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS = -c -I $(HEADER)

SRCS = *.c

OBJS = $(SRCS:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) $(OFLAGS) $(SRCS)
	ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re