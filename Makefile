CC = gcc
# -Werror says that sbrk is deprecated
CFLAGS = -Wall -Wextra -pedantic -pthread -I./ -std=gnu89

SRC0 = naive_malloc.c brk_utils.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = naive_malloc

SRC1 = _malloc.c brk_utils.c
OBJ1 = $(SRC1:.c=.o)
NAME1 = _malloc


.PHONY: all clean oclean

all: $(OBJ0) $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)
	$(CC) $(CFLAGS) $(OBJ1) -o $(NAME1)

clean:
	rm $(NAME0)
	rm $(NAME1)

oclean:
	rm $(OBJ0)
	rm $(OBJ1)

naive: $(OBJ0)
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)

malloc: $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $(NAME1)

betty:
	betty *.c *h
