//
// Created by Mike Smith on 2017/2/13.
//

#include <iostream>
#include "../Headers/cursor.h"

namespace fx
{
	void Cursor::move_left(void)
	{
		if (_status == CURSOR_EDITING)
		{
			if (_curr_node->symbol() != NULL)  // Not the head node of the main expr of the line.
			{
				if (_curr_node->symbol()->type() == SYMBOL_STR && _pos > 1)   // If in a string and can still move to left.
				{
					_pos--; // Move to left directly.
				}
				else if (_curr_node->prev() == NULL)    // Current node is the head node.
				{
					Symbol *curr_symbol = _curr_expr->parent()->symbol();
					int curr_arg_index = curr_symbol->arg_index(_curr_expr);     // Calculate the index of the current expr in the arg_list.
					
					if (curr_arg_index == 0)    // If it's already the first arg, get it's parent node and move to before it, and update current expr.
					{
						Node *ptr;
						
						_curr_node = _curr_expr->parent()->prev();
						for (ptr = _curr_node; ptr->prev() != NULL; ptr = ptr->prev());
						if (ptr->symbol() == NULL)
						{
							_curr_expr = _curr_line->expr();
						}
						else
						{
							int arg_count = ptr->symbol()->arg_count();
							
							for (int i = 0; i < arg_count; i++)
							{
								if (ptr == ptr->symbol()->arg(i).head())
								{
									_curr_expr = &ptr->symbol()->arg(i);
								}
							}
						}
						
						if (_curr_node->prev() == NULL || _curr_node->symbol()->type() != SYMBOL_STR)
						{
							_pos = 1;
						}
						else
						{
							_pos = (int)_curr_node->symbol()->str().size();
						}
					}
					else
					{
						_curr_expr = &curr_symbol->arg(curr_arg_index - 1);
						_curr_node = _curr_expr->head();
						
						if (_curr_node->symbol()->type() == SYMBOL_STR)
						{
							_pos = (int)_curr_node->symbol()->str().size();
						}
						else
						{
							_pos = 1;
						}
					}
				}
				else if (_curr_node->symbol()->type() != SYMBOL_STR)
				{
					_curr_expr = &_curr_node->symbol()->arg(_curr_node->symbol()->arg_count() - 1);
					_curr_node = _curr_expr->last();
					if (_curr_node->prev() == NULL || _curr_node->symbol()->type() != SYMBOL_STR)
					{
						_pos = 1;
					}
					else
					{
						_pos = (int)_curr_node->symbol()->str().size();
					}
				}
				else
				{
					_curr_node = _curr_node->prev();
					
					if (_curr_node->prev() == NULL || _curr_node->symbol()->type() != SYMBOL_STR)
					{
						_pos = 1;
					}
					else
					{
						_pos = (int)_curr_node->symbol()->str().size();
					}
				}
			}
			else
			{
				_curr_expr = _curr_line->expr();
				_curr_node = _curr_expr->last();
				
				if (_curr_node->prev() == NULL || _curr_node->symbol()->type() != SYMBOL_STR)
				{
					_pos = 1;
				}
				else
				{
					_pos = (int)_curr_node->symbol()->str().size();
				}
			}
		}
		else
		{
			if (_curr_line->editable())
			{
				_curr_expr = _curr_line->expr();
				_curr_node = _curr_expr->last();
				if (_curr_node->head_of_line() || _curr_node->symbol()->type() != SYMBOL_STR)
				{
					_pos = 1;
				}
				else
				{
					_pos = (int)_curr_node->symbol()->str().size();
				}
				_status = CURSOR_EDITING;
			}
			else
			{
				if (_curr_line->expr()->width() > SCREEN_WIDTH)
				{
					_curr_line->set_scroll(_curr_line->scroll() + 16);
					if (_curr_line->scroll() > 0)
					{
						_curr_line->set_scroll(0);
					}
				}
			}
		}
	}
	
	void Cursor::move_right(void)
	{
		if (_status == CURSOR_EDITING)
		{
			if (_curr_node->symbol() != NULL && _curr_node->symbol()->type() == SYMBOL_STR && _pos < _curr_node->symbol()->str().size())
			{
				_pos++;
			}
			else if (_curr_node->next() != NULL)
			{
				if (_curr_node->next()->symbol()->type() != SYMBOL_STR)
				{
					_curr_expr = &_curr_node->next()->symbol()->arg(0);
					_curr_node = _curr_expr->head();
					_pos = 1;
				}
				else
				{
					_curr_node = _curr_node->next();
					_pos = 1;
				}
			}
			else if (_curr_expr->parent() != NULL)
			{
				Symbol *curr_symbol = _curr_expr->parent()->symbol();
				int curr_arg_index = curr_symbol->arg_index(_curr_expr);
				
				if (curr_arg_index < curr_symbol->arg_count() - 1)
				{
					_curr_expr = &(curr_symbol->arg(curr_arg_index + 1));
					_curr_node = _curr_expr->head();
					_pos = 1;
				}
				else
				{
					Node *ptr;
					
					_curr_node = _curr_expr->parent();
					_pos = 1;
					
					// Find the head of the node list.
					for (ptr = _curr_node; ptr->prev() != NULL; ptr = ptr->prev());
					
					// Test if it's the main expr of the line.
					if (ptr->symbol() == NULL)
					{
						_curr_expr = _curr_line->expr();
					}
					else    // If not, get the pointer to the expr.
					{
						int arg_count = ptr->symbol()->arg_count();
						
						for (int i = 0; i < arg_count; i++)
						{
							if (ptr == ptr->symbol()->arg(i).head())
							{
								_curr_expr = &ptr->symbol()->arg(i);
								break;
							}
						}
					}
				}
			}
			else
			{
				_curr_node = _curr_expr->head();
				_pos = 1;
			}
		}
		else
		{
			if (curr_line()->editable())
			{
				_curr_expr = _curr_line->expr();
				_curr_node = _curr_expr->head();
				_pos = 1;
				_status = CURSOR_EDITING;
			}
			else
			{
				if (_curr_line->width() > SCREEN_WIDTH)
				{
					_curr_line->set_scroll(_curr_line->scroll() - 16);
					if (_curr_line->width() + _curr_line->scroll() < SCREEN_WIDTH)
					{
						_curr_line->set_scroll(SCREEN_WIDTH - _curr_line->width());
					}
				}
			}
		}
	}
	
	void Cursor::set_curr_line(Line *line)
	{
		_curr_line = line;
		_curr_expr = _curr_line->expr();
		_curr_node = _curr_expr->head();
		_pos = 1;
		if (_curr_line->expr()->empty())
		{
			_status = CURSOR_EDITING;
		}
		else
		{
			_status = CURSOR_SELECTING;
		}
	}
	
	void Cursor::insert(SymbolType type, const char *c_str)
	{
		if (type == SYMBOL_STR)
		{
			if (_status == CURSOR_EDITING)
			{
				if (_curr_node->head_of_line())
				{
					if (_curr_node->last_of_expr() || _curr_node->next()->symbol()->type() != SYMBOL_STR)
					{
						_curr_node = _curr_node->append(SYMBOL_STR, c_str);
						_pos = 1;
					}
					else
					{
						_curr_node->symbol()->str().insert(0, c_str);
						_pos++;
					}
				}
				else
				{
					if (_curr_node->symbol()->type() == SYMBOL_STR)
					{
						_curr_node->symbol()->str().insert((size_t)pos(), c_str);
						_pos++;
					}
					else if (_curr_node->last_of_expr() || _curr_node->next()->symbol()->type() != SYMBOL_STR)
					{
						_curr_node = _curr_node->append(SYMBOL_STR, c_str);
						_pos = 1;
					}
					else
					{
						_curr_node->symbol()->str().insert(0, c_str);
						_pos = 1;
					}
				}
			}
			else
			{
				if (_curr_line->editable())
				{
					_curr_line->expr()->clear();
					_curr_expr = _curr_line->expr();
					_curr_node = _curr_expr->head()->append(SYMBOL_STR, c_str);
					_pos = 1;
					_status = CURSOR_EDITING;
				}
			}
		}
		else
		{
			if (_status == CURSOR_EDITING)
			{
				if (_curr_node->head_of_line() || _curr_node->symbol()->type() != fx::SYMBOL_STR)
				{
					_curr_expr = &curr_node()->append(type)->symbol()->arg(0);
					_curr_node = _curr_expr->head();
					_pos = 1;
				}
				else
				{
					if (_pos < _curr_node->symbol()->str().size())
					{
						String &curr_str = _curr_node->symbol()->str();
						
						_curr_node->append(SYMBOL_STR, curr_str.c_str() + _pos);
						curr_str.remove((size_t)_pos, curr_str.size());
					}
					_curr_expr = &_curr_node->append(type)->symbol()->arg(0);
					_curr_node = _curr_expr->head();
					_pos = 1;
				}
			}
			else
			{
				if (_curr_line->editable())
				{
					_curr_line->expr()->clear();
					_curr_expr = curr_line()->expr();
					_curr_node = curr_expr()->head()->append(type);
					_pos = 1;
					_status = CURSOR_EDITING;
				}
			}
		}
	}
	
	void Cursor::backspace(void)
	{
		
	}
	
	void Cursor::all_clear(void)
	{
		if (_curr_line->editable())
		{
			_curr_line->expr()->clear();
			_curr_expr = _curr_line->expr();
			_curr_node = _curr_expr->head();
			_status = CURSOR_EDITING;
			_pos = 1;
		}
	}
}