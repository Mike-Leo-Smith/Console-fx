//
// Created by Mike Smith on 2017/2/14.
//

#ifndef CONSOLE_FX_LINE_H
#define CONSOLE_FX_LINE_H

#include "expr.h"

namespace fx
{
	class Line
	{
	private:
		int _scroll;
		Expr *_expr;
	
	public:
		Line(void) : _scroll(0) { _expr = new Expr; }
		int scroll(void) const { return _scroll; }
		void set_scroll(int scroll) { _scroll = scroll; }
		Expr *expr(void) const { return _expr; }
	};
}

#endif //CONSOLE_FX_LINE_H
