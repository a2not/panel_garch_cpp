CC = g++
CFLAGS = -std=c++17 -g -Wall -I ../eigen
TARGET = panel_garch

clean:
	rm -r *.out *.out.dSYM*

%: %.cpp
	$(CC) $(CFLAGS) $*.cpp -o $*.out
	./$*.out

.PHONY: % clean
