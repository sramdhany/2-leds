# Sarah Ramdhany
# makefile
# ver 9
all: input.c MyLib.c
        gcc -c MyLib.c
        gcc -o input input.c MyLib.o -l bcm2835