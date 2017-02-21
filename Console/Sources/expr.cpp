//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/expr.h"
#include "../Headers/misc.h"

namespace fx
{
	int Expr::calc_width(void)
	{
		_width = 0;
		Node *ptr = _node_list->next();
		
		if (ptr == NULL)
		{
			_width = FONT_WIDTH;
		}
		else
		{
			while (ptr != NULL)
			{
				_width += ptr->symbol()->calc_width();
				ptr = ptr->next();
			}
		}
		
		return _width;
	}
	
	int Expr::calc_height(void)
	{
		_height = 0;
		Node *ptr = _node_list->next();
		
		if (ptr == NULL)
		{
			_height = FONT_HEIGHT;
		}
		else
		{
			while (ptr != NULL)
			{
				_height = max(_height, ptr->symbol()->calc_height());
				ptr = ptr->next();
			}
		}
		
		return _height;
	}
	
	int Expr::calc_depth(void)
	{
		_depth = 0;
		Node *ptr = _node_list->next();
		
		if (ptr == NULL)
		{
			_depth = FONT_DEPTH;
		}
		else
		{
			while (ptr != NULL)
			{
				_depth = max(_depth, ptr->symbol()->calc_depth());
				ptr = ptr->next();
			}
		}
		
		return _depth;
	}
	
	Expr::Expr(Node *parent) : _width(FONT_WIDTH), _height(FONT_HEIGHT), _depth(FONT_DEPTH), _parent(parent)
	{
		if (parent == NULL)
		{
			_node_list = new Node(NULL);
		}
		else
		{
			_node_list = new Node(parent->symbol());
		}
	}
	
	Expr::Expr(const char *c_str, size_t start_pos, size_t end_pos)
	{
		_node_list = new Node(NULL);
		
		Node *last = _node_list;
		size_t prev_pos, curr_pos;
		
		for (prev_pos = curr_pos = start_pos; curr_pos <= end_pos; curr_pos++)
		{
			if (c_str[curr_pos] == '/')
			{
				// Dealing with the left side of the '/'.
				if (c_str[curr_pos - 1] == ')')     // The left side of the '/' has something in a pair of parentheses.
				{
					size_t left_par_pos;
					size_t right_par_pos = curr_pos - 1;
					
					for (left_par_pos = right_par_pos - 2; c_str[left_par_pos] != '('; left_par_pos--);
					
					if (prev_pos < left_par_pos)
					{
						// Not a pair of function parentheses.
						if (!is_char(c_str[left_par_pos - 1]))
						{
							last = last->append(SYMBOL_STR, "");
							last->symbol()->str().append(c_str + prev_pos, left_par_pos - prev_pos);
							
							Expr *frac_arg_0 = new Expr(c_str, left_par_pos + 1, right_par_pos - 1);
							
							last = last->append(SYMBOL_FRAC);
							last->symbol()->arg(0).head()->append(frac_arg_0);
							delete frac_arg_0;
						}
						else
						{
							size_t func_start_pos;
							
							// Find where the function name starts.
							for (func_start_pos = curr_pos - 1; func_start_pos > prev_pos && is_char(c_str[func_start_pos - 1]); func_start_pos--);
							
							if (func_start_pos > prev_pos)
							{
								last = last->append(SYMBOL_STR, "");
								last->symbol()->str().append(c_str + prev_pos, func_start_pos - prev_pos);
							}
							
							Expr *frac_arg_0 = new Expr(c_str, func_start_pos, right_par_pos);
							
							last = last->append(SYMBOL_FRAC);
							last->symbol()->arg(0).head()->append(frac_arg_0);
							delete frac_arg_0;
						}
					}
					else    // Everything on the left side of '/' is in a pair of parentheses.
					{
						Expr *frac_arg_0 = new Expr(c_str, left_par_pos + 1, right_par_pos - 1);
						
						last = last->append(SYMBOL_FRAC);
						last->symbol()->arg(0).head()->append(frac_arg_0);
						delete frac_arg_0;
					}
				}
				else    // Left side of the '/' is a string.
				{
					size_t arg_start_pos;
					
					// Find where the arg starts.
					for (arg_start_pos = curr_pos - 1; arg_start_pos > prev_pos && is_char(c_str[arg_start_pos - 1]); arg_start_pos--);
					
					if (arg_start_pos > prev_pos)
					{
						last = last->append(SYMBOL_STR, "");
						last->symbol()->str().append(c_str + prev_pos, arg_start_pos - prev_pos);
					}
					
					Expr *frac_arg_0 = new Expr(c_str, arg_start_pos, curr_pos - 1);
					
					last = last->append(SYMBOL_FRAC);
					last->symbol()->arg(0).head()->append(frac_arg_0);
					delete frac_arg_0;
				}
				
				// Dealing with the right side.
				
			}
			
			if (c_str[curr_pos] == '^')
			{
				
			}
		}
	}
	
	Expr::~Expr(void)
	{
		while (_node_list->next() != NULL)
		{
			delete _node_list->next();
		}
		delete _node_list;
		_node_list = NULL;
		_width = _height = _depth = 0;
	}
	
	String &Expr::to_str(String &result) const
	{
		Node *ptr = _node_list->next();
		String partial_result;
		
		result.clear();
		while (ptr != NULL)
		{
			result.append(ptr->symbol()->to_str(partial_result));
			ptr = ptr->next();
		}
		
		return result;
	}
	
	void Expr::set_parent(Node *parent)
	{
		_parent = parent;
	}
	
	void Expr::clear(void)
	{
		while (_node_list->next() != NULL)
		{
			delete _node_list->next();
		}
	}
	
	Node *Expr::last(void) const
	{
		Node *ptr = _node_list;
		
		while (ptr->next() != NULL)
		{
			ptr = ptr->next();
		}
		
		return ptr;
	}
}