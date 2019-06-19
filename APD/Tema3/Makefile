build: homework
homework: homework.c
	mpicc -o homework homework.c -lm -Wall
serial: homework
	mpirun -np 1 homework imagini.in
distrib: homework
	mpirun -np 4 homework imagini.in
test: homework_debug.c
	gcc -Wall -g homework_debug.c -lm -o test
clean:
	rm -f homework test debug a.out
