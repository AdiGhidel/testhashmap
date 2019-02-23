all: 
	g++ hash.cpp -o hashmap -Wall
run: hashmap
	./hashmap
clean: 
	rm *.o

.PHONY: all run