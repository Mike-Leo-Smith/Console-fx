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