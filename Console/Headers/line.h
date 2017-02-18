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
		int _top;
		int _scroll;
		bool _editable;
		Expr *_expr;
		LineType _type;
	
	public:
		Line(LineType type = LINE_INPUT, bool editable = true, int top = 0) : _top(top), _scroll(0), _editable(editable), _type(type) { _expr = new Expr; }
		~Line(void) { if (_expr != NULL) delete _expr; };
		int scroll(void) const { return _scroll; }
		int top(void) const { return _top; }
		Expr *expr(void) const { return _expr; }
		LineType type(void) const { return _type; }
		bool editable(void) const { return _editable; }
		void set_top(int top) { _top = top; }
		void set_scroll(int scroll) { _scroll = scroll; }
		void set_editable(bool editable) { _editable = editable; }
		void set_type(LineType type) { _type = type; }
	};
}

#endif //CONSOLE_FX_LINE_H
