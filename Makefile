CC = g++
CFLAGS = -std=c++17 -g -Wall
TARGET = panel_garch

main: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.out
	./main.out

clean:
	rm -r *.out *.out.dSYM*

%: %.cpp
	$(CC) $(CFLAGS) $*.cpp -o $*.out
	./$*.out

.PHONY: main % clean
