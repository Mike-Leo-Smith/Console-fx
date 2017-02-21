//
// Created by Mike Smith on 2017/2/12.
//

#include "../Headers/symbol.h"
#include "../Headers/expr.h"
#include "../Headers/misc.h"

namespace fx
{
	Symbol::Symbol(Node *parent_node, SymbolType type, const char *c_str) : _type(type), _width(0), _height(0), _depth(0)
	{
		switch (_type)
		{
		case SYMBOL_STR:
			_str = new String(c_str);
			break;
		
		case SYMBOL_ABS:
		case SYMBOL_INTEGRAL:
		case SYMBOL_SQRT:
			_arg_list = new Expr[1];
			_arg_list[0].set_parent(parent_node);
			_arg_list[0].head()->set_symbol(this);
			break;
		
		case SYMBOL_FRAC:
		case SYMBOL_LOG:
		case SYMBOL_POWER:
		case SYMBOL_ROOT:
			_arg_list = new Expr[2];
			_arg_list[0].set_parent(parent_node);
			_arg_list[1].set_parent(parent_node);
			_arg_list[0].head()->set_symbol(this);
			_arg_list[1].head()->set_symbol(this);
			break;
		
		case SYMBOL_DEFINITE:
			_arg_list = new Expr[3];
			_arg_list[0].set_parent(parent_node);
			_arg_list[1].set_parent(parent_node);
			_arg_list[2].set_parent(parent_node);
			_arg_list[0].head()->set_symbol(this);
			_arg_list[1].head()->set_symbol(this);
			_arg_list[2].head()->set_symbol(this);
			break;
		
		case SYMBOL_PRODUCT:
		case SYMBOL_SUM:
			_arg_list = new Expr[4];
			_arg_list[0].set_parent(parent_node);
			_arg_list[1].set_parent(parent_node);
			_arg_list[2].set_parent(parent_node);
			_arg_list[3].set_parent(parent_node);
			_arg_list[0].head()->set_symbol(this);
			_arg_list[1].head()->set_symbol(this);
			_arg_list[2].head()->set_symbol(this);
			_arg_list[3].head()->set_symbol(this);
			break;
		
		case SYMBOL_HEAD:
			_str = NULL;
			break;
		
		default:
			break;
		}
	}
	
	int Symbol::calc_width(void)
	{
		switch (_type)
		{
		case SYMBOL_ABS:
			_width = 2 + _arg_list[0].calc_width() + 2;
			break;
		
		case SYMBOL_DEFINITE:
			_width = 6 + max(_arg_list[1].calc_width(), _arg_list[2].calc_width()) + 1 + _arg_list[0].calc_width() + 2 * FONT_WIDTH;
			break;
		
		case SYMBOL_FRAC:
			_width = 1 + max(_arg_list[0].calc_width(), _arg_list[1].calc_width()) + 1;
			break;
		
		case SYMBOL_INTEGRAL:
			_width = 6 + _arg_list[0].calc_width() + 2 * FONT_WIDTH;
			break;
		
		case SYMBOL_LOG:
			_width = 3 * FONT_WIDTH + _arg_list[0].calc_width() + 4 + _arg_list[1].calc_width() + 4;
			break;
		
		case SYMBOL_POWER:
			_width = _arg_list[0].calc_width() + _arg_list[1].calc_width();
			break;
		
		case SYMBOL_ROOT:
			_width = _arg_list[0].calc_width() + 2 + _arg_list[1].calc_width() + 1;
			break;
		
		case SYMBOL_SQRT:
			_width = 4 + _arg_list[0].calc_width() + 1;
			break;
		
		case SYMBOL_STR:
			_width = (int)_str->size() * FONT_WIDTH;
			break;
		
		case SYMBOL_PRODUCT:
		case SYMBOL_SUM:
			_width = max(_arg_list[1].calc_width() + FONT_WIDTH + _arg_list[2].calc_width(), _arg_list[3].calc_width()) + 4 + _arg_list[0].calc_width() + 4;
			break;
		
		default:
			break;
		}
		
		return _width;
	}
	
	int Symbol::calc_height(void)
	{
		switch (_type)
		{
		case SYMBOL_ABS:
			_height = _arg_list[0].calc_height() + 1;
			break;
		
		case SYMBOL_DEFINITE:
			_height = max(_arg_list[2].calc_height() + _arg_list[2].calc_depth() + FONT_HEIGHT - 2, _arg_list[0].calc_height());
			break;
		
		case SYMBOL_FRAC:
			_height = _arg_list[0].calc_height() + _arg_list[0].calc_depth() + 1;
			break;
		
		case SYMBOL_INTEGRAL:
			_height = 2 + _arg_list[0].calc_height();
			break;
		
		case SYMBOL_LOG:
			_height = _arg_list[1].calc_height();
			break;
		
		case SYMBOL_POWER:
			_height = _arg_list[0].calc_height() + _arg_list[1].calc_height() + _arg_list[1].calc_depth() - 5;
			break;
		
		case SYMBOL_PRODUCT:
			_height = max(_arg_list[3].calc_height() + _arg_list[3].calc_depth() + 4, _arg_list[0].calc_height());
			break;
		
		case SYMBOL_ROOT:
			_height = _arg_list[1].calc_height() + _arg_list[0].calc_height() + _arg_list[0].calc_depth() - FONT_DEPTH;
			break;
		
		case SYMBOL_SQRT:
			_height = _arg_list[0].calc_height() + 2;
			break;
		
		case SYMBOL_STR:
			_height = FONT_HEIGHT;
			break;
		
		case SYMBOL_SUM:
			_height = max(_arg_list[3].calc_height() + _arg_list[3].calc_depth() + 5, _arg_list[0].calc_height());
			break;
		
		default:
			break;
		}
		
		return _height;
	}
	
	int Symbol::calc_depth(void)
	{
		_depth = 0;
		
		switch (_type)
		{
		case SYMBOL_ABS:
			_depth = _arg_list[0].calc_depth() + 1;
			break;
		
		case SYMBOL_DEFINITE:
			_depth = max(_arg_list[1].calc_height() + _arg_list[1].calc_depth(), _arg_list[0].calc_depth());
			break;
		
		case SYMBOL_FRAC:
			_depth = 1 + _arg_list[1].calc_height() + _arg_list[1].calc_depth();
			break;
		
		case SYMBOL_INTEGRAL:
			_depth = _arg_list[0].calc_depth() + 1;
			break;
		
		case SYMBOL_LOG:
			_depth = max(_arg_list[0].calc_height() + _arg_list[0].calc_depth() - 1, _arg_list[1].calc_depth());
			break;
		
		case SYMBOL_POWER:
			_depth = _arg_list[0].calc_depth();
			break;
		
		case SYMBOL_PRODUCT:
			_depth = max(max(_arg_list[1].calc_height() + _arg_list[1].calc_depth(), _arg_list[2].calc_height() + _arg_list[2].calc_depth()) + 4, _arg_list[0].calc_depth());
			break;
		
		case SYMBOL_ROOT:
			_depth = _arg_list[1].calc_depth();
			break;
		
		case SYMBOL_SQRT:
			_depth = _arg_list[0].calc_depth();
			break;
		
		case SYMBOL_STR:
			_depth = FONT_DEPTH;
			break;
		
		case SYMBOL_SUM:
			_depth = max(max(_arg_list[1].calc_height() + _arg_list[1].calc_depth(), _arg_list[2].calc_height() + _arg_list[2].calc_depth()) + 5, _arg_list[0].calc_depth());
			break;
		
		default:
			break;
		}
		
		return _depth;
	}
	
	Symbol::~Symbol(void)
	{
		if (_type == SYMBOL_STR)
		{
			delete _str;
		}
		else
		{
			delete[] _arg_list;
		}
		_arg_list = NULL;
		_width = _height = _depth = 0;
	}
	
	Expr &Symbol::arg(int index) const
	{
		return _arg_list[index];
	}
	
	String &Symbol::to_str(String &result) const
	{
		String partial_result;
		
		result.clear();
		switch (_type)
		{
		case SYMBOL_ABS:
			result.append("abs(").append(_arg_list[0].to_str(partial_result)).append(")");
			break;
		
		case SYMBOL_DEFINITE:
			result.append("defint(").append(_arg_list[0].to_str(partial_result)).append(",x,").append(_arg_list[1].to_str(partial_result)).append(",")
			      .append(_arg_list[2].to_str(partial_result)).append(")");
			break;
		
		case SYMBOL_FRAC:
			result.append("((").append(_arg_list[0].to_str(partial_result)).append(")/(").append(_arg_list[1].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_INTEGRAL:
			result.append("(integral(").append(_arg_list[0].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_LOG:
			result.append("(log(").append(_arg_list[1].to_str(partial_result)).append(")/log(").append(_arg_list[0].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_POWER:
			result.append("((").append(_arg_list[0].to_str(partial_result)).append(")^(").append(_arg_list[1].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_PRODUCT:
			result.append("(product(").append(_arg_list[1].to_str(partial_result)).append(",").append(_arg_list[2].to_str(partial_result)).append(",")
			      .append(_arg_list[3].to_str(partial_result)).append(",").append(_arg_list[0].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_ROOT:
			result.append("((").append(_arg_list[1].to_str(partial_result)).append(")^(1/(").append(_arg_list[0].to_str(partial_result)).append(")))");
			break;
		
		case SYMBOL_SQRT:
			result.append("(sqrt(").append(_arg_list[0].to_str(partial_result)).append("))");
			break;
		
		case SYMBOL_STR:
			result.append(*_str);
			break;
		
		case SYMBOL_SUM:
			result.append("(sum(").append(_arg_list[1].to_str(partial_result)).append(",").append(_arg_list[2].to_str(partial_result)).append(",")
			      .append(_arg_list[3].to_str(partial_result)).append(",").append(_arg_list[0].to_str(partial_result)).append("))");
			break;
		
		default:
			break;
		}
		
		return result;
	}
	
	int Symbol::arg_count(void) const
	{
		int count;
		
		switch (_type)
		{
		case SYMBOL_STR:
			count = 0;
			break;
		
		case SYMBOL_ABS:
		case SYMBOL_INTEGRAL:
		case SYMBOL_SQRT:
			count = 1;
			break;
		
		case SYMBOL_FRAC:
		case SYMBOL_LOG:
		case SYMBOL_POWER:
		case SYMBOL_ROOT:
			count = 2;
			break;
		
		case SYMBOL_DEFINITE:
			count = 3;
			break;
		
		case SYMBOL_PRODUCT:
		case SYMBOL_SUM:
			count = 4;
			break;
		
		default:
			count = 0;
			break;
		}
		
		return count;
	}
	
	int Symbol::arg_index(const Expr *arg) const
	{
		return (int)(arg - _arg_list);
	}
	
	int Symbol::arg_index(const Expr &arg) const
	{
		return (int)(&arg - _arg_list);
	}
}