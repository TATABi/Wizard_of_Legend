bin/generate : src/bitmap1_1.c
	g++ -std=c++11 `pkg-config --cflags glib-2.0` -o bin/generate src/bitmap1_1.c -lpthread

clean :
	rm bin/*
