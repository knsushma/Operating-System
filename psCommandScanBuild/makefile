CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o processVirtualMemory.o processCommandLine.o processState.o processSystime.o processUtime.o parseCommand.o processUtility.o dirRead.o processDisplay.o ps537Handler.o
	$(CC) -o $(EXE) main.o processCommandLine.o processVirtualMemory.o processState.o processSystime.o processUtime.o parseCommand.o processUtility.o dirRead.o processDisplay.o ps537Handler.o

main.o: main.c processVirtualMemory.h processCommandLine.h processState.h processSystime.h processUtime.h parseCommand.h processUtility.h dirRead.h helper.h processDisplay.h ps537Handler.h
	$(CC) $(WARNING_FLAGS) -c main.c

processDisplay.o: processDisplay.h processDisplay.c
	$(CC) $(WARNING_FLAGS) -c processDisplay.c

ps537Handler.o: ps537Handler.c ps537Handler.h
	$(CC) $(WARNING_FLAGS) -c ps537Handler.c

processCommandLine.o: processCommandLine.c processCommandLine.h
	$(CC) $(WARNING_FLAGS) -c processCommandLine.c

processVirtualMemory.o: processVirtualMemory.h processVirtualMemory.c
	$(CC) $(WARNING_FLAGS) -c processVirtualMemory.c

processState.o: processState.h processState.c
	$(CC) $(WARNING_FLAGS) -c processState.c

processSystime.o: processSystime.h processSystime.c
	$(CC) $(WARNING_FLAGS) -c processSystime.c

processUtime.o: processUtime.h processUtime.c
	$(CC) $(WARNING_FLAGS) -c processUtime.c

parseCommand.o: parseCommand.h parseCommand.c
	$(CC) $(WARNING_FLAGS) -c parseCommand.c

processUtility.o: processUtility.c
	$(CC) $(WARNING_FLAGS) -c processUtility.c

dirRead.o: dirRead.c dirRead.h
	$(CC) $(WARNING_FLAGS) -c dirRead.c

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
