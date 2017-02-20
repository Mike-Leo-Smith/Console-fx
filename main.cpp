#include <iostream>
#include <glfw/glfw3.h>
#include "Console/Headers/display.h"
#include "Console/Headers/console.h"
#include "Eigenmath/Headers/defs.h"

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

void DisplayVRAM(void)
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

fx::String io_buffer;
fx::String calc_buffer;

void printchar(int c)
{
	calc_buffer.append((char)c);
}

void
printstr(char *s)
{
	calc_buffer.append(s);
}

int main()
{
	fx::Console console(vram);
	Init();
	const char *help_str[] =
			{
					"F1:  ABS",
					"F2:  DEF",
					"F3:  FRA",
					"F4:  INT",
					"F5:  LOG",
					"F6:  POW",
					"F7:  PRO",
					"F8:  ROO",
					"F9:  SQR",
					"F10: STR",
					"F11: SUM",
					NULL
			};
	
	for (int i = 0; help_str[i] != NULL; i++)
	{
		std::cout << help_str[i] << "\t";
	}
	std::cout << std::endl;
	
	while (true)
	{
		console.input(io_buffer);
		calc_buffer.clear();
		run((char *)io_buffer.c_str());
		if (calc_buffer.c_str()[calc_buffer.size() - 1] == '\n')
		{
			calc_buffer.backspace();
		}
		console.output(calc_buffer);
	}
}