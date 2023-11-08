CC = g++
CFLAGS = -IcPubcrypt/includes
LDFLAGS = -lgmp
SOURCES = main.cpp $(wildcard cPubcrypt/algorithm/*.c) $(wildcard cPubcrypt/cryptosystem/*.cpp)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)