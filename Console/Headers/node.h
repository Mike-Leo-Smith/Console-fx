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
		Node(Node *prev = NULL, Node *next = NULL, SymbolType type = SYMBOL_HEAD, const char *c_str = "");
		~Node(void);
		Symbol *symbol(void) { return _symbol; }
		Node *prev(void) { return _prev; }
		Node *next(void) { return _next; }
		Node *insert_before(SymbolType type = SYMBOL_STR, const char *c_str = "");
		Node *insert_after(SymbolType type = SYMBOL_STR, const char *c_str = "");
	};
}

#endif //CONSOLE_FX_NODE_H
