//
// Created by Mike Smith on 2017/2/16.
//

#include <GLFW/glfw3.h>
#include "../../graphics.h"
#include "../Headers/symbol.h"
#include "../Headers/key.h"

namespace fx
{
	// Platform-specific function, need to be implemented by yourself.
	int GetKeycode(void)
	{
		int code = 0;
		
		glfwWaitEventsTimeout(1);
		if (glfwGetKey(win, GLFW_KEY_1))
		{
			code = '1';
		}
		else if (glfwGetKey(win, GLFW_KEY_ENTER))
		{
			code = CONTROL_EXE;
		}
		else if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			code = CONTROL_RIGHT;
		}
		else if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			code = CONTROL_LEFT;
		}
		else if (glfwGetKey(win, GLFW_KEY_UP))
		{
			code = CONTROL_UP;
		}
		else if (glfwGetKey(win, GLFW_KEY_DOWN))
		{
			code = CONTROL_DOWN;
		}
		else if (glfwGetKey(win, GLFW_KEY_D))
		{
			code = SYMBOL_DEFINITE;
		}
		
		Render();
		return code;
	}
}