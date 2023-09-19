CC = gcc
CFLAGS = -Isrc/includes -lgmp
SOURCES = main.c src/arithmetic/*.c src/pubcrypt/*.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = rsa

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)