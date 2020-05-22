all: gitint-shell

gitint-shell: gitint-shell.cpp gitint.o
	g++ -g -Wall  --std=c++11 gitint-shell.cpp gitint.o -o gitint-shell
	

gitint.o: gitint.cpp
	g++ -g -Wall  --std=c++11 -c gitint.cpp -o gitint.o

clean:
	rm -rf gitint-shell *.o *~