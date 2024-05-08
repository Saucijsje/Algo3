CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = standaard.o veld.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Boeket

clean:
	rm -f *.o Boeket

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

veld.o: veld.cc veld.h standaard.h constantes.h
	$(CC) $(CompileParms)  veld.cc

main.o: main.cc veld.h standaard.h constantes.h
	$(CC) $(CompileParms)  main.cc

