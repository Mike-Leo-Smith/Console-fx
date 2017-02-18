//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/console.h"
#include "../../graphics.h"

namespace fx
{
	Console::Console(unsigned char *vram) : _line_start(0), _line_end(0), _display(vram, _cursor), _y_offset(0)
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
			_cursor.curr_line()->expr()->update();
			render();
			
			int keycode = GetKeycode();
			
			if ((keycode >= '0' && keycode <= '9') || (keycode >= 'a' && keycode <= 'z') || (keycode >= 'A' && keycode <= 'Z') || keycode == '.' || keycode == '(' || keycode == ')' || keycode == '!' || keycode == '-' || keycode == '='
			    || keycode == '%' || keycode == '/' || keycode == '*' || keycode == '+' || keycode == '[' || keycode == ']' || keycode == '{' || keycode == '}' || keycode == '<' || keycode == '>' || keycode == ',' || keycode == ' ')
			{
				char tmp_str[] = {(char)keycode, '\0'};
				
				if (_cursor.status() == CURSOR_EDITING)
				{
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
				}
				else
				{
					if (_cursor.curr_line()->editable())
					{
						_cursor.curr_line()->expr()->clear();
						_cursor.set_curr_expr(_cursor.curr_line()->expr());
						_cursor.set_curr_node(_cursor.curr_expr()->node_list()->insert(SYMBOL_STR, tmp_str));
						_cursor.set_pos(1);
						_cursor.set_status(CURSOR_EDITING);
					}
				}
				continue;
			}
			
			if ((keycode & 0xff0000) == 0xff0000)
			{
				if (_cursor.status() == CURSOR_EDITING)
				{
					if (_cursor.curr_node()->symbol() == NULL || _cursor.curr_node()->symbol()->type() != fx::SYMBOL_STR)
					{
						_cursor.set_curr_expr(&_cursor.curr_node()->insert((fx::SymbolType)keycode)->symbol()->arg(0));
						_cursor.set_curr_node(_cursor.curr_expr()->node_list());
						_cursor.set_pos(1);
					}
					else
					{
						if (_cursor.pos() < _cursor.curr_node()->symbol()->str().size())
						{
							fx::String &curr_str = _cursor.curr_node()->symbol()->str();
							_cursor.curr_node()->insert(fx::SYMBOL_STR, curr_str.c_str() + _cursor.pos());
							curr_str.remove((size_t)_cursor.pos(), curr_str.size());
						}
						_cursor.set_curr_expr(&_cursor.curr_node()->insert((fx::SymbolType)keycode)->symbol()->arg(0));
						_cursor.set_curr_node(_cursor.curr_expr()->node_list());
						_cursor.set_pos(1);
					}
				}
				else
				{
					if (_cursor.curr_line()->editable())
					{
						_cursor.curr_line()->expr()->clear();
						_cursor.set_curr_expr(_cursor.curr_line()->expr());
						_cursor.set_curr_node(_cursor.curr_expr()->node_list()->insert((fx::SymbolType)keycode));
						_cursor.set_pos(1);
						_cursor.set_status(CURSOR_EDITING);
					}
				}
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
				if (_cursor.curr_line()->editable())
				{
					_cursor.curr_line()->expr()->clear();
					_cursor.set_curr_expr(_cursor.curr_line()->expr());
					_cursor.set_curr_node(_cursor.curr_expr()->node_list());
					_cursor.set_status(CURSOR_EDITING);
					_cursor.set_pos(1);
				}
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
				if (_cursor.curr_line()->expr()->empty())
				{
					_cursor.set_status(CURSOR_EDITING);
				}
				else
				{
					_cursor.set_status(CURSOR_SELECTING);
				}
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
				if (_cursor.curr_line()->expr()->empty())
				{
					_cursor.set_status(CURSOR_EDITING);
				}
				else
				{
					_cursor.set_status(CURSOR_SELECTING);
				}
				continue;
			}
			
			if (keycode == CONTROL_LEFT)
			{
				if (_cursor.status() == CURSOR_EDITING)
				{
					_cursor.move_left();
				}
				else
				{
					if (_cursor.curr_line()->editable())
					{
						Node *ptr;
						
						_cursor.set_curr_expr(_cursor.curr_line()->expr());
						for (ptr = _cursor.curr_expr()->node_list(); ptr->next() != NULL; ptr = ptr->next());
						_cursor.set_curr_node(ptr);
						if (_cursor.curr_node()->symbol() == NULL || _cursor.curr_node()->symbol()->type() != SYMBOL_STR)
						{
							_cursor.set_pos(1);
						}
						else
						{
							_cursor.set_pos((int)_cursor.curr_node()->symbol()->str().size());
						}
						_cursor.set_status(CURSOR_EDITING);
					}
					else
					{
						if (_cursor.curr_line()->expr()->width() > SCREEN_WIDTH)
						{
							_cursor.curr_line()->set_scroll(_cursor.curr_line()->scroll() + 16);
							if (_cursor.curr_line()->scroll() > 0)
							{
								_cursor.curr_line()->set_scroll(0);
							}
						}
					}
				}
				continue;
			}
			
			if (keycode == CONTROL_RIGHT)
			{
				if (_cursor.status() == CURSOR_EDITING)
				{
					_cursor.move_right();
				}
				else
				{
					if (_cursor.curr_line()->editable())
					{
						_cursor.set_curr_expr(_cursor.curr_line()->expr());
						_cursor.set_curr_node(_cursor.curr_expr()->node_list());
						_cursor.set_pos(1);
						_cursor.set_status(CURSOR_EDITING);
					}
					else
					{
						if (_cursor.curr_line()->expr()->width() > SCREEN_WIDTH)
						{
							_cursor.curr_line()->set_scroll(_cursor.curr_line()->scroll() - 16);
							if (_cursor.curr_line()->expr()->width() + _cursor.curr_line()->scroll() < SCREEN_WIDTH)
							{
								_cursor.curr_line()->set_scroll(SCREEN_WIDTH - _cursor.curr_line()->expr()->width());
							}
						}
					}
				}
				continue;
			}
		}
	}
	
	void Console::output(const String &str_output)
	{
		// Line for output.
		add_line(LINE_OUTPUT, false);
		_line_queue[_line_end]->expr()->node_list()->insert(SYMBOL_STR, str_output.size() > 0 ? str_output.c_str() : "Done");
		_line_queue[_line_end]->expr()->update();
		
		if (_line_queue[_line_end]->expr()->width() >= SCREEN_WIDTH)
		{
			_line_queue[_line_end]->set_scroll(0);
		}
		else
		{
			_line_queue[_line_end]->set_scroll(SCREEN_WIDTH - _line_queue[_line_end]->expr()->width());
		}
		
		// New line for input in the next turn.
		_cursor.set_curr_line(add_line(LINE_INPUT, true));
		_line_queue[_line_end]->expr()->update();
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
			
			_display.print_line(*_line_queue[i], _y_offset + _line_queue[i]->top());
			if (_cursor.curr_line() == _line_queue[i])
			{
				if (_cursor.status() == CURSOR_SELECTING)
				{
					if (_y_offset + _cursor.curr_line()->top() < 0)
					{
						_y_offset = 0;
						i = _line_start;
						continue;
					}
					else if (_y_offset + _cursor.curr_line()->top() + _cursor.curr_line()->expr()->height() + _cursor.curr_line()->expr()->depth() > SCREEN_HEIGHT)
					{
						_y_offset = SCREEN_HEIGHT - (_cursor.curr_line()->top() + _cursor.curr_line()->expr()->height() + _cursor.curr_line()->expr()->depth());
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