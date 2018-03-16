
all:
	g++ -O2 -Wall -Wshadow -std=c++11 *cpp *hpp; 
	rm *gch;
