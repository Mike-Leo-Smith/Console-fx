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
	return true;
}

int main()
{
	fx::Line line(fx::LINE_INPUT, false, 0);
	line.expr()->update();
	fx::Cursor cursor(&line);
	fx::Display display(vram, cursor);
	
	Init();
	display.clear_all();
	display.print_line(line, 0, 0);
	
	int x = 0;
	int y = 0;
	
	while (Render())
	{
		glfwWaitEventsTimeout(1);
		if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			cursor.move_left();
		}
		else if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			cursor.move_right();
		}
		else if (glfwGetKey(win, GLFW_KEY_I))
		{
			if (cursor.curr_node()->symbol() == NULL || cursor.curr_node()->symbol()->type() != fx::SYMBOL_STR)
			{
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_INTEGRAL)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
			else
			{
				if (cursor.pos() < cursor.curr_node()->symbol()->str().size())
				{
					fx::String &curr_str = cursor.curr_node()->symbol()->str();
					cursor.curr_node()->insert(fx::SYMBOL_STR, curr_str.c_str() + cursor.pos());
					curr_str.remove((size_t)cursor.pos(), curr_str.size());
				}
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_INTEGRAL)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
		}
		else if (glfwGetKey(win, GLFW_KEY_S))
		{
			if (cursor.curr_node()->symbol() == NULL || cursor.curr_node()->symbol()->type() != fx::SYMBOL_STR)
			{
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_SUM)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
			else
			{
				if (cursor.pos() < cursor.curr_node()->symbol()->str().size())
				{
					fx::String &curr_str = cursor.curr_node()->symbol()->str();
					cursor.curr_node()->insert(fx::SYMBOL_STR, curr_str.c_str() + cursor.pos());
					curr_str.remove((size_t)cursor.pos(), curr_str.size());
				}
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_SUM)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
		}
		else if (glfwGetKey(win, GLFW_KEY_6))
		{
			if (cursor.curr_node()->symbol() == NULL || cursor.curr_node()->symbol()->type() != fx::SYMBOL_STR)
			{
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_POWER)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
			else
			{
				if (cursor.pos() < cursor.curr_node()->symbol()->str().size())
				{
					fx::String &curr_str = cursor.curr_node()->symbol()->str();
					cursor.curr_node()->insert(fx::SYMBOL_STR, curr_str.c_str() + cursor.pos());
					curr_str.remove((size_t)cursor.pos(), curr_str.size());
				}
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_POWER)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
		}
		else if (glfwGetKey(win, GLFW_KEY_0))
		{
			
		}
		else if (glfwGetKey(win, '/'))
		{
			if (cursor.curr_node()->symbol() == NULL || cursor.curr_node()->symbol()->type() != fx::SYMBOL_STR)
			{
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_FRAC)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
			else
			{
				if (cursor.pos() < cursor.curr_node()->symbol()->str().size())
				{
					fx::String &curr_str = cursor.curr_node()->symbol()->str();
					cursor.curr_node()->insert(fx::SYMBOL_STR, curr_str.c_str() + cursor.pos());
					curr_str.remove((size_t)cursor.pos(), curr_str.size());
				}
				cursor.set_curr_expr(&cursor.curr_node()->insert(fx::SYMBOL_FRAC)->symbol()->arg(0));
				cursor.set_curr_node(cursor.curr_expr()->node_list());
				cursor.set_pos(1);
			}
		}
		
		display.clear_all();
		display.print_line(line, x, y);
		if (cursor.out_of_sight())
		{
			if (cursor.left() < 0)
			{
				if (cursor.curr_node()->symbol() == NULL)
				{
					line.set_scroll(0);
				}
				else
				{
					line.set_scroll(line.scroll() + 16 - cursor.left());
					if (line.scroll() > 0)
					{
						line.set_scroll(0);
					}
				}
			}
			
			if (cursor.left() >= SCREEN_WIDTH - 8)
			{
				line.set_scroll(line.scroll() - cursor.left() - 12 + SCREEN_WIDTH);
			}
			
			if (cursor.top() < 0)
			{
				y = 0;
			}
			else if (cursor.top() + cursor.length() > SCREEN_HEIGHT)
			{
				y -= cursor.top() + cursor.length() - SCREEN_HEIGHT;
			}
			
			display.clear_all();
			display.print_line(line, x, y);
		}
		//cursor.flash();
		line.expr()->update();
	}
	
	return 0;
}