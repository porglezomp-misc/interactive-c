FLAGS=-Wall -Werror -Wextra -pedantic
DIR=/home/caleb/data/development/c/interactive/

Program.out: main.c libstateful.so
	gcc -o $@ main.c -lstateful -L${DIR} ${FLAGS} -std=c99 -Wl,-rpath=${DIR}

libstateful.so: lib.c
	gcc -c lib.c ${FLAGS} -fpic -std=c99
	gcc -shared -o $@ lib.o -std=c99
