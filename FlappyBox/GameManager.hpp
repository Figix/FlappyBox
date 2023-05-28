#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace BoxGame {
	class GameManager {
	public:
		int GameState;
		// 0:게임 스타트, 1:인 게임, 2:게임 오버
		enum GameState {
			GameStart,
			inGame,
			GameOver
		};
		int score;
		GameManager() {
			GameState = GameStart;
			score = 0;
		}
		~GameManager() {

		}

		void Zeroscore() {
			score = 0;
		}

		void Upscore() {
			score += 100;
		}

		void showScore() {
			std::cout << score << "점입니다." << std::endl;
		}

		void GameState_Start() {
			GameState = GameStart;
		}
		void GameState_inGame() {
			GameState = inGame;
		}
		void GameState_Over() {
			GameState = GameOver;
		}
	};
}