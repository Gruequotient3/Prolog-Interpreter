CC = gcc

PROGNAME = main

CFLAGS = -Wall -Wextra
CFLAGS += -g

LDFLAGS = -lm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

RM = rm -rf

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@


clean:
	$(RM) $(OBJ) $(PROGNAME)
