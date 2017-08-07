#!/usr/bin/make -f

name := "$(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")"

bin:
	mkdir -p bin
	g++ -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -DSFML_STATIC -msse2 -mfpmath=sse -o bin/${name} src/*.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
clang:
	mkdir -p bin
	clang++ -std=c++14 -O2 -Wall -Wextra -Wpedantic -I. -DSFML_STATIC -msse2 -mfpmath=sse -o bin/${name} src/*.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
clean:
	rm -rf bin
.PHONY:	bin	clang	clean