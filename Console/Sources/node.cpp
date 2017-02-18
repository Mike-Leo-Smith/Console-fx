//
// Created by Mike Smith on 2017/2/14.
//

#include "../Headers/node.h"

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
}