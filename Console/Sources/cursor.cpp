//
// Created by Mike Smith on 2017/2/13.
//

#include <iostream>
#include "../Headers/cursor.h"

namespace fx
{
	void Cursor::move_up(void)
	{
		
	}
	
	void Cursor::move_down(void)
	{
		
	}
	
	void Cursor::move_left(void)
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
							if (ptr == ptr->symbol()->arg(i).node_list())
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
					_curr_node = _curr_expr->node_list();
					
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
				Node *ptr;
				
				_curr_expr = &_curr_node->symbol()->arg(_curr_node->symbol()->arg_count() - 1);
				for (ptr = _curr_expr->node_list(); ptr->next() != NULL; ptr = ptr->next());
				_curr_node = ptr;
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
			Node *ptr;
			
			_curr_expr = _curr_line->expr();
			for (ptr = _curr_expr->node_list(); ptr->next() != NULL; ptr = ptr->next());
			_curr_node = ptr;
			
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
	
	void Cursor::move_right(void)
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
				_curr_node = _curr_expr->node_list();
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
				_curr_node = _curr_expr->node_list();
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
						if (ptr == ptr->symbol()->arg(i).node_list())
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
			_curr_node = _curr_expr->node_list();
			_pos = 1;
		}
	}
}