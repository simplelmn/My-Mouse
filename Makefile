CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = src/my_mouse.c src/my_math.c src/my_queue.c src/my_string.c main.c
TARGET = my_mouse

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -rf $(TARGET)