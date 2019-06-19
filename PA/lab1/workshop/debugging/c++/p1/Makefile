CC=g++
CXXFLAGS=-Wall -g -std=c++11
EXE=permutations

all: $(EXE)

$(EXE): $(EXE).cpp
	$(CC) $(CXXFLAGS) -o $@ $^

run: $(EXE)
	./$(EXE)

clean:
	rm $(EXE)
