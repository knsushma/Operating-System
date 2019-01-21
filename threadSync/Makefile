CC = gcc
WARNING_FLAGS = -Wall -Wextra
LDFLAGS = -lpthread
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o Queue.o munch1.o munch2.o reader.o writer.o utility.o
	$(CC) -o $(EXE) main.o munch1.o Queue.o munch2.o reader.o writer.o utility.o $(LDFLAGS)

main.o: main.c Queue.h munch1.h munch2.h reader.h writer.h utility.h
	$(CC) $(WARNING_FLAGS) -c main.c

munch1.o: munch1.c munch1.h
	$(CC) $(WARNING_FLAGS) -c munch1.c

Queue.o: Queue.h Queue.c
	$(CC) $(WARNING_FLAGS) -c Queue.c

munch2.o: munch2.h munch2.c
	$(CC) $(WARNING_FLAGS) -c munch2.c

reader.o: reader.h reader.c
	$(CC) $(WARNING_FLAGS) -c reader.c

writer.o: writer.h writer.c
	$(CC) $(WARNING_FLAGS) -c writer.c

utility.o: utility.h utility.c
	$(CC) $(WARNING_FLAGS) -c utility.c

clean:
	rm $(EXE) *.o
#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html