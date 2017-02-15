//
// Created by Mike Smith on 2017/1/22.
//

#ifndef CONSOLE_FX_ERROR_H
#define CONSOLE_FX_ERROR_H

#include "string.h"
#include "message.h"

#define ERROR_STACK_CAPACITY 16

namespace fx
{
	enum ErrorCode
	{
		ERROR_NO_ERROR,
		ERROR_MEMORY,
		ERROR_ARGUMENT,
		ERROR_UNKNOWN
	};
	
	class ErrorStack
	{
	private:
		ErrorCode _error[ERROR_STACK_CAPACITY];
		int _top;
	
	public:
		ErrorStack(void);
		void push(ErrorCode error);
		ErrorCode pop(void);
		ErrorCode top(void) const;
		void clear(void);
		bool empty(void) const;
		size_t size(void) const;
	};
	
	class Error
	{
	private:
		Message *_msg;
		ErrorStack _stack;
		const String last(void);
		const String info(void);
	
	public:
		Error(Message &msg);
		void add(ErrorCode error);
		bool empty(void);
		void dispose_last(void);
		void dispose_every(void);
		void dispose_all(void);
	};
}

#endif //CONSOLE_FX_ERROR_H
