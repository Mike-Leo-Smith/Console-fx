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
		Expr(Node *parent = NULL) :  _parent(parent), _width(0), _height(0), _depth(0) { _node_list = new Node(NULL, NULL, SYMBOL_HEAD); };
		void sample(void)
		{
			_node_list->insert_after(SYMBOL_SUM)->insert_before(SYMBOL_STR, "+666+")->insert_before(SYMBOL_PRODUCT)->symbol()->arg(3)._node_list->insert_after(SYMBOL_DEFINITE);
		}
		~Expr(void);
		Node *node_list(void) const { return _node_list; }
		int width(void) const { return _width; }
		int height(void) const { return _height; }
		int depth(void) const { return _depth; }
		int calc_width(void);
		int calc_height(void);
		int calc_depth(void);
		void update(void) { calc_width(), calc_height(), calc_depth(); }
		String &to_str(String &result);
	};
}

#endif //CONSOLE_FX_EXPR_H
