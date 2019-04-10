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

	m_window = SDL_CreateWindow("Haskell, C++ Inter-Op", 0, 0, 1280, 720, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if(profiling) {
		initChecks();
	}

	// Load image for renderering & Create objects
	m_image = IMG_Load("ASSETS//IMAGES//Circle.png");
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_image);
	SDL_FreeSurface(m_image);
	createObjs();

	// Open text file for writing
	if(profiling) {
		myfile.open("TextFiles/profiling2.txt");
	}
}

// Game deconstructor
Game::~Game(){
	if(myfile.is_open()) {
		myfile.close();
	}
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

		if(m_haskell) { 
			haskellUpdate();
		}
		else {
			nativeUpdate();
		}
		printData();
		ftime = 0;

		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));

	}
	
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	exit( GetCurrentProcessId() );
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
			if (event.key.keysym.sym == SDLK_SPACE) {
				// Add new circle
				Circle* temp1 = new Circle(objs.size(), 100.0f, 100.0f, false, 20, red, m_texture);
				int tempX = rand() % 7 - 3;
				int tempY = rand() % 7 - 3;
				while ((tempX < 2 && tempX > -2) && (tempY < 2 && tempY > -2))
				{
					tempX = rand() % 7 - 3;
					tempY = rand() % 7 - 3;
				}
				temp1->setVel(std::make_pair<float, float>(tempX, tempY));
				objs.push_back(temp1);
			}
			break;
		default:
			break;
		}
	}
}

//Update for C++ physics
void Game::nativeUpdate()
{
	operations = 0;

	for(int i = 0; i < (int)objs.size(); i++) {
		collided = false;

		for (int j = 0; j < (int)objs.size(); j++) {
			if (j != i && j < i) {
				if(m_physics.circleCircleCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), objs[j]->getPosX(), objs[j]->getPosY(), objs[j]->getRadius())) {

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
					

					objs[i]->setPos(std::make_pair<float, float>(m_physics.applyForce(x1, m_physics.circlePushBackX(x1, r1, x2, r2)), m_physics.applyForce(y1, m_physics.circlePushBackY(y1, r1, y2, r2))));
					objs[j]->setPos(std::make_pair<float, float>(m_physics.applyForce(x2, m_physics.circlePushBackX(x2, r2, x1, r1)), m_physics.applyForce(y2, m_physics.circlePushBackX(y2, r2, y1, r1))));

					x1 = objs[i]->getPos().first;
					y1 = objs[i]->getPos().second;
					x2 = objs[j]->getPos().first;
					y2 = objs[j]->getPos().second;

					objs[i]->setVel(std::make_pair<float, float>(m_physics.circleVelX1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					m_physics.circleVelY1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					objs[j]->setVel(std::make_pair<float, float>(m_physics.circleVelX2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					m_physics.circleVelY2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					collided = true;
					operations += 12;
				}
				operations++;
			}
		}

		if(m_physics.circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_top->getPos().first, m_top->getPos().second, m_top->getRect().first,  m_top->getRect().second)) {
			objs[i]->setPosY(m_physics.applyForce(objs[i]->getPosY(), m_physics.topPushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_top->getPos().first, m_top->getPos().second, m_top->getRect().first,  m_top->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, m_physics.circleRectResY(objs[i]->getVel().second)));
			collided = true;
			operations += 3;
		}

		operations++;
		if(m_physics.circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)) {
			objs[i]->setPosY(m_physics.applyForce(objs[i]->getPosY(), -m_physics.pushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, m_physics.circleRectResY(objs[i]->getVel().second)));
			collided = true;

			operations += 3;
		}
		operations++;


		if(m_physics.circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second)) {
			objs[i]->setPosX(m_physics.applyForce(m_physics.pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second), objs[i]->getPosX()));
			objs[i]->setVel(std::make_pair<float, float>(m_physics.circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;
			operations += 3;
		}
		operations++;

		if(m_physics.circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)) {
			objs[i]->setPosX(m_physics.applyForce(objs[i]->getPosX(), m_physics.pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(m_physics.circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;
			operations += 3;
		}
		operations++;

		objs[i]->setPosX(m_physics.applyForce(objs[i]->getPosX(), objs[i]->getVel().first));
		operations++;
		objs[i]->setPosY(m_physics.applyForce(objs[i]->getPosY(), objs[i]->getVel().second));
		operations++;

		if (m_physics.checkLeftBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(m_physics.leftBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (m_physics.checkRightBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(m_physics.rightBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (m_physics.checkTopBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(m_physics.topBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (m_physics.checkBottomBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(m_physics.bottomBoundRes(objs[i]->getRadius()));
			operations++;
		}
		operations += 4;

		objs[i]->update();
	}
}


//Update for Haskell physics
void Game::haskellUpdate()
{
	operations = 0;

	for(int i = 0; i < (int)objs.size(); i++) {
		collided = false;

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
					objs[j]->setPos(std::make_pair<float, float>(applyForce(x2, circlePushBackX(x2, r2, x1, r1)), applyForce(y2, circlePushBackX(y2, r2, y1, r1))));

					x1 = objs[i]->getPos().first;
					y1 = objs[i]->getPos().second;
					x2 = objs[j]->getPos().first;
					y2 = objs[j]->getPos().second;

					objs[i]->setVel(std::make_pair<float, float>(circleVelX1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					circleVelY1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					objs[j]->setVel(std::make_pair<float, float>(circleVelX2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2), 
					circleVelY2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2)));

					collided = true;
					operations += 12;
				}
				operations++;
			}
		}

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_top->getPos().first, m_top->getPos().second, m_top->getRect().first,  m_top->getRect().second)) {
			objs[i]->setPosY(applyForce(objs[i]->getPosY(), topPushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_top->getPos().first, m_top->getPos().second, m_top->getRect().first,  m_top->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, circleRectResY(objs[i]->getVel().second)));
			collided = true;
			operations += 3;
		}
		operations++;

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)) {
			objs[i]->setPosY(applyForce(objs[i]->getPosY(), -pushBackPosY(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_ground->getPos().first, m_ground->getPos().second, m_ground->getRect().first,  m_ground->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(objs[i]->getVel().first, circleRectResY(objs[i]->getVel().second)));
			collided = true;

			operations += 3;
		}
		operations++;


		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second)) {
			objs[i]->setPosX(applyForce(pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_left->getPos().first, m_left->getPos().second, m_left->getRect().first,  m_left->getRect().second), -objs[i]->getPosX()));
			objs[i]->setVel(std::make_pair<float, float>(circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;
			
			operations += 3;
		}
		operations++;

		if(circleRectCollision(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)) {
			objs[i]->setPosX(applyForce(objs[i]->getPosX(), -pushBackPosX(objs[i]->getPosX(), objs[i]->getPosY(), objs[i]->getRadius(), m_right->getPos().first, m_right->getPos().second, m_right->getRect().first,  m_right->getRect().second)));
			objs[i]->setVel(std::make_pair<float, float>(circleRectResX(objs[i]->getVel().first), objs[i]->getVel().second));
			collided = true;

			operations += 3;
		}
		operations++;

		objs[i]->setPosX(applyForce(objs[i]->getPosX(), objs[i]->getVel().first));
		operations++;
		objs[i]->setPosY(applyForce(objs[i]->getPosY(), objs[i]->getVel().second));
		operations++;

		if (checkLeftBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(leftBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (checkRightBound(objs[i]->getPosX(), objs[i]->getRadius())) {
			objs[i]->setPosX(rightBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (checkTopBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(topBoundRes(objs[i]->getRadius()));
			operations++;
		}
		if (checkBottomBound(objs[i]->getPosY(), objs[i]->getRadius())) {
			objs[i]->setPosY(bottomBoundRes(objs[i]->getRadius()));
			operations++;
		}
		operations += 4;

		objs[i]->update();
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

	m_spawn->render(m_renderer);
	for (int i = 0; i < static_cast<int>(objs.size()); i++) {
		objs[i]->render(m_renderer);
	}
	m_top->render(m_renderer);
	m_ground->render(m_renderer);
	m_left->render(m_renderer);
	m_right->render(m_renderer);

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

// Get System data for profiling
void Game::initChecks() {
	SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

// Get current Cpu usage as percent
double Game::getCurrentVal() {
	FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
        (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

// Get amount of RAM used by current proccess
double Game::getRam() {
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

	return physMemUsedByMe;
}

void Game::printData() {
	if(profiling) {
		for(int i = 0; i < 1000000; i += 10000) {
			if(operations > i && operations < i + 10000 && !operChecks[i / 10000]) {

				//Print Data to console
				std::cout << "**************" << std::endl;
				double ram = ((getRam() / 1024) /1024);
				double cpu = getCurrentVal();

				std::cout << "Mem in MB: " << ram << std::endl;
				std::cout << "CPU USED: " << cpu << std::endl;
				std::cout << "Amount of Objs: " << objs.size() << std::endl;
				std::cout << "Ticks - " << ftime << std::endl;
				std::cout << "Function calls - " << operations << std::endl;

				// Write Data to a file
				if(myfile.is_open()) {
					myfile  << row << "," 
					<< ram << ","
					<< cpu << ","
					<< objs.size() << ","
					<< ftime << ","
					<< operations << "\n";
				}
				row++;
				std::cout << "**************" << std::endl << std::endl << std::endl;
				operChecks[i / 10000] = true;
			}
			else if (operations > i && operations < i + 10000 && operChecks[i / 10000] == true) {
				// Make new Circle for profiling
				Circle* temp1 = new Circle(objs.size(), 100.0f, 100.0f, false, 20, red, m_texture);
				int tempX = rand() % 7 - 3;
				int tempY = rand() % 7 - 3;
				while ((tempX < 2 && tempX > -2) && (tempY < 2 && tempY > -2))
				{
					tempX = rand() % 7 - 3;
					tempY = rand() % 7 - 3;
				}
				temp1->setVel(std::make_pair<float, float>(tempX, tempY));
				objs.push_back(temp1);
			}
		}
	}
}

void Game::createObjs() {
	// Create Objects
	for (int i = 0; i < 4; i++) {
		Circle* temp = new Circle(i, (i + 1) * 200.0f, 100.0f, false, 20, red, m_texture);
		int tempX = rand() % 7 - 3;
		int tempY = rand() % 7 - 3;
		temp->setVel(std::make_pair<float, float>(tempX, tempY));
		objs.push_back(temp);
	}

	// Create boundaries and spawn position
	m_ground = new RectangleObj(-1000, 670, 2280, 1550, true, blue);
	m_left = new RectangleObj(-1500, 0, 1550, 720, true, blue);
	m_right = new RectangleObj(1230, 0, 1550, 720, true, blue);
	m_top = new RectangleObj(0, -1500, 1280, 1550, true, blue);
	m_spawn = new RectangleObj(70, 70, 60, 60, false, green);
}