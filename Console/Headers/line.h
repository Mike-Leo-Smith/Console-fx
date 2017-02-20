//
// Created by Mike Smith on 2017/2/14.
//

#ifndef CONSOLE_FX_LINE_H
#define CONSOLE_FX_LINE_H

#include "expr.h"

namespace fx
{
	enum LineType
	{
		LINE_INPUT,
		LINE_OUTPUT
	};
	
	class Line
	{
	private:
		int _offset;
		int _scroll;
		bool _editable;
		Expr *_expr;
		LineType _type;
	
	public:
		Line(LineType type = LINE_INPUT, bool editable = true, int offset = 0) : _offset(offset), _scroll(0), _editable(editable), _type(type) { _expr = new Expr; }
		~Line(void);
		int scroll(void) const { return _scroll; }
		int offset(void) const { return _offset; }
		int bottom(void) const { return (_offset + height() - 1); }
		Expr *expr(void) const { return _expr; }
		LineType type(void) const { return _type; }
		bool editable(void) const { return _editable; }
		int width(void) const { return _expr->width(); }
		int height(void) const { return (_expr->height() + _expr->depth()); }
		void set_offset(int top) { _offset = top; }
		void set_scroll(int scroll) { _scroll = scroll; }
		void set_editable(bool editable) { _editable = editable; }
		void set_type(LineType type) { _type = type; }
		void update(void) { _expr->calc_width(), _expr->calc_height(), _expr->calc_depth(); }
	};
}

#endif //CONSOLE_FX_LINE_H
