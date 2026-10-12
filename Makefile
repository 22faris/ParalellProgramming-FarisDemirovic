CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = main
SOURCE = main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) 5

clean:
	rm -f $(TARGET)

.PHONY: all valgrind clean
