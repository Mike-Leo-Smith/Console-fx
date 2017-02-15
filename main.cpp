#include <iostream>
#include <glfw/glfw3.h>
#include "Console/Headers/display.h"

GLFWwindow *win;
const int scale = 3;
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
	glfwSetWindowSizeLimits(win, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale,SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);
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

bool Render(void)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			(vram[(y << SCREEN_WIDTH_RSHIFT) + (x >> 3)] & (128 >> (x & 7))) ? DrawPixel(x, y) : ClearPixel(x, y);
		}
	}
	glFlush();
	glfwSwapBuffers(win);
	if (glfwWindowShouldClose(win))
	{
		glfwDestroyWindow(win);
		return false;
	}
	glfwWaitEventsTimeout(0.05);
	return true;
}

int main()
{
	fx::Display display(vram);
	fx::String str = "hello, world", p1, p2;
	
	str.split(5, p2, p2);
	
	std::cout << str.c_str() << std::endl;
	std::cout << p1.c_str() << std::endl;
	std::cout << p2.c_str() << std::endl;
	
	Init();
	//display.draw_line(0, 0, 127, 63);
	//display.print_char('H', 0, 0);
	
	clock_t t0 = clock();
	fx::Expr expr;
	
	expr.sample();
	expr.update();
	std::cout << expr.to_str(p1).c_str() << std::endl;
	//display.draw_line(99, 20, 100, 0);
	display.print_expr(expr, 1, 12);
	//display.reverse_area(1, 24 - expr.height() + 1, 1 + expr.width() - 1, 24 + expr.depth());
	//display.print_str("hello", 94, 8);
	
	clock_t t1 = clock();
	//std::cout << expr.node_list()->next()->symbol()->arg_index(expr.node_list()->next()->symbol()->arg(2)) << std::endl;
	std::cout << (t1 - t0) / 1000.0 << "ms" << std::endl;
	
	while (Render())
		;
	
	return 0;
}