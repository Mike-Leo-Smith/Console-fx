//
// Created by Mike Smith on 2017/2/16.
//

#include <GLFW/glfw3.h>
#include "../../graphics.h"
#include "../Headers/key.h"
#include "../Headers/symbol.h"

namespace fx
{
	// Platform-specific function, need to be implemented by yourself.
	int GetKeycode(void)
	{
		glfwWaitEventsTimeout(1);
		
		if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))
		{
			if (glfwGetKey(win, '1'))
			{
				return '!';
			}
			
			if (glfwGetKey(win, '6'))
			{
				return SYMBOL_POWER;
			}
			
			if (glfwGetKey(win, '8'))
			{
				return '*';
			}
			
			if (glfwGetKey(win, '9'))
			{
				return '(';
			}
			
			if (glfwGetKey(win, '0'))
			{
				return ')';
			}
			
			if (glfwGetKey(win, '='))
			{
				return '+';
			}
			
			if (glfwGetKey(win, ','))
			{
				return '<';
			}
			
			if (glfwGetKey(win, '.'))
			{
				return '>';
			}
			
			if (glfwGetKey(win, '\''))
			{
				return '\"';
			}
		}
		
		for (int i = 0; i <= 0x7f; i++)
		{
			if (glfwGetKey(win, i))
			{
				if (i >= 'A' && i <= 'Z')
				{
					if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))
					{
						return i;
					}
					else
					{
						return i - 'A' + 'a';
					}
				}
				else
				{
					return i;
				}
			}
		}
		
		if (glfwGetKey(win, GLFW_KEY_ENTER))
		{
			return CONTROL_EXE;
		}
		
		if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			return CONTROL_RIGHT;
		}
		
		if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			return CONTROL_LEFT;
		}
		
		if (glfwGetKey(win, GLFW_KEY_UP))
		{
			return CONTROL_UP;
		}
		
		if (glfwGetKey(win, GLFW_KEY_DOWN))
		{
			return CONTROL_DOWN;
		}
		else if (glfwGetKey(win, GLFW_KEY_LEFT_ALT))
		{
			return CONTROL_AC;
		}
		
		for (int i = GLFW_KEY_F1; i <= GLFW_KEY_F11; i++)
		{
			if (glfwGetKey(win, i))
			{
				return SYMBOL_ABS + i - GLFW_KEY_F1;
			}
		}
		
		return 0;
	}
}