LIB = -fpic -c
SO = -shared
SO_FILES = lib/calcNewton.c lib/calcAreas.c
SO_FILES_O = calcNewton.o calcAreas.o
LD_LIBS += -L.

all:  main

liblogconsole.so: lib/logconsole.c lib/logfile.c
	gcc -fpic -c lib/logconsole.c lib/logfile.c
	gcc -shared -o liblogconsole.so logconsole.o logfile.o

libcalc.so: $(SO_FILES)
	gcc -fpic -c $(SO_FILES)
	gcc -shared -o libcalc.so $(SO_FILES_O)

main: main.o libcalc.so liblogconsole.so
	gcc -o main main.o -ldl

main.o: main.c
	gcc -o main.o -c main.c

install:
	cp *.so /usr/local/lib

uninstall:
	rm /usr/local/lib/liblogconsole.so /usr/local/lib/libcalc.so

clean:
	rm *.o *.so

