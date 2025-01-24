C = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

SRC0 = naive_malloc.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = naive_malloc



.PHONY: all clean oclean

all:
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)

clean:
	rm $(NAME0)

oclean:
	rm $(OBJ0)

naive:
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)


betty:
	betty *.c *h
