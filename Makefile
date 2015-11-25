CXX=g++ -std=c++11
CXXFLAGS=-Wall

all: baby

baby: baby.o main.o
	$(CXX) -o baby baby.o main.o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

baby.o: baby.hpp

run: baby
	./baby 

clean:
	rm -f baby.o main.o
	rm -f baby
