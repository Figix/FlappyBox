#pragma once
#include <GLFW/glfw3.h>

namespace BoxGame {
	class Enemy {
	public:
		float x, y;
		float size;

		Enemy() {
			size = 0.5f;
			x = 0;
			y = 0;
		}
		~Enemy() {

		}

		void Draw() {
			glColor4f(1, 0, 0, 1);
			glBegin(GL_QUADS);
			glVertex2f(x - (size / 8), y - (size / 2));
			glVertex2f(x - (size / 8), y + (size / 2));
			glVertex2f(x + (size / 8), y + (size / 2));
			glVertex2f(x + (size / 8), y - (size / 2));
			glEnd();
		}

		void Move() {
			x = x - 0.025f;
		}
	};
}