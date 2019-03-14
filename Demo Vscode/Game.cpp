#include "Game.h"

// Game constrcutor
Game::Game() {
	//Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create Console Window, Sdl Window & Renderer
	AllocConsole();
	AttachConsole( GetCurrentProcessId() ) ;
	freopen( "CON", "w", stdout ) ;

	m_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	// Create Objects
	for (int i = 0; i < 1; i++) {
		Circle* temp = new Circle((i + 1) * 100.0f, 100.0f, true, 30, red);
		objs.push_back(temp);
	}

	m_ground = new RectangleObj(0, 600, 1280, 120, true, blue);
}

// Game deconstructor
Game::~Game(){
}

// Game Loop
void Game::run() {
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime = 0;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime [[maybe_unused]] = 0;

	while (!m_exitGame) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update();
		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

// Event Handling
void Game::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			FreeConsole();
			m_exitGame = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_exitGame = true;
			if (event.key.keysym.sym == SDLK_RIGHT) {
				Circle* temp1 = new Circle(100.0f, 100.0f, true, 30, red);
				objs.push_back(temp1);
			}
			break;
		default:
			break;
		}
	}
}

//Update Loop
void Game::update()
{
	for(int i = 0; i < (int)objs.size(); i++) {
		objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, moveGravity(objs[i]->getVel().second)));
		objs[i]->setPosX(applyForce(objs[i]->getPosX(), objs[i]->getVel().first));
		objs[i]->setPosY(applyForce(objs[i]->getPosY(), objs[i]->getVel().second));

		if (checkLeftBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(leftBoundRes(objs[i]->getRadius()));
		}
		if (checkRightBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(rightBoundRes(objs[i]->getRadius()));
		}

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)) {
			objs[i]->setPosX(applyForce(objs[i]->getPosX(), -pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)));
			objs[i]->setPosY(applyForce(objs[0]->getPosY(), -pushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(circleRectResX(objs[i]->getVel().first), circleRectResY(objs[i]->getVel().second)));
		}

		for (int j = 0; j < (int)objs.size(); j++) {
			if (j != i && j < i) {
				if(circleCircleCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), objs[j]->getPosX(), objs[j]->getPosY(), objs[j]->getRadius())) {
					std::cout << "Collision Laaaad" << std::endl;
					
					//objs[i]->setPos(std::make_pair<float, float>(applyForce(objs[i]->getPos().first, newVelX1(objs[i]->getVel().first, objs[j]->getVel().first)), applyForce(objs[i]->getPos().second, newVelY1(objs[i]->getVel().second, objs[j]->getVel().second))));
					//objs[j]->setPos(std::make_pair<float, float>(applyForce(objs[j]->getPos().first, newVelX2(objs[i]->getVel().first, objs[j]->getVel().first)), applyForce(objs[j]->getPos().second, newVelY2(objs[i]->getVel().second, objs[j]->getVel().second))));
					
					objs[i]->setVel(std::make_pair<float, float>(newVelX1(objs[i]->getPos().first, objs[i]->getPos().second, objs[i]->getVel().first, objs[i]->getVel().second,
					objs[j]->getPos().first, objs[j]->getPos().second, objs[j]->getVel().first, objs[j]->getVel().second),
					newVelY1(objs[i]->getPos().first, objs[i]->getPos().second, objs[i]->getVel().first, objs[i]->getVel().second,
					objs[j]->getPos().first, objs[j]->getPos().second, objs[j]->getVel().first, objs[j]->getVel().second)));

					objs[j]->setVel(std::make_pair<float, float>(newVelX2(objs[i]->getPos().first, objs[i]->getPos().second, objs[i]->getVel().first, objs[i]->getVel().second,
					objs[j]->getPos().first, objs[j]->getPos().second, objs[j]->getVel().first, objs[j]->getVel().second),
					newVelY2(objs[i]->getPos().first, objs[i]->getPos().second, objs[i]->getVel().first, objs[i]->getVel().second,
					objs[j]->getPos().first, objs[j]->getPos().second, objs[j]->getVel().first, objs[j]->getVel().second)));

					std::cout << objs[i]->getVel().second << std::endl;
				}
			}
		}
	}
}

// Render Loop
void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	m_ground->render(m_renderer);
	for (int i = 0; i < static_cast<int>(objs.size()); i++) {
		objs[i]->render(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}

// Function to setup a font
void Game::setUpFont() {

	if (TTF_Init() < 0)
	{
		std::cout << "Error initialising font" << std::endl;
	}
	const char *path = "ASSETS\\FONTS\\arial.ttf";
	Arial = TTF_OpenFont(path, 500);
}
