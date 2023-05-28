#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "GameLoop.hpp"

int main()
{
	BoxGame::GameLoop Loop;
	Loop.Run();
}
