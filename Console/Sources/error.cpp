//
// Created by Mike Smith on 2017/1/22.
//

#include <cstddef>
#include "../Headers/error.h"

namespace fx
{
	ErrorStack::ErrorStack(void) : _top(-1) {}
	
	void ErrorStack::push(ErrorCode error)
	{
		if (error != ERROR_NO_ERROR && _top < ERROR_STACK_CAPACITY - 1)
			_error[++_top] = error;
	}
	
	ErrorCode ErrorStack::pop(void)
	{
		return (_top >= 0) ? _error[_top--] : ERROR_NO_ERROR;
	}
	
	ErrorCode ErrorStack::top(void) const
	{
		return (_top >= 0) ? _error[_top] : ERROR_NO_ERROR;
	}
	
	bool ErrorStack::empty(void) const
	{
		return (_top == -1);
	}
	
	size_t ErrorStack::size(void) const
	{
		return (size_t)(_top + 1);
	}
	
	void ErrorStack::clear(void)
	{
		_top = -1;
	}
	
	const String Error::last(void)
	{
		switch (_stack.top())
		{
		case ERROR_NO_ERROR:
			return "no error";
		case ERROR_ARGUMENT:
			return "argument error";
		case ERROR_MEMORY:
			return "memory error";
		case ERROR_UNKNOWN:
			return "unknown error";
		default:
			return "unknown error";
		}
	}
	
	const String Error::info(void)
	{
		if (empty())
		{
			return "No error.";
		}
		else
		{
			return String().append("Total: ").append(_stack.size()).append(" error").append(_stack.size() == 1 ? ".\n" : "s.\n").append("Last: ").append(last()).append('.');
		}
	}
	
	void Error::add(ErrorCode error)
	{
		_stack.push(error);
	}
	
	void Error::dispose_last(void)
	{
		if (_stack.top() != ERROR_NO_ERROR)
		{
			_msg->show(last());
		}
		_stack.pop();
	}
	
	void Error::dispose_every(void)
	{
		while (!empty())
		{
			dispose_last();
		}
	}
	
	void Error::dispose_all(void)
	{
		if (!empty())
		{
			_msg->show(info());
		}
		_stack.clear();
	}
	
	bool Error::empty(void)
	{
		return _stack.empty();
	}
	
	Error::Error(Message &msg) : _msg(&msg), _stack() {}
}