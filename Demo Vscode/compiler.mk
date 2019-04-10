# Makefile

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I"C:\SDL2-2.0.3\x86_64-w64-mingw32\include\SDL2"\
-I"C:\Program Files\Haskell Platform\8.4.3\lib\include"\
-I"C:\Users\dylmr\Documents\Haskell-Project\Demo Vscode\imgui"\
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

#Linker Flags for SDL2
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lstdc++ -optl-mwindows -optl-Wl,-allow-multiple-definition

#Compiler flags ignore warnings
COMPILER_FLAGS = -w -Wunused-variable -Wuninitialized

#Create executable with object files
output: physics.o rectangleObj.o circle.o nativePhysics.o game.o main.o
	ghc -g -no-hs-main main.o game.o nativePhysics.o rectangleObj.o circle.o Haskell/physics.o $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o HaskellDemo

main.o: main.cpp 
	g++ $(INCLUDE_PATHS) -c main.cpp

game.o: Game.cpp Game.h
	g++ $(INCLUDE_PATHS) -c game.cpp 

nativePhysics.o: NativePhysics/NativePhysics.cpp NativePhysics/NativePhysics.h
	g++ $(INCLUDE_PATHS) -c NativePhysics/NativePhysics.cpp

circle.o: objects/Circle.cpp objects/Circle.h
	g++ $(INCLUDE_PATHS) -c objects/Circle.cpp

rectangleObj.o: objects/RectangleObj.cpp objects/RectangleObj.h
	g++ $(INCLUDE_PATHS) -c objects/RectangleObj.cpp

physics.o: Haskell/Physics.hs;
	ghc $(INCLUDE_PATHS) -fforce-recomp Haskell/Physics.hs -c

#Clean project dir
.PHONY: clean
clean: ; del *.o *.hi *_stub.h *.exe