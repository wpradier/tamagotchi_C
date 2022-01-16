NAME=tamagotchi
CC=gcc
CFLAGS=-Wall -Wextra -Werror

INCLUDES = includes

SRCS = srcs/main.c	\

OBJS = $(SRCS:.c=.o)



all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -I $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
