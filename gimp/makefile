bin/output : src/bitmap.c
	g++ -std=c++11 `pkg-config --cflags glib-2.0` -o bin/output src/bitmap.c -lpthread

clean :
	rm bin/*
