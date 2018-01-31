all: example

example: src/ft_malloc.c
	gcc example.c src/ft_malloc.c -I./include
