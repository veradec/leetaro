main: main.c helpers.h ante.h
	gcc main.c -lraylib -lm -o output/main

run: main.c helpers.h ante.h
	gcc main.c -lraylib -lm -o output/main
	./output/main



