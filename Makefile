NAME=tamagotchi
CC=gcc
CFLAGS=-Wall -Wextra -Werror

INCLUDES = includes

SRCS = srcs/main.c		\
       srcs/db_connect.c	\

OBJS = $(SRCS:.c=.o)

CONFIGS = `pkg-config --cflags gtk+-3.0`	\
	  `pkg-config --libs gtk+-3.0`		\
	  `mysql_config --cflags`		\
	  `mysql_config --libs`



all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(CONFIGS) -I $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
