#!/usr/bin/make -f

name := "$(shell pwd | sed -r "s/.*\/([a-zA-Z0-9_-]*)/\1/")"

bin:
	mkdir -p bin
	g++ -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -msse2 -mfpmath=sse -o bin/${name} src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf bin
.PHONY:	bin	clean