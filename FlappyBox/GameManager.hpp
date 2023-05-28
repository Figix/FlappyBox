#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace BoxGame {
	class GameManager {
	public:
		int GameState;
		// 0:���� ��ŸƮ, 1:�� ����, 2:���� ����
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
			std::cout << score << "���Դϴ�." << std::endl;
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