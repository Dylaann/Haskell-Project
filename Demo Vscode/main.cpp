/*
* @author Dylan Murphy
* @version 1.0
* @date 12/04/2019
*/

#include "Game.h"
#include "Haskell/Physics_stub.h"
#include <HsFFI.h>

using namespace std;

int main(int argc, char* argv[]) {
	hs_init(&argc, &argv);
	Game game;
	game.run();
	hs_exit();

	return 0;
}