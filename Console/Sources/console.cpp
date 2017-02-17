//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/console.h"

namespace fx
{
	Console::Console(unsigned char *vram) : _line_start(0), _line_end(0), _display(vram, _cursor), y_offset(0)
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
		int y = _line_queue[_line_end]->top() + _line_queue[_line_end]->expr()->height() + _line_queue[_line_end]->expr()->depth();
		
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
		
		_line_queue[_line_end] = new Line(type, editable, y);
		return _line_queue[_line_end];
	}
	
	String &Console::input(String &str_input)
	{
		while (true)
		{
			_cursor.curr_expr()->update();
			render();
			
			int keycode = GetKeycode();
			
			if (keycode >= '0' && keycode <= '9' || keycode >= 'a' && keycode <= 'z' || keycode >= 'A' && keycode <= 'Z' || keycode == '.' || keycode == '(' || keycode == ')' || keycode == '!'
			    || keycode == '%' || keycode == '*' || keycode == '+' || keycode == '[' || keycode == ']' || keycode == '{' || keycode == '}' || keycode == '<' || keycode == '>' || keycode == ',')
			{
				char tmp_str[] = {(char)keycode, '\0'};
				if (_cursor.curr_node()->symbol() == NULL)
				{
					if (_cursor.curr_node()->next() == NULL || _cursor.curr_node()->next()->symbol()->type() != SYMBOL_STR)
					{
						_cursor.set_curr_node(_cursor.curr_node()->insert(SYMBOL_STR, tmp_str));
						_cursor.set_pos(1);
					}
					else
					{
						_cursor.curr_node()->symbol()->str().insert(0, tmp_str);
						_cursor.set_pos(_cursor.pos() + 1);
					}
				}
				else
				{
					if (_cursor.curr_node()->symbol()->type() == SYMBOL_STR)
					{
						_cursor.curr_node()->symbol()->str().insert((size_t)_cursor.pos(), tmp_str);
						_cursor.set_pos(_cursor.pos() + 1);
					}
					else if (_cursor.curr_node()->next() == NULL || _cursor.curr_node()->next()->symbol()->type() != SYMBOL_STR)
					{
						_cursor.set_curr_node(_cursor.curr_node()->insert(SYMBOL_STR, tmp_str));
						_cursor.set_pos(1);
					}
					else
					{
						_cursor.curr_node()->symbol()->str().insert(0, tmp_str);
						_cursor.set_pos(1);
					}
				}
				continue;
			}
			
			if (keycode == KEY_CTRL_EXE)
			{
				if (_cursor.curr_line() == _line_queue[_line_end])
				{
					_line_queue[_line_end]->set_editable(false);
					return _line_queue[_line_end]->expr()->to_str(str_input);
				}
				continue;
			}
			
			if (keycode == KEY_CTRL_LEFT)
			{
				_cursor.move_left();
				continue;
			}
			
			if (keycode == KEY_CTRL_RIGHT)
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
		_line_queue[_line_end]->expr()->node_list()->insert(SYMBOL_STR, str_output.c_str());
		_line_queue[_line_end]->expr()->update();
		
		if (_line_queue[_line_end]->expr()->width() >= SCREEN_WIDTH)
		{
			_line_queue[_line_end]->set_scroll(0);
		}
		else
		{
			_line_queue[_line_end]->set_scroll(SCREEN_WIDTH - _line_queue[_line_end]->expr()->width() + 1);
		}
		
		// New line for input in the next turn.
		_cursor.set_curr_line(add_line(LINE_INPUT, true));
	}
	
	void Console::render(void)
	{
		
	}
}