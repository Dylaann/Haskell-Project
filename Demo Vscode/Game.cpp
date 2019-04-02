#include "Game.h"

// Game constrcutor
Game::Game() {
	srand(NULL);
	//Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create Console Window, Sdl Window & Renderer
	AllocConsole();
	AttachConsole( GetCurrentProcessId() ) ;
	freopen( "CON", "w", stdout ) ;

	m_window = SDL_CreateWindow("Haskell, C++ Inter-Op", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	m_image = IMG_Load("ASSETS//IMAGES//Circle.png");
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_image);
	SDL_FreeSurface(m_image);

	// Create Objects
	for (int i = 0; i < 4; i++) {
		Circle* temp = new Circle(i, (i + 1) * 200.0f, 100.0f, false, 30, red, m_texture);
		int tempX = rand() % 7 - 3;
		int tempY = rand() % 7 - 3;
		temp->setVel(std::make_pair<float, float>(tempX, tempY));
		objs.push_back(temp);
	}

	m_ground = new RectangleObj(-10000, 700, 2280, 1200, true, blue);
	m_left = new RectangleObj(-14500, -100, 1500, 2000, true, blue);
	m_right = new RectangleObj(12300, -100, 1500, 2000, true, blue);
	m_spawn = new RectangleObj(70, 70, 60, 60, false, green);
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

	current_time = SDL_GetTicks();

	while (!m_exitGame) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime += (current_time - old_time);

		update();

		std::cout << "Update Time: " << ftime << std::endl;
		ftime = 0;

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
				Circle* temp1 = new Circle(objs.size(), 100.0f, 100.0f, false, 30, red, m_texture);
				int tempX = rand() % 7 - 3;
				int tempY = rand() % 7 - 3;
				while ((tempX < 1 && tempX > -1) && (tempY < 1 && tempY > -1))
				{
					tempX = rand() % 7 - 3;
					tempY = rand() % 7 - 3;
					std::cout << "X: " << tempX << ", Y: " << tempY << std::endl;
				}
				temp1->setVel(std::make_pair<float, float>(tempX, tempY));
				std::cout << "X: " << tempX << ", Y: " << tempY << std::endl;
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
	int operations = 0;

	for(int i = 0; i < (int)objs.size(); i++) {
		bool collided = false;
		//objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, moveGravity(objs[i]->getVel().second)));
		operations++;

		for (int j = 0; j < (int)objs.size(); j++) {
			if (j != i && j < i) {
				if(circleCircleCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), objs[j]->getPosX(), objs[j]->getPosY(), objs[j]->getRadius())) {

					float x1 = objs[i]->getPos().first;
					float y1 = objs[i]->getPos().second;
					float vx1 = objs[i]->getVel().first;
					float vy1 = objs[i]->getVel().second;
					float m1 = objs[i]->getMass();
					float r1 = objs[i]->getRadius();
					float x2 = objs[j]->getPos().first;
					float y2 = objs[j]->getPos().second;
					float vx2 = objs[j]->getVel().first;
					float vy2 = objs[j]->getVel().second;
					float m2 = objs[j]->getMass();
					float r2 = objs[j]->getRadius();
					

					objs[i]->setPos(std::make_pair<float, float>(applyForce(x1, circlePushBackX(x1, r1, x2, r2)), applyForce(y1, circlePushBackY(y1, r1, y2, r2))));
					//objs[j]->setPos(std::make_pair<float, float>(applyForce(x2, circlePushBackX(x2, r2, x1, r1)), applyForce(y2, circlePushBackX(y2, r2, y1, r1))));

					x1 = objs[i]->getPos().first;
					y1 = objs[i]->getPos().second;
					x2 = objs[j]->getPos().first;
					y2 = objs[j]->getPos().second;

					objs[i]->setVel(std::make_pair<float, float>(lastHopeX1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					lastHopeY1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					objs[j]->setVel(std::make_pair<float, float>(lastHopeX2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					lastHopeY2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					collided = true;
					operations += 10;
				}
				operations++;
			}
		}

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)) {
			objs[i]->setPosY(applyForce(objs[i]->getPosY(), -pushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(groundRestitution(objs[i]->getVel().first), circleRectResY(objs[i]->getVel().second)));
			collided = true;

			operations += 4;
		}
		operations++;


		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second)) {
			objs[i]->setPosX(applyForce(pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second), -objs[i]->getPosX()));
			objs[i]->setVel(std::make_pair<float, float>(circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;
			
			operations += 4;
		}
		operations++;

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)) {
			objs[i]->setPosX(applyForce(objs[i]->getPosX(), -pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;

			operations += 4;
		}
		operations++;

		objs[i]->setPosX(applyForce(objs[i]->getPosX(), objs[i]->getVel().first));
		operations++;
		objs[i]->setPosY(applyForce(objs[i]->getPosY(), objs[i]->getVel().second));
		operations++;

		if (checkLeftBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(leftBoundRes(objs[i]->getRadius()));
		}
		if (checkRightBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(rightBoundRes(objs[i]->getRadius()));
		}
		if (checkTopBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(topBoundRes(objs[i]->getRadius()));
		}
		if (checkBottomBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(bottomBoundRes(objs[i]->getRadius()));
		}
		operations += 4;

		objs[i]->update();
	}

	//std::cout << "Operations: " << operations << std::endl;
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

	m_spawn->render(m_renderer);
	m_ground->render(m_renderer);
	m_left->render(m_renderer);
	m_right->render(m_renderer);
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
