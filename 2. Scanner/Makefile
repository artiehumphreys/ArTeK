CC = g++
FLEX = flex
CPPFLAGS = -std=c++11 -Wall
FLEXFLAGS = --c++ --yyclass=Scanner

all:	scanner

scanner.cpp: scanner.flex
	$(FLEX) $(FLEXFLAGS) -o $@ $^

scanner: driver.cpp scanner.cpp
	$(CC) $(CPPFLAGS) -o $@ $^
