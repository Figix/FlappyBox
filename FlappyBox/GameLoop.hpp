#pragma once
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "EnemyManager.hpp"
#include "GameManager.hpp"
#include "Player.hpp"
#include "Texturemapping.hpp"

#define VK_S 0x53
#define VK_A 0x41

using namespace std;

static bool pressS;
static bool pressSpace;

namespace BoxGame
{
	class GameLoop {

	private:
		EnemyManager* EM = new EnemyManager();
		GameManager* GM = new GameManager();
		Player* PL = new Player();
		bool _isGameRunning;

	public:
		GameLoop() {}
		~GameLoop() {}
		//input과 이벤트를 관리하기 위한 callback함수들
		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{

			//GLFW_PRESS(do), GLFW_REPEAT(ing), GLFW_RELEASE(end), GLFW_KEY_UNKNOWN(none)
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
			if (key == GLFW_KEY_S && action == GLFW_PRESS) { pressS = true; }
			else { pressS = false; }
			if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) { pressSpace = true; }
			else { pressSpace = false; }
		}
		void Run()
		{
			GLFWwindow* window;
			glfwSetErrorCallback(error_callback);
			if (!glfwInit())
			{
				std::exit(EXIT_FAILURE);
			}
			window = glfwCreateWindow(512, 512, "Flappy Box", NULL, NULL);

			Initialize(window);
			while (!glfwWindowShouldClose(window))
			{
				Update(window);
				Render(window);

			}
			Release(window);
		}

		void Initialize(GLFWwindow* window) {
			if (!window)
			{
				glfwTerminate();
				std::exit(EXIT_FAILURE);
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glfwMakeContextCurrent(window);
			//그래픽 관련 데이터들을 디바이스(그래픽에서는 출력 장치)를 매핑(연결해주는)것
			//지정한 윈도우 창 기준으로 그리기 위한 메소드
			glfwSetKeyCallback(window, key_callback);
			//key입력 이벤트 받는 메소드
			init_texture_GameStart();
			init_texture_GameOver();
			GM->GameState = GM->GameStart;
		}
		void Update(GLFWwindow* window) {
			//게임 스테이트 관리
			if (GM->GameState == GM->GameStart) {
				if (pressSpace) { GM->Zeroscore();  EM->shuffle(); PL->Setpos(); GM->GameState = GM->inGame; }
			} else if (GM->GameState == GM->GameOver) {
				if (pressSpace) { GM->Zeroscore();  EM->shuffle(); PL->Setpos(); GM->GameState = GM->inGame; }
			}
			if (GM->GameState == GM->inGame) {		//인게임!
				if (pressS) { PL->Stop(); }
				PL->Move();
				EM->allMove();
				if (EM->outCheck()) { 
					GM->Upscore();
				}
				if (isCollision()) { GM->showScore(); GM->GameState = GM->GameOver; }
			}
		}
		void Render(GLFWwindow* window) {
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;


			glClearColor(0.15, 0.15, 0.15, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			if (GM->GameState == GM->GameStart) {		//게임시작!
				DrawGameStart();
			}
			else if (GM->GameState == GM->inGame) {		//인게임!
				PL->Draw();
				EM->allDraw();
			}
			else if (GM->GameState == GM->GameOver) {	//게임오버!
				DrawGameOver();
			}

			glfwSwapBuffers(window);
			//렌더링이 오래걸릴 경우 다 못칠하니 미리 칠해두고 그것을 현재있는것과 바꿈
			glfwPollEvents();
			//이벤트에서 중복된 이벤트들을 정리해서 전달해주는 것
			//함수가 실행되는 순간마다 전달받는다.

			glFlush();
			glDisable(GL_TEXTURE_2D);
			glFinish();



			this_thread::sleep_for(chrono::milliseconds(5));
			//출력 후 0.02초동안 여유 시간을 가지고 다시 게임루프돌음
		}
		void Release(GLFWwindow* window) {
			glfwDestroyWindow(window);
			glfwTerminate();
			std::exit(EXIT_SUCCESS);
		}

		bool isCollision() {
			for (int i = 0; i < 3; i++) {
				if (fabs(PL->x - EM->E[i].x) < (PL->size / 2) + (EM->E[i].size / 16)) {
					if (fabs(PL->y - EM->E[i].y) < (PL->size / 2) + (EM->E[i].size / 2)) {
						return true;
					}
				}
			}
			return false;
		}
		void DrawGameStart() {
			glColor4f(0.25, 0.25, 0.25, 1);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, textGameStart);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}
		void DrawGameOver() {
			glColor4f(0.5, 0.5, 0.5, 1);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, textGameOver);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0);
			glEnd();
		}
	};
}