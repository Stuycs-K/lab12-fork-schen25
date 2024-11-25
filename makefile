.PHONY: compile run clean
compile: main.o
	@gcc -o program main.o
run: program
	@./program
main.o: main.c
	@gcc -c main.c
clean:
	rm *.o
	rm program
