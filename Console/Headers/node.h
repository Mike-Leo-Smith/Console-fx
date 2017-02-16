//
// Created by Mike Smith on 2017/2/14.
//

#ifndef CONSOLE_FX_NODE_H
#define CONSOLE_FX_NODE_H

#include "symbol.h"

namespace fx
{
	class Node
	{
	private:
		Symbol *_symbol;
		Node *_prev;
		Node *_next;
	
	public:
		Node(Node *prev, Node *next, SymbolType type, const char *c_str = "");
		Node(Symbol *parent_symbol) : _symbol(parent_symbol), _prev(NULL), _next(NULL) {}   // Used only for constructing the head of a node_list.
		~Node(void);
		Symbol *symbol(void) const { return _symbol; }
		Node *prev(void) const { return _prev; }
		Node *next(void) const { return _next; }
		void set_symbol(Symbol *symbol) { _symbol = symbol; }
		Node *insert(SymbolType type = SYMBOL_STR, const char *c_str = "");
	};
}

#endif //CONSOLE_FX_NODE_H
