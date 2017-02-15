//
// Created by Mike Smith on 2017/2/13.
//

#ifndef CONSOLE_FX_CURSOR_H
#define CONSOLE_FX_CURSOR_H

#include "expr.h"
#include "line.h"

namespace fx
{
	class Cursor
	{
	private:
		Line *_curr_line;
		Expr *_curr_expr;
		Node *_curr_node;
		int _pos;
	
	public:
		Line *curr_line(void) { return _curr_line; }
		Expr *curr_expr(void) { return _curr_expr; }
		Node *curr_node(void) { return _curr_node; }
		int pos(void) const { return _pos; }
		void move_up(void);
		void move_down(void);
		void move_left(void);
		void move_right(void);
	};
}

#endif //CONSOLE_FX_CURSOR_H
