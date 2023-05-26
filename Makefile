# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: ferate magazin supercomputer teleportare

run-p1:
	./supercomputer
run-p2:
	./ferate
run-p3:
	./teleportare
run-p4:
	./magazin


# Nu uitați să modificați numele surselor și, eventual, ale executabilelor.
supercomputer: skel/supercomputer/supercomputer.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
ferate: skel/ferate/ferate.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
teleportare: skel/teleportare/teleportare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
magazin: skel/magazin/magazin.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f supercomputer ferate teleportare magazin *.out
