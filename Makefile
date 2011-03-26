LIB = -fpic -c
SO = -shared
SO_FILES = lib/calcNewton.c lib/calcAreas.c
SO_FILES_O = calcNewton.o calcAreas.o
LD_LIBS += -L.

all:  main

libcalc.so: $(SO_FILES)
	gcc -fpic -c $(SO_FILES)
	gcc -shared -o libcalc.so $(SO_FILES_O)

main: main.o libcalc.so
	gcc -o main main.o  -lcalc -ldl

main.o: main.c
	gcc -o main.o -c main.c

install:
	cp *.so /usr/local/lib

clean:
	rm *.o *.so

