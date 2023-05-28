#pragma once
#include <GLFW/glfw3.h>

namespace BoxGame {
	class Player {
	private:
		float spd;
		float tmp;

	public:
		float x, y, size;

		Player() {
			size = 0.1f;
			x = -0.75f;
			y = 0.0f;
			spd = 0.15f;
			tmp = 0.0f;
		}
		~Player() {

		}

		void Draw() {
			glColor4f(1, 1, 1, 1);
			glBegin(GL_QUADS);
			glVertex2f(x - (size / 2), y - (size / 2));
			glVertex2f(x - (size / 2), y + (size / 2));
			glVertex2f(x + (size / 2), y + (size / 2));
			glVertex2f(x + (size / 2), y - (size / 2));
			glEnd();
		}

		void Move() {
			if (y > 1.0f || y < -1.0f) {
				spd = spd * -1.0f;
			}
			y = y + spd;
			if (spd == 0) { spd = tmp; }
		}

		void Stop() {
			tmp = spd;
			spd = 0.0f;
		}

		void Setpos() {
			x = -0.75f;
			y = 0.0f;
		}
	};
}