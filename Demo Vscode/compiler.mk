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

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lstdc++ -optl-mwindows -optl-Wl,-allow-multiple-definition

COMPILER_FLAGS = -w

output: move.o rectangleObj.o circle.o game.o main.o
	ghc -g -no-hs-main main.o game.o rectangleObj.o circle.o Haskell/move.o $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o HaskellDemo

main.o: main.cpp 
	g++ $(INCLUDE_PATHS) -c main.cpp

game.o: Game.cpp Game.h
	g++ $(INCLUDE_PATHS) -c game.cpp 

circle.o: objects/Circle.cpp objects/Circle.h
	g++ $(INCLUDE_PATHS) -c objects/Circle.cpp

rectangleObj.o: objects/RectangleObj.cpp objects/RectangleObj.h
	g++ $(INCLUDE_PATHS) -c objects/RectangleObj.cpp

move.o: Haskell/Move.hs;
	ghc $(INCLUDE_PATHS) -fforce-recomp Haskell/Move.hs -c

.PHONY: clean
clean: ; del *.o *.hi *_stub.h *.exe