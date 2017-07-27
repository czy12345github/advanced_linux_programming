objectsA = processA.o

all : processA

processA : $(objectsA)
	gcc -o processA $(objectsA)

processA.o : binary_semaphore.h

clean :
	rm $(objectsA) processA
