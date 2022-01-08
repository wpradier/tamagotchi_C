CC=gcc
CFLAGS=-Wall
NAME=tamagotchi

all: $(NAME)

$(NAME):
	gcc main.c -o $(NAME)
