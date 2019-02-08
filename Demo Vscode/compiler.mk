# Makefile

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I"C:\SDL2-2.0.3\x86_64-w64-mingw32\include\SDL2"\
-I"C:\Program Files\Haskell Platform\8.4.3\lib\include"\
-I/iconv\
-I/HSrts\
-I/HSbase-4.11.1.0.o\
-I/HSghc-prim-0.3.0.0\
-I/HSinteger-gmp-0.5.0.0\
-I/HSghc-prim-0.3.0.0\
-Wall\

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L"C:\SDL2-2.0.3\x86_64-w64-mingw32\lib"\
-L"C:\Program Files\Haskell Platform\8.4.3\lib\ghc-8.4.3"\
-L"C:\Program Files\Haskell Platform\8.4.3\lib\base-4.11.1.0"\
-L"C:\Program Files\Haskell Platform\8.4.3\lib\ghc-prim-0.5.2.0"\
-L"C:\Program Files\Haskell Platform\8.4.3\lib\integer-gmp-1.0.2.0"\


LINKER_FLAGS = -lSDL2main -lSDL2 -lstdc++

COMPILER_FLAGS = -w -Wl, -subsystem,windows

output: move.o circle.o game.o main.o
	ghc main.o game.o circle.o Haskell/move.o $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS)

main.o: main.cpp 
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c main.cpp

game.o: Game.cpp Game.h
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c game.cpp 

circle.o: objects/Circle.cpp objects/Circle.h
	g++ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c objects/Circle.cpp

move.o: Haskell/Move.hs;
	ghc -no-hs-main $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -fforce-recomp Haskell/Move.hs -c

.PHONY: clean
clean: ; del *.o *.hi *_stub.h *.exe