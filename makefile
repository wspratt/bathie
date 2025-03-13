CC=gcc
objects = gas_prop.o gas_eq.o

gas_prop: $(objects)
	$(CC) -o gas_prop $(objects) -I. -lm

gas_prop.o: gas_prop.c gas_eq.h
	$(CC) -c gas_prop.c -I. -lm

gas_eq.o: gas_eq.h
	$(CC) -c gas_eq.c -I.

clean:
	rm gas_prop $(objects)
