CC = gcc
CFLAGS = -Isrc/includes
LDFLAGS = -lgmp
SOURCES = main.c $(wildcard src/arithmetic/*.c) $(wildcard src/pubcrypt/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = rsa.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)