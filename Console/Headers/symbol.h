//
// Created by Mike Smith on 2017/2/12.
//

#ifndef CONSOLE_FX_SYMBOL_H
#define CONSOLE_FX_SYMBOL_H

#include "string.h"

namespace fx
{
	class Node;
	class Expr;
	
	enum SymbolType
	{
		SYMBOL_HEAD = 0xfe0000,    // Symbol in a head node.
		SYMBOL_ABS = 0xff0000,     // Values start from 0xff0000 to avoid mixing with other keycode or ConsoleCode.
		SYMBOL_DEFINITE,
		SYMBOL_FRAC,
		SYMBOL_INTEGRAL,
		SYMBOL_LOG,
		SYMBOL_POWER,
		SYMBOL_PRODUCT,
		SYMBOL_ROOT,
		SYMBOL_SQRT,
		SYMBOL_STR,
		SYMBOL_SUM
	};
	
	class Symbol
	{
	private:
		SymbolType _type;
		int _width;
		int _height;
		int _depth;
		union
		{
			String *_str;
			Expr *_arg_list;
		};
	
	public:
		Symbol(Node *parent_node, SymbolType type, const char *c_str);
		~Symbol(void);
		int width(void) const { return _width; }
		int height(void) const { return _height; }
		int depth(void) const { return _depth; }
		SymbolType type(void) const { return _type; }
		String &str(void) const { return *_str; }
		Expr *arg_list(void) const { return _arg_list; }
		Expr &arg(int index) const;
		int arg_index(const Expr *arg) const;
		int arg_index(const Expr &arg) const;
		int arg_count(void) const;
		int calc_width(void);
		int calc_height(void);
		int calc_depth(void);
		String &to_str(String &result) const;
	};
}

#endif //CONSOLE_FX_SYMBOL_H
