.phony : build run clean dynarray chained skiplist

dynarray:
	gcc dynarray.c -o main

chained:
	gcc chained.c -o main

skiplist:
	gcc skiplist.c -o main

run:
	./main

clean:
	rm main