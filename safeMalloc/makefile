CC=gcc
SCAN_BUILD_DIR = scan-build-out
EXE=output

all: main.o 537malloc.o tree.o
	$(CC) -g -O0 -o $(EXE) main.o 537malloc.o tree.o

main.o: main.c
	$(CC) -g -O0 -c -Wall -Wextra main.c

obj: 537malloc.o tree.o

537malloc.o: 537malloc.c 537malloc.h tree.h
	$(CC) -g -O0 -c -Wall -Wextra 537malloc.c

tree.o: tree.c tree.h
	$(CC) -g -O0 -c -Wall -Wextra tree.c

clean:
	-rm *.o $(EXE)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
