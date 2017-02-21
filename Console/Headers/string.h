//
// Created by Mike Smith on 2017/2/7.
//

#ifndef CONSOLE_FX_STRING_H
#define CONSOLE_FX_STRING_H

#include <cstddef>
#include "config.h"

namespace fx
{
	class String
	{
	private:
		char *_c_str;
		size_t _size;
		size_t _capacity;
	
	public:
		String(size_t capacity = 0);
		String(const char *c_str);
		String(const String &str);
		~String(void);
		
		size_t size(void) const { return _size; }
		const char *c_str(void) const { return _c_str; }
		
		String &clear(void);
		String &append(const char *c_str, size_t str_len = 0);
		String &append(const String &str);
		String &append(char c);
		String &backspace(size_t len = 1);
		String &insert(size_t pos, char c);
		String &insert(size_t pos, const char *c_str);
		String &insert(size_t pos, const String &str);
		String &remove(size_t pos, size_t len = 1);
		
		char operator[](size_t index) const { return (index < _size) ? _c_str[index] : (char)'\0'; }
	};
}

#endif //CONSOLE_FX_STRING_H
