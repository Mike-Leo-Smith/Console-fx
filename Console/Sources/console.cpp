//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/console.h"
#include "../../graphics.h"

namespace fx
{
	Console::Console(unsigned char *vram) : _line_start(0), _line_end(0), _display(vram, _cursor), _offset(0)
	{
		_line_queue[0] = new Line(LINE_INPUT, true, 0);
		_cursor.set_curr_line(_line_queue[0]);
	}
	
	Console::~Console(void)
	{
		while (_line_start != _line_end)
		{
			pop_line();
		}
	}
	
	void Console::pop_line(void)
	{
		if (_line_start != _line_end)
		{
			delete _line_queue[_line_start];
			_line_queue[_line_start] = NULL;
			if (_line_start + 1 >= LINE_QUEUE_CAPACITY)
			{
				_line_start = 0;
			}
			else
			{
				_line_start++;
			}
		}
	}
	
	Line *Console::add_line(LineType type, bool editable)
	{
		int offset = _line_queue[_line_end]->bottom() + 1;
		
		if (_line_end + 1 >= LINE_QUEUE_CAPACITY)
		{
			_line_end = 0;
		}
		else
		{
			_line_end++;
		}
		
		if (_line_end == _line_start)
		{
			pop_line();
		}
		
		_line_queue[_line_end] = new Line(type, editable, offset);
		return _line_queue[_line_end];
	}
	
	String &Console::input(String &str_input)
	{
		while (true)
		{
			_cursor.curr_line()->update();
			render();
			
			int keycode = GetKeycode();
			
			if ((keycode >= '0' && keycode <= '9') || (keycode >= 'a' && keycode <= 'z') || (keycode >= 'A' && keycode <= 'Z')
			    || keycode == '.' || keycode == '(' || keycode == ')' || keycode == '!' || keycode == '-' || keycode == '='
			    || keycode == '%' || keycode == '/' || keycode == '*' || keycode == '+' || keycode == '[' || keycode == ']'
			    || keycode == '{' || keycode == '}' || keycode == '<' || keycode == '>' || keycode == ',' || keycode == ' ')
			{
				char tmp_str[] = {(char)keycode, '\0'};
				
				_cursor.insert(SYMBOL_STR, tmp_str);
				continue;
			}
			
			if ((keycode & 0xff0000) == 0xff0000)
			{
				_cursor.insert((SymbolType)keycode);
				continue;
			}
			
			if (keycode == CONTROL_EXE)
			{
				if (_cursor.curr_line() == _line_queue[_line_end] && !_cursor.curr_line()->expr()->empty())
				{
					_line_queue[_line_end]->set_editable(false);
					return _line_queue[_line_end]->expr()->to_str(str_input);
				}
				continue;
			}
			
			if (keycode == CONTROL_AC)
			{
				_cursor.all_clear();
			}
			
			if (keycode == CONTROL_UP)
			{
				int index;
				
				for (index = 0; _cursor.curr_line() != _line_queue[index]; index++);
				if (index != _line_start)
				{
					index--;
					if (index < 0)
					{
						index = LINE_QUEUE_CAPACITY - 1;
					}
				}
				_cursor.set_curr_line(_line_queue[index]);
				continue;
			}
			
			if (keycode == CONTROL_DOWN)
			{
				int index;
				
				for (index = 0; _cursor.curr_line() != _line_queue[index]; index++);
				if (index != _line_end)
				{
					index++;
					if (index >= LINE_QUEUE_CAPACITY)
					{
						index = 0;
					}
				}
				_cursor.set_curr_line(_line_queue[index]);
				continue;
			}
			
			if (keycode == CONTROL_LEFT)
			{
				_cursor.move_left();
				continue;
			}
			
			if (keycode == CONTROL_RIGHT)
			{
				_cursor.move_right();
				continue;
			}
		}
	}
	
	void Console::output(const String &str_output)
	{
		// Line for output.
		add_line(LINE_OUTPUT, false);
		_line_queue[_line_end]->expr()->head()->append(SYMBOL_STR, str_output.size() > 0 ? str_output.c_str() : "Done");
		_line_queue[_line_end]->update();
		
		if (_line_queue[_line_end]->width() >= SCREEN_WIDTH)
		{
			_line_queue[_line_end]->set_scroll(0);
		}
		else
		{
			_line_queue[_line_end]->set_scroll(SCREEN_WIDTH - _line_queue[_line_end]->width());
		}
		
		// New line for input in the next turn.
		_cursor.set_curr_line(add_line(LINE_INPUT, true));
		_line_queue[_line_end]->update();
	}
	
	void Console::render(void)
	{
		_display.clear_all();
		int i = _line_start;
		
		while (true)
		{
			if ((_line_end == LINE_QUEUE_CAPACITY - 1 && i == 0) || (_line_end < LINE_QUEUE_CAPACITY - 1 && i == _line_end + 1))
			{
				break;
			}
			
			_display.print_line(*_line_queue[i], _offset + _line_queue[i]->offset());
			if (_cursor.curr_line() == _line_queue[i])
			{
				if (_cursor.status() == CURSOR_SELECTING)
				{
					if (_offset + _cursor.curr_line()->offset() < 0)
					{
						_offset = 0;
						i = _line_start;
						continue;
					}
					else if (_offset + _cursor.curr_line()->bottom() >= SCREEN_HEIGHT)
					{
						_offset = SCREEN_HEIGHT - _cursor.curr_line()->bottom() - 1;
						i = _line_start;
						continue;
					}
				}
				else
				{
					
				}
			}
			
			i++;
			if (i >= LINE_QUEUE_CAPACITY)
			{
				i = 0;
			}
		}
		DisplayVRAM();
	}
}