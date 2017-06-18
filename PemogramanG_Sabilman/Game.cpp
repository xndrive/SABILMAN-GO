#include "Game.h"

Engine::Game::Game()
{
}


Engine::Game::~Game()
{
}

void Engine::Game::Start(string windowTitle, unsigned int screenWidth, unsigned int screenHeight, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale)
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->timeScale = timeScale;

	if (targetFrameRate > 0) {
		targetFrameTime = 1000.0f / targetFrameRate;
	}


	Uint32 flags = SDL_WINDOW_OPENGL;

	if (WindowFlag::EXCLUSIVE_FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WindowFlag::FULLSCREEN == windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (WindowFlag::BORDERLESS == windowFlag) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Setup SDL Window
	SDL_Window* window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (window == nullptr) {
		Err("Failed to create SDL window!");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		Err("Failed to create SDL_GL context!");
	}

	//Set up glew (optional but recommended)
	GLenum glewStat = glewInit();
	if (glewStat != GLEW_OK) {
		Err("Failed to initialize glew!");
	}

	//Set VSYNC
	SDL_GL_SetSwapInterval(vsync);

	this->state = State::RUNNING;

	// Init delta time calculation
	last = SDL_GetTicks();

	Init();

	//Will loop until we set _gameState to EXIT
	while (State::RUNNING == state) {
		float deltaTime = GetDeltaTime();
		
		GetFPS();
		reshape(this->screenWidth, this->screenHeight);
		PollInput();
		Update(deltaTime);
		Render();
		//manipulasi posisi
		moveEnemy();
		if (cekLives()) {
			
			if (getRepeat() != true) {
				state = State::EXIT;
			}
			else
			{
				
				Reset();
			}
		}

		SDL_GL_SwapWindow(window);
		LimitFPS();

		//print only once every 60 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 60) {
			std::cout << "FPS: " << fps << std::endl;
			cout << "Level: : " << getCurrentLevel() << endl;
			cout <<"Score: "<<getScore() << endl;
			cout << "HighScore: " << getHighscore() << endl;
			cout << "Money: " << getMoney() << endl;
			cout << "Lives: " << getLives() << endl;
			cout <<"======================" <<endl<<endl ;
			frameCounter = 0;
		}
	}

}


float Engine::Game::GetDeltaTime()
{
	unsigned int time = SDL_GetTicks();
	unsigned int delta = time - lastFrame;
	lastFrame = time;

	return delta * timeScale;
}

void Engine::Game::GetFPS()
{
	if (SDL_GetTicks() - last > 1000) {
		fps = _fps;
		_fps = 0;
		last += 1000;
	}
	_fps++;
}

void Engine::Game::PollInput()
{
	SDL_Event evt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = State::EXIT;
			break;
		case SDL_KEYDOWN:
			if (evt.key.keysym.sym == SDLK_a) {
				movePemainX(-0.02f);
				break;
			}
			else if (evt.key.keysym.sym == SDLK_d) {
				movePemainX(0.02f);
				break;
			}
			else if (evt.key.keysym.sym == SDLK_w) {
				movePemainY(0.02f);
				break;
			}
			else if (evt.key.keysym.sym == SDLK_s) {
				movePemainY(-0.02f);
				break;
			}
			else if (evt.key.keysym.sym == SDLK_m) {
				stopBGM();
				break;
			}
			else if (evt.key.keysym.sym == SDLK_n) {
				BGM();
				break;
			}
		}

	}
//	cout << posX << endl;
}

//Prints out an error message and exits the game
void Engine::Game::Err(string errorString)
{
	std::cout << errorString << std::endl;
	SDL_Quit();
	exit(1);
}

void Engine::Game::LimitFPS()
{
	//Limit the FPS to the max FPS
	SDL_Delay((Uint32)(targetFrameTime));

}

void Engine::Game::setWinWidth(int width) {
	Game::winWidth = width;
}

void Engine::Game::reshape(GLsizei width, GLsizei height) {
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(-1.5 * aspect, 1.5 * aspect, -1.5, 1.5);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(-1.5, 1.5, -1.5 / aspect, 1.5 / aspect);
	}
	glMatrixMode(GL_MODELVIEW);
}

void Engine::Game::newInit() {

}

void Engine::Game::newUpdate() {

}
void Engine::Game::stop() {
	SDL_Quit();
}

