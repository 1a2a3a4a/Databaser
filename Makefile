CC = gcc 
FLAGS = -Wall -ggdb -std=c99

db: db.o dbmod.o 
	$(CC) $(FLAGS) $^ -o  $@

%.o: %.c %.h
	$(CC) $(FLAGS) -c $<

db.o: db.c dbmod.h
	$(CC) $(FLAGS) -c  db.c 
.PHONY: run
run: db SWE.db 
	./db SWE.db
mem: db SWE.db
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all  ./db SWE.db

clean: 
	rm -f *o d
