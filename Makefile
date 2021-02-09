all: pruebaGrafo pruebaBFS

pruebaGrafo: pruebaGrafo.c Grafo.o arbolBinarioGrafo.o Cola.o
	gcc -g -Wall -I ./ -o pruebaGrafo pruebaGrafo.c Grafo.o arbolBinarioGrafo.o Cola.o

pruebaBFS: pruebaBFS.c Grafo.o arbolBinarioGrafo.o Cola.o
	gcc -g -Wall -I ./ -o pruebaBFS pruebaBFS.c Grafo.o arbolBinarioGrafo.o Cola.o

arbolBinarioGrafo.o: arbolBinarioGrafo.c
	gcc -g -Wall -I ./ -c arbolBinarioGrafo.c
	
Grafo.o: Grafo.c
	gcc -g -Wall -I ./ -c Grafo.c
	
Cola.o: Cola.c
	gcc -g -Wall -I ./ -c Cola.c
	
clean:
	rm *.o pruebaGrafo pruebaBFS
