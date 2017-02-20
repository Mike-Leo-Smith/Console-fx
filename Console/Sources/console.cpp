//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/console.h"

namespace fx
{
	Console::Console(unsigned char *vram) : _line_start(0), _line_end(0), _line_count(0), _display(vram, _cursor), _offset(0)
	{
		_line_queue[0] = new Line(LINE_INPUT, true, 0);
		_line_count++;
		_cursor.goto_line(_line_queue[0]);
	}
	
	Console::~Console(void)
	{
		while (_line_start != _line_end)
		{
			pop_line();
		}
		_line_count = 0;
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
			_line_count--;
		}
	}
	
	Line *Console::add_line(LineType type, bool editable)
	{
		int gap = 3;
		int offset = _line_queue[_line_end]->bottom() + 1 + gap;
		
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
		_line_count++;
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
			    || keycode == ' ' || keycode == '/' || keycode == '*' || keycode == '+' || keycode == '[' || keycode == ']'
			    || keycode == '{' || keycode == '}' || keycode == '<' || keycode == '>' || keycode == ',' || keycode == '\"')
			{
				char tmp_str[] = {(char)keycode, '\0'};
				
				_cursor.insert(SYMBOL_STR, tmp_str);
				continue;
			}
			
			if (keycode == VARIABLE_ANS)
			{
				_cursor.insert(SYMBOL_STR, "last");
				continue;
			}
			
			if (keycode == VARIABLE_PI)
			{
				_cursor.insert(SYMBOL_STR, "pi");
				continue;
			}
			
			if (keycode == VARIABLE_THETA)
			{
				_cursor.insert(SYMBOL_STR, "theta");
				continue;
			}
			
			if (keycode == FUNCTION_CUBEROOT)
			{
				_cursor.insert(SYMBOL_ROOT);
				_cursor.insert(SYMBOL_STR, "3");
				_cursor.move_right();
				continue;
			}
			
			if (keycode == FUNCTION_ARCCOS)
			{
				_cursor.insert(SYMBOL_STR, "arccos(");
				continue;
			}
			
			if (keycode == FUNCTION_ARCSIN)
			{
				_cursor.insert(SYMBOL_STR, "arcsin(");
				continue;
			}
			
			if (keycode == FUNCTION_ARCTAN)
			{
				_cursor.insert(SYMBOL_STR, "arctan(");
				continue;
			}
			
			if (keycode == FUNCTION_SQUARE)
			{
				_cursor.insert(SYMBOL_POWER);
				_cursor.move_right();
				_cursor.insert(SYMBOL_STR, "2");
				_cursor.move_left();
				_cursor.move_left();
				continue;
			}
			
			if (keycode == FUNCTION_POWER_10)
			{
				_cursor.insert(SYMBOL_POWER);
				_cursor.insert(SYMBOL_STR, "10");
				_cursor.move_right();
				continue;
			}
			
			if (keycode == FUNCTION_POWER_E)
			{
				_cursor.insert(SYMBOL_POWER);
				_cursor.insert(SYMBOL_STR, "e");
				_cursor.move_right();
				continue;
			}
			
			if (keycode == FUNCTION_LN)
			{
				_cursor.insert(SYMBOL_STR, "ln(");
				continue;
			}
			
			if (keycode == FUNCTION_SIN)
			{
				_cursor.insert(SYMBOL_STR, "sin(");
				continue;
			}
			
			if (keycode == FUNCTION_COS)
			{
				_cursor.insert(SYMBOL_STR, "cos(");
				continue;
			}
			
			if (keycode == FUNCTION_TAN)
			{
				_cursor.insert(SYMBOL_STR, "tan(");
			}
			
			if (keycode == FUNCTION_FLOAT)
			{
				_cursor.insert(SYMBOL_STR, "float(");
				continue;
			}
			
			if (keycode == FUNCTION_RECIPROCAL)
			{
				_cursor.insert(SYMBOL_POWER);
				_cursor.move_right();
				_cursor.insert(SYMBOL_STR, "-1");
				_cursor.move_left();
				_cursor.move_left();
				_cursor.move_left();
				continue;
			}
			
			if (keycode == FUNCTION_EXP)
			{
				_cursor.insert(SYMBOL_STR, "exp(");
				continue;
			}
			
			if (keycode == FUNCTION_SIMPLIFY)
			{
				_cursor.insert(SYMBOL_STR, "simplify(");
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
					_line_queue[_line_end]->set_scroll(0);
					return _line_queue[_line_end]->expr()->to_str(str_input);
				}
				continue;
			}
			
			if (keycode == CONTROL_AC)
			{
				_cursor.clear_line();
				continue;
			}
			
			if (keycode == CONTROL_DEL)
			{
				_cursor.backspace();
				continue;
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
				_cursor.goto_line(_line_queue[index]);
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
				_cursor.goto_line(_line_queue[index]);
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
		_cursor.goto_line(add_line(LINE_INPUT, true));
		_line_queue[_line_end]->update();
	}
	
	void Console::render(void)
	{
		int i = _line_start;
		int visited = 0;
		
		_display.clear_all();
		while (visited < _line_count)
		{
			_display.print_line(*_line_queue[i], _offset + _line_queue[i]->offset());
			if (_cursor.curr_line() == _line_queue[i])
			{
				bool redraw_flag = false;
				int bottom_preserved = 8;
				
				if (_cursor.status() == CURSOR_SELECTING)
				{
					if (_offset + _cursor.curr_line()->offset() < 0)
					{
						_offset = -_cursor.curr_line()->offset();
						if (_offset > 0)
						{
							_offset = 0;
						}
						redraw_flag = true;
					}
					else if (_offset + _cursor.curr_line()->bottom() >= SCREEN_HEIGHT - bottom_preserved)
					{
						if (_cursor.curr_line()->height() < SCREEN_HEIGHT - bottom_preserved)
						{
							_offset += SCREEN_HEIGHT - bottom_preserved - (_offset + _cursor.curr_line()->bottom()) - 1;
							redraw_flag = true;
						}
					}
				}
				else
				{
					int scroll_round = 2 * FONT_WIDTH - 1;
					
					if (_cursor.x() < SCREEN_WIDTH - 24)
					{
						if (_cursor.curr_line()->scroll() < 0)
						{
							int d = SCREEN_WIDTH - 24 - _cursor.x();
							int scroll_back = (d / scroll_round + 1) * scroll_round;
							
							_cursor.curr_line()->set_scroll(_cursor.curr_line()->scroll() + scroll_back);
							if (_cursor.curr_line()->scroll() > 0)
							{
								_cursor.curr_line()->set_scroll(0);
							}
							redraw_flag = true;
						}
					}
					else if (_cursor.x() >= SCREEN_WIDTH - 8)
					{
						if (_cursor.curr_line()->width() > SCREEN_WIDTH)
						{
							int d = _cursor.x() - (SCREEN_WIDTH - 8);
							int scroll_more = (d / scroll_round + 1) * scroll_round;
							
							_cursor.curr_line()->set_scroll(_cursor.curr_line()->scroll() - scroll_more);
							redraw_flag = true;
						}
					}
					
					if (_cursor.y() < 0)
					{
						_offset -= _cursor.y();
						redraw_flag = true;
					}
					else if (_cursor.y() + _cursor.length() + 1 > SCREEN_HEIGHT - bottom_preserved)
					{
						if (_cursor.length() + 1 < SCREEN_HEIGHT - bottom_preserved)
						{
							_offset += SCREEN_HEIGHT - bottom_preserved - (_cursor.y() + _cursor.length()) - 1;
							redraw_flag = true;
						}
					}
				}
				
				if (redraw_flag)
				{
					i = _line_start;
					visited = 0;
					_display.clear_all();
					continue;
				}
			}
			
			i++;
			if (i >= LINE_QUEUE_CAPACITY)
			{
				i = 0;
			}
			visited++;
		}
	}
}
