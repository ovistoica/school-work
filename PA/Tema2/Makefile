.PHONY: build run clean

CFLAGS = -Wall -std=c++11 -g

build: build_minlexbfs build_disjcnt build_revedges

build_minlexbfs:
	g++ $(CFLAGS) src/minlexbfs.cpp -o minlexbfs

build_disjcnt:
	g++ $(CFLAGS) src/disjcnt.cpp -o disjcnt

build_rtd:
	g++ $(CFLAGS) src/rtd.cpp -o rtd

build_revedges:
	g++ $(CFLAGS) src/revedges.cpp -o revedges


run-p1:
	./minlexbfs

run-p2:
	./disjcnt

run-p4:
	./revedges

clean:
	rm -f minlexbfs disjcnt revedges
