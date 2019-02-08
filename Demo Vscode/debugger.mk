# Makefile

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:/SDL2-2.0.8/include\

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:/SDL2-2.0.8/lib/x64\

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lstdc++

COMPILER_FLAGS = -w -Wl, -subsystem,windows

output: main.o game.o
	g++ main.o game.o $(LINKER_FLAGS) -o output

main.o: main.cpp
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c main.cpp

game.o: game.cpp game.h 
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c game.cpp

clean:
	@echo "clean Project"
	rm *.o
	@echo "clean finished"