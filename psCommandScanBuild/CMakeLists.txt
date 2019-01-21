cmake_minimum_required(VERSION 3.12)
project(Operating_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(Operating_System
        README.md main.c
        processUtility.c
        dirRead.c
        parseCommand.c
        processCommandLine.c
        processState.c
        processSystime.c
        processUtime.c
        processVirtualMemory.c
        processDisplay.c
        ps537Handler.c)


