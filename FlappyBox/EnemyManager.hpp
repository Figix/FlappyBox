#pragma once
#include "Enemy.hpp"
#include <cstdlib>

namespace BoxGame {
	class EnemyManager {
	private:
		const float stool = 0.25f;
	public:
		Enemy* E = new Enemy[3];

		EnemyManager() {
		}
		~EnemyManager() {

		}

		void allDraw() {
			for (int i = 0; i < 3; i++) {
				E[i].Draw();
			}
		}
		void allMove() {
			for (int i = 0; i < 3; i++) {
				E[i].Move();
			}
		}

		void shuffle() {
			for (int i = 0; i < 3; i++) {	//X값 오른쪽 끝으로 몰기
				E[i].x = 1.f + E[i].size;
			}
			switch (rand() % 4)				//y값 랜덤으로 만들기 4개 패턴
			{
			case 0:
				//E[?].y = -1 +stool + (E[0].size*0);
				E[0].y = -1 + stool + (E[0].size * 1);
				E[1].y = -1 + stool + (E[0].size * 2);
				E[2].y = -1 + stool + (E[0].size * 3);
				break;
			case 1:
				E[0].y = -1 + stool + (E[0].size * 0);
				//E[?].y = -1 + stool + (E[0].size * 1);
				E[1].y = -1 + stool + (E[0].size * 2);
				E[2].y = -1 + stool + (E[0].size * 3);
				break;
			case 2:
				E[0].y = -1 + stool + (E[0].size * 0);
				E[1].y = -1 + stool + (E[0].size * 1);
				//E[1].y = -1 + stool + (E[0].size * 2);
				E[2].y = -1 + stool + (E[0].size * 3);
				break;
			case 3:
				E[0].y = -1 + stool + (E[0].size * 0);
				E[1].y = -1 + stool + (E[0].size * 1);
				E[2].y = -1 + stool + (E[0].size * 2);
				//E[2].y = -1 + stool + (E[0].size * 3);
				break;

			default:
				break;
			}
		}

		bool outCheck() {
			if (E[0].x < -1) {
				shuffle();
				return true;
			}
			return false;
		}
	};
}