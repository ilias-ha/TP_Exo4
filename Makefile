CC = gcc
CFLAGS = -O3 -g
LDFLAGS = -L.
LIBS = -lppm

TARGET = test mandel

all: $(TARGET)

libppm.so: ppm.c
	$(CC) $(CFLAGS) -fpic -shared $^ -o $@

test: main.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) main.c $(LIBS) -lm -o $@

mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LIBS) -lm -o $@

clean:
	rm -f $(TARGET) *.so
