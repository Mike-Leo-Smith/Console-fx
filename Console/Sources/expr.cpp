//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/expr.h"
#include "../Headers/misc.h"
#include "../Headers/font.h"

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
	
	Expr::~Expr(void)
	{
		/*
		Node *curr = _node_list;
		
		if (curr != NULL)
		{
			Node *next = curr->next();
			
			while (next != NULL)
			{
				delete curr;
				curr = next;
				next = curr->next();
			}
			delete curr;
			_node_list = NULL;
		}
		_width = _height = _depth = 0;
		 */
		
		while (_node_list->next() != NULL)
		{
			delete _node_list->next();
		}
		delete _node_list;
		_node_list = NULL;
		_width = _height = _depth = 0;
	}
	
	String &Expr::to_str(String &result)
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
}