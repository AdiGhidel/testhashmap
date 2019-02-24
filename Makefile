all: Hash.o
	g++ Hash.cpp -o hashmap
run: 
	./hashmap
clean: 
	rm *.o

.PHONY: all run