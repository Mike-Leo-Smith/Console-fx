//
// Created by Mike Smith on 2017/2/14.
//

#include "../Headers/node.h"
#include "../Headers/expr.h"

namespace fx
{
	Node::Node(Node *prev, Node *next, SymbolType type, const char *c_str) : _prev(prev), _next(next)
	{
		_symbol = new Symbol(this, type, c_str);
	}
	
	Node::~Node(void)
	{
		if (_prev != NULL)
		{
			_prev->_next = _next;
		}
		else
		{
			delete _symbol;
		}
		
		if (_next != NULL)
		{
			_next->_prev = _prev;
		}
	}
	
	Node *Node::append(SymbolType type, const char *c_str)
	{
		Node *new_node = new Node(this, _next, type, c_str);
		
		if (_next != NULL)
		{
			_next->_prev = new_node;
		}
		_next = new_node;
		
		return new_node;
	}
	
	Node *Node::find_head(void) const
	{
		Node *ptr;
		
		for (ptr = (Node *)this; ptr->_prev != NULL; ptr = ptr->prev());
		
		return ptr;
	}
	
	Node *Node::append(const Expr *expr)
	{
		Node *ptr;
		
		for (ptr = expr->head()->next(); ptr != NULL; ptr = ptr->next())
		{
			if (ptr->symbol()->type() == SYMBOL_STR)
			{
				append(SYMBOL_STR, ptr->symbol()->str().c_str());
			}
			else
			{
				int arg_count = ptr->symbol()->arg_count();
				
				append(ptr->symbol()->type());
				for (int i = 0; i < arg_count; i++)
				{
					_next->symbol()->arg(i).head()->append(&ptr->symbol()->arg(i));
				}
			}
		}
		
		if (_next != NULL)
		{
			return _next;
		}
		else
		{
			return this;
		}
	}
}