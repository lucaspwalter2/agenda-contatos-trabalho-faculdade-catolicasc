CC=gcc
CFLAGS=-ansi -Wall -Wextra -pedantic

all: agenda_contatos

agenda_contatos: agenda_contatos.c
	$(CC) $(CFLAGS) agenda_contatos.c -o agenda_contatos

clean:
	rm -f agenda_contatos contatos.txt
