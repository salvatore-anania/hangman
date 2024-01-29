CC=gcc
CFLAGS=-Wall -Werror -Wextra
EXECUTABLE=hangman

all: $(EXECUTABLE)

$(EXECUTABLE): main.o hangman.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

hangman.o: hangman.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE).exe

.PHONY: all clean fclean run