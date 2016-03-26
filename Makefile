FLAGS=-Wall -Werror -Wextra -pedantic
DIR=/home/caleb/data/development/c/interactive/

Program.out: main.c libstateful.so
	gcc -o $@ main.c ${FLAGS} -std=c99 -ldl -L${DIR} -Wl,-rpath=${DIR}

libstateful.so: lib.c
	gcc -c lib.c ${FLAGS} -fpic -std=c99
	gcc -shared -o $@ lib.o -std=c99
	pkill Program.out --signal SIGUSR1 || true
