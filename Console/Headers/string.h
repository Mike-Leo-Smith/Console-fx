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
		String &append(void);
		String &append(const char *c_str);
		String &append(const String &str);
		String &append(char c);
		String &append(int num);
		String &append(unsigned int num);
		String &append(long num);
		String &append(unsigned long num);
		String &append(double num);
		String &backspace(size_t len = 1);
		String &duplicate(int times = 2);
		String &insert(size_t pos, char c);
		String &insert(size_t pos, const char *c_str);
		String &insert(size_t pos, const String &str);
		String &remove(size_t pos, size_t len = 1);
		String &reverse(void);
		String &split(size_t pos, String &part1, String &part2);
		
		String &operator=(const String &str);
		String &operator=(const char *c_str);
		String &operator--(void) { return backspace(); }
		String &operator++(void) { return append(); }
		String &operator*=(int rhs) { return duplicate(rhs); }
		char operator[](size_t index) const { return (index < _size) ? _c_str[index] : (char)'\0'; }
		template<typename T> String &operator+=(const T &rhs) { return append(rhs); }
		const String operator*(int rhs) const { return String(*this).duplicate(rhs); }
		template<typename Tl, typename Tr> friend const String operator+(const Tl &lhs, const Tr &rhs) { return String().append(lhs).append(rhs); }
	};
}

#endif //CONSOLE_FX_STRING_H
