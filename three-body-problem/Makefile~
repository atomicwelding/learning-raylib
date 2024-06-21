CC = clang
CFLAGS = -I/opt/homebrew/include/
LDFLAGS = -L/opt/homebrew/lib/ -lraylib

# Target for compiling the main.c file
raylib: main.o
	$(CC) -std=c2x -o raylib main.o $(LDFLAGS)

# Rule for compiling main.c into main.o
main.o: main.c
	$(CC) -std=c2x -c main.c $(CFLAGS)

# Clean up object files and the executable
clean:
	rm -f main.o
