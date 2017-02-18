#include <iostream>
#include <glfw/glfw3.h>
#include "Console/Headers/display.h"
#include "Console/Headers/console.h"

GLFWwindow *win;
const int scale = 2;
unsigned char vram[VRAM_SIZE_BYTE];

void Init(void)
{
	glfwInit();
	win = glfwCreateWindow(SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale, "Display", NULL, NULL);
	glfwMakeContextCurrent(win);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glTranslated(-1.0, 1.0, 0);
	glScaled(2.0 / SCREEN_WIDTH, -2.0 / SCREEN_HEIGHT, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSetWindowSizeLimits(win, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);
}

inline void DrawPixel(int x, int y)
{
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	{
		glVertex2d(x, y);
		glVertex2d(x, y + 1);
		glVertex2d(x + 1, y + 1);
		glVertex2d(x + 1, y);
	}
	glEnd();
}

inline void ClearPixel(int x, int y)
{
	glColor3ub(235, 235, 235);
	glBegin(GL_QUADS);
	{
		glVertex2d(x, y);
		glVertex2d(x, y + 1);
		glVertex2d(x + 1, y + 1);
		glVertex2d(x + 1, y);
	}
	glEnd();
}

void Render(void)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			(vram[(y * SCREEN_WIDTH_BYTE) + (x >> 3)] & (128 >> (x & 7))) ? DrawPixel(x, y) : ClearPixel(x, y);
		}
	}
	glFlush();
	glfwSwapBuffers(win);
	if (glfwWindowShouldClose(win))
	{
		glfwDestroyWindow(win);
		exit(0);
	}
}

int main()
{
	fx::Console console(vram);
	fx::String buffer;
	Init();
	while (true)
	{
		console.input(buffer);
		std::cout << buffer.c_str() << std::endl;
		console.output(buffer);
	}
}