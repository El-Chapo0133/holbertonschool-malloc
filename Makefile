CC = gcc
# -Werror says that sbrk is deprecated
CFLAGS = -Wall -Wextra -pedantic -pthread -I./ -std=gnu89

SRC0 = naive_malloc.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = naive_malloc



.PHONY: all clean oclean

all: $(OBJ0)
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)

clean:
	rm $(NAME0)

oclean:
	rm $(OBJ0)

naive: $(OBJ0)
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)


betty:
	betty *.c *h
