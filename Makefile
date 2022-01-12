CC=gcc
CFLAGS=-Wall
NAME=tamagotchi

all: $(NAME)

$(NAME):
	gcc `pkg-config --cflags gtk+-3.0` -o $(NAME) main.c `pkg-config --libs gtk+-3.0`
