CC=gcc
CFLAGS+=-Wall -Wextra
LIBS+=-lX11 -lXrandr

OBJECTS=xwhite.o

all: xwhite

.o:
	$(CC) -c $(CFLAGS) -o $@ $<

xwhite: $(OBJECTS)
	$(CC) -o xwhite $(OBJECTS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) xwhite

.PHONY: install
install:
	install -m 0755 -T ./xwhite /usr/bin/xwhite 
