//
// Created by Mike Smith on 2017/2/14.
//

#include "../Headers/node.h"

namespace fx
{
	Node::Node(Node *prev, Node *next, SymbolType type, const char *c_str) : _prev(prev), _next(next)
	{
		if (type == SYMBOL_HEAD)
		{
			_symbol = NULL;
		}
		else
		{
			_symbol = new Symbol(type, c_str);
		}
	}
	
	Node::~Node(void)
	{
		if (_prev != NULL)
		{
			_prev->_next = _next;
		}
		
		if (_next != NULL)
		{
			_next->_prev = _prev;
		}
		
		if (_symbol != NULL)
		{
			delete _symbol;
		}
	}
	
	Node *Node::insert_before(SymbolType type, const char *c_str)
	{
		Node *new_node = new Node(_prev, this, type, c_str);
		
		_prev->_next = new_node;
		_prev = new_node;
		
		return new_node;
	}
	
	Node *Node::insert_after(SymbolType type, const char *c_str)
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