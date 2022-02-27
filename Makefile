NAME=tamagotchi
CC=gcc
CFLAGS=-Wall -Wextra -Werror

INCLUDES = includes


SRCS = srcs/main.c				\
       srcs/db_connect.c			\
       srcs/game_graphic.c			\
			 srcs/game_play_graphic.c \
       srcs/fetch_save.c			\
       srcs/conf_funcs/load_conf.c		\
       srcs/conf_funcs/print_conf.c		\
       srcs/conf_funcs/free_conf.c		\
       srcs/tamagotchi_funcs/init_tamagotchi.c	\
       srcs/tamagotchi_funcs/print_tamagotchi.c	\
       srcs/tamagotchi_funcs/free_tamagotchi.c	\
       srcs/gamestate_funcs/init_gamestate.c	\
			 srcs/init_parameters.c	\
			 srcs/home_page.c 			\
			 srcs/name_graphic.c		\
			 srcs/shop_page.c				\
			 srcs/print_parameters.c\
			 srcs/ft_strnew.c				\
			 srcs/weather.c					\
			 srcs/alert_page.c			\


OBJS = $(SRCS:.c=.o)

CONFIGS = `pkg-config --cflags gtk+-3.0`	\
	  `pkg-config --libs gtk+-3.0`		\
	  `mysql_config --cflags`		\
	  `mysql_config --libs`


all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(CONFIGS) -I $(INCLUDES) -ljson-c -lcurl -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
