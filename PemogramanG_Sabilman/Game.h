#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <GL/freeglut.h>


using namespace std;

enum class State { RUNNING, EXIT };
enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS};

namespace Engine {
	class Game
	{
	public:
		Game();
		~Game();
		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		int getWinWidth();
		void setWinWidth(int width);
		int getWinHeight();
		void setWinHeight(int height);
	protected:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		virtual void movePemainX(float a) = 0;
		virtual void movePemainY(float a) = 0;
		virtual void moveEnemy() = 0;
		virtual void BGM() = 0;
		virtual void stopBGM() = 0;
		virtual bool getRepeat() = 0;
		virtual bool cekLives() = 0;
		virtual void Reset() = 0;
		virtual int getScore() = 0;
		virtual int getHighscore() = 0;
		virtual int getMoney() = 0;
		virtual int getCurrentLevel() = 0;
		virtual int getLives() = 0;

	private:
		unsigned int screenWidth, screenHeight, lastFrame = 0, last = 0, _fps = 0, fps = 0;
		float winWidth, winHeight;
		float targetFrameTime = 0, timeScale;
		State state;
		float GetDeltaTime();
		void GetFPS();
		void PollInput();
		void stop();
		void Err(string errorString);
		void LimitFPS();
		void reshape(GLsizei width, GLsizei height);
		void newInit();
		void newUpdate(); //buat init, update render yg baru di game.cpp
	};
}

