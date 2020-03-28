CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack

all: example

example : Jack/jack_module.o filter/lpf.o osc.o main.o
	$(CC) -o $@ $(CFLAGS) jack_module.o lpf.o osc.o main.o $(LDFLAGS) -llo
	

.cpp.o:folders
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
