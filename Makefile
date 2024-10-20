CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99
targets=image_editor

build:$(targets)

image_editor:image_editor.c
	 $(CC) $(CFLAGS) image_editor.c -lm -o image_editor

clean:
	rm -f $(targets)
