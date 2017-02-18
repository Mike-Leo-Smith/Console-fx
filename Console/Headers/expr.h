//
// Created by Mike Smith on 2017/2/12.
//

#ifndef CONSOLE_FX_EXPR_H
#define CONSOLE_FX_EXPR_H

#include "string.h"
#include "symbol.h"
#include "node.h"

namespace fx
{
	class Expr
	{
	private:
		Node *_node_list;
		Node *_parent;
		
		int _width;
		int _height;
		int _depth;
	
	public:
		Expr(Node *parent = NULL);
		~Expr(void);
		Node *last(void) const;
		Node *head(void) const { return _node_list; }
		Node *parent(void) const { return _parent; }
		int width(void) const { return _width; }
		int height(void) const { return _height; }
		int depth(void) const { return _depth; }
		bool empty(void) const { return (_node_list->next() == NULL); }
		void set_parent(Node *parent);
		int calc_width(void);
		int calc_height(void);
		int calc_depth(void);
		void clear(void);
		String &to_str(String &result) const;
	};
}

#endif //CONSOLE_FX_EXPR_H
