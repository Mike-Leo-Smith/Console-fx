//
// Created by Mike Smith on 2017/2/13.
//

#ifndef CONSOLE_FX_CURSOR_H
#define CONSOLE_FX_CURSOR_H

#include "expr.h"
#include "line.h"
#include "config.h"

namespace fx
{
	enum CursorStatus
	{
		CURSOR_EDITING,
		CURSOR_SELECTING
	};
	
	class Cursor
	{
	private:
		CursorStatus _status;
		Line *_curr_line;
		Expr *_curr_expr;
		Node *_curr_node;
		int _left;
		int _top;
		int _length;
		int _pos;
		bool _visible;
	
	public:
		Cursor(void) : _curr_line(NULL), _curr_expr(NULL), _curr_node(NULL), _visible(true), _left(0), _top(0), _length(7), _status(CURSOR_EDITING) {}
		Line *curr_line(void) const { return _curr_line; }
		Expr *curr_expr(void) const { return _curr_expr; }
		Node *curr_node(void) const { return _curr_node; }
		CursorStatus status(void) const { return _status; }
		bool visible(void) const { return _visible; }
		void flash(void) { _visible = !_visible; }
		int pos(void) const { return _pos; }
		int left(void) const { return _left; }
		int top(void) const { return _top; }
		int length(void) const { return _length; }
		void set_left(int left) { _left = left; }
		void set_top(int top) { _top = top; }
		void set_length(int length) { _length = length; }
		void goto_line(Line *line);
		void move_left(void);
		void move_right(void);
		void insert(SymbolType type, const char *c_str = "");
		void all_clear(void);
		void backspace(void);
	};
}

#endif //CONSOLE_FX_CURSOR_H
