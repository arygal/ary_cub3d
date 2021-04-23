# HEADER = libft.h

NAME = libft.a

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

OFLAGS = -O2

# OFLAGS = -c -I $(HEADER)

SRCS =	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c

# OBJS = $(SRCS:.c=.o)

OBJS = $(patsubst %.c,%.o,$(SRCS))

DINF = $(patsubst %.c,%.d,$(SRCS))

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)


%.o : %.c
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@ -MD

include $(wildcard $(DINF))

clean:
	$(RM) $(OBJS) $(DINF)

fclean: clean
	$(RM) $(NAME) $(DINF)

re: fclean all

.PHONY:	all clean fclean re