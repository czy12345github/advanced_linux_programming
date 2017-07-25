objectsA = processA.o
objectsB = processB.o

all : processA processB

processA : $(objectsA)
	gcc -o processA $(objectsA)

processB : $(objectsB)
	gcc -o processB $(objectsB)

processA.o : shared_memory.h
processB.o : shared_memory.h

clean :
	rm processA $(objectsA) processB $(objectsB)
