//
// Created by Mike Smith on 2017/2/7.
//

#include <cstring>
#include <cstdio>
#include <iostream>
#include "../Headers/string.h"
#include "../Headers/misc.h"

namespace fx
{
	// Default constructor.
	String::String(size_t capacity) : _size(0)
	{
		_capacity = (capacity / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		_c_str = new char[_capacity]; // Allocate space.
		_c_str[0] = '\0';     // Make sure that _c_str is properly ended.
	}
	
	// Copy construction from another string. Note that str._c_str is copied.
	String::String(const String &str) : _size(str._size), _capacity(str._capacity)
	{
		// Allocate space and copy.
		_c_str = new char[_capacity];
		memmove(_c_str, str._c_str, _size + 1);
	}
	
	// Copy construction from a C-style string. Note that c_str is copied.
	String::String(const char *c_str) : _size(strlen(c_str))
	{
		// Calculate capacity, rounded to avoid fragmentation.
		_capacity = (_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		
		// Allocate space and copy.
		_c_str = new char[_capacity];
		memmove(_c_str, c_str, _size + 1);
	}
	
	// Destructor.
	String::~String(void)
	{
		// Free the space allocated.
		delete[] _c_str;
		
		_c_str = NULL;
		_size = 0;
		_capacity = 0;
	}
	
	// Clear the string.
	String &String::clear(void)
	{
		// Shrink if allocated too much space.
		if (_capacity > STRING_CAPACITY_BLOCK)
		{
			// Free the old space.
			delete[] _c_str;
			
			// Update Attributes.
			_capacity = STRING_CAPACITY_BLOCK;
			_c_str = new char[_capacity];
			_c_str[0] = '\0';
			_size = 0;
		}
		else    // Otherwise, just blind all the chars.
		{
			_c_str[0] = '\0';
			_size = 0;
		}
		
		return *this;
	}
	
	// Delete the last few chars at the length of len.
	String &String::backspace(size_t len)
	{
		if (len <= 0 || _size == 0)
		{
			return *this;
		}
		
		// Avoid underflow.
		if (len > _size)
		{
			len = _size;
		}
		
		// Calculate new attributes.
		size_t new_size = _size - len;
		size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		
		if (new_capacity <= (_capacity >> 1))   // Too much space, need to shrink.
		{
			// Allocate new space and copy.
			char *new_c_str = new char[new_capacity];
			memmove(new_c_str, _c_str, new_size);
			new_c_str[new_size] = '\0';
			
			// Free old space.
			delete[] _c_str;
			
			// Update Attributes.
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else    // Blind the last chars directly.
		{
			_c_str[new_size] = '\0';
			_size = new_size;
		}
		
		return *this;
	}
	
	// Append the string by duplicating the last char.
	String &String::append(void)
	{
		if (_size > 0)
		{
			append(_c_str[_size - 1]);
		}
		
		return *this;
	}
	
	// Append the string by a C-style string.
	String &String::append(const char *c_str)
	{
		size_t len = strlen(c_str);
		size_t new_size = _size + len;
		
		if (new_size >= _capacity)
		{
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
			char *new_c_str = new char[new_capacity];
			
			memmove(new_c_str, _c_str, _size);
			memmove(new_c_str + _size, c_str, len + 1);
			delete[] _c_str;
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else
		{
			memmove(_c_str + _size, c_str, len + 1);
			_size = new_size;
		}
		
		return *this;
	}
	
	// Append the string with another string.
	String &String::append(const String &str)
	{
		// Calculate new size.
		size_t new_size = _size + str._size;
		
		if (new_size >= _capacity)     // No enough space to hold the new string.
		{
			// Calculate new capacity and allocate new space.
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;   // Rounded to eliminate fragmentation.
			char *new_c_str = new char[new_capacity];
			
			// Copy the two strings into a new space
			memmove(new_c_str, _c_str, _size);
			memmove(new_c_str + _size, str._c_str, str._size + 1);  // Plus 1 to rhs._size to ensure the end '\0' is copied.
			
			// Free the old space.
			delete[] _c_str;
			
			// Update attributes.
			_c_str = new_c_str;
			_capacity = new_capacity;
			_size = new_size;
		}
		else    // Enough space.
		{
			// Copy rhs._c_str directly. Plus 1 to ensure _c_str properly ended.
			memmove(_c_str + _size, str._c_str, str._size + 1);
			
			// Update attributes.
			_size = new_size;
		}
		
		return *this;
	}
	
	// Append the string with a char.
	String &String::append(char c)
	{
		if (_size + 1 >= _capacity)  // No enough space.
		{
			// Expand the capacity twice as before and allocate new space.
			size_t new_capacity = _capacity << 1;
			char *new_c_str = new char[new_capacity];
			
			// Copy into the new space.
			memmove(new_c_str, _c_str, _size);
			new_c_str[_size] = c;
			new_c_str[_size + 1] = '\0';
			
			// Free the space allocated before.
			delete[] _c_str;
			
			// Update Attributes
			_c_str = new_c_str;
			_capacity = new_capacity;
			_size++;
		}
		else    // Enough space.
		{
			// Append the string directly and make sure it properly ended.
			_c_str[_size] = c;
			_c_str[_size + 1] = '\0';
			
			// Update _size;
			_size++;
		}
		
		return *this;
	}
	
	// Append the string with an int.
	String &String::append(int num)
	{
		char tmp[30];
		
		sprintf(tmp, "%d", num);
		return append(tmp);
	}
	
	// Append the string with an unsigned int.
	String &String::append(unsigned int num)
	{
		char tmp[30];
		
		sprintf(tmp, "%u", num);
		return append(tmp);
	}
	
	// Append the string with a long int.
	String &String::append(long num)
	{
		char tmp[30];
		
		sprintf(tmp, "%ld", num);
		return append(tmp);
	}
	
	// Append the string with an unsigned long int.
	String &String::append(unsigned long num)
	{
		char tmp[30];
		
		sprintf(tmp, "%lu", num);
		return append(tmp);
	}
	
	// Append the string with a double.
	String &String::append(double num)
	{
		char tmp[30];
		
		sprintf(tmp, "%lf", num);
		return append(tmp);
	}
	
	// Duplicate the string several times. Note that (times == 1) returns the string itself, and (times == 0) means clear the string.
	String &String::duplicate(int times)
	{
		if (times <= 1)
		{
			if (times == 0)
			{
				clear();
			}
		}
		else
		{
			// Calculate new attributes.
			size_t new_size = _size * times;
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
			
			if (_capacity < new_capacity)   // No enough space.
			{
				// Allocate new space.
				char *new_c_str = new char[new_capacity];
				
				// Copy into new space.
				for (int i = 0; i < times; i++)
				{
					memmove(new_c_str + i * _size, _c_str, _size);
				}
				new_c_str[new_size] = '\0';
				
				// Free the previously allocated space.
				delete[] _c_str;
				
				// Update attributes.
				_c_str = new_c_str;
				_capacity = new_capacity;
				_size = new_size;
			}
			else    // Enough space.
			{
				// Copy.
				for (int i = 1; i < times; i++)
				{
					memmove(_c_str + i * _size, _c_str, _size);
				}
				_c_str[new_size] = '\0';
				
				// Update attributes.
				_size = new_size;
			}
		}
		
		return *this;
	}
	
	String &String::operator=(const String &str)
	{
		char *new_c_str = new char[str._capacity];
		
		memmove(new_c_str, str._c_str, str._size + 1);
		delete[] _c_str;
		_c_str = new_c_str;
		_size = str._size;
		_capacity = str._capacity;
		
		return *this;
	}
	
	String &String::operator=(const char *c_str)
	{
		size_t new_size = strlen(c_str);
		size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		char *new_c_str = new char[new_capacity];
		
		memmove(new_c_str, c_str, new_size + 1);
		delete[] _c_str;
		_c_str = new_c_str;
		_size = new_size;
		_capacity = new_capacity;
		
		return *this;
	}
	
	String &String::insert(size_t pos, char c)
	{
		if (pos > _size)
		{
			pos = _size;
		}
		
		size_t new_size = _size + 1;
		
		if (new_size >= _capacity)
		{
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
			char *new_c_str = new char[new_capacity];
			
			memmove(new_c_str, _c_str, pos);
			new_c_str[pos] = c;
			memmove(new_c_str + pos + 1, _c_str + pos, _size - pos + 1);
			
			delete[] _c_str;
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else
		{
			memmove(_c_str + pos + 1, _c_str + pos, _size - pos + 1);
			_c_str[pos] = c;
			_size++;
		}
		
		return *this;
	}
	
	String &String::insert(size_t pos, const char *c_str)
	{
		if (pos > _size)
		{
			pos = _size;
		}
		
		size_t len = strlen(c_str);
		size_t new_size = _size + len;
		
		if (new_size >= _capacity)
		{
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
			char *new_c_str = new char[new_capacity];
			
			memmove(new_c_str, _c_str, pos);
			memmove(new_c_str + pos, c_str, len);
			memmove(new_c_str + pos + len, _c_str + pos, _size - pos + 1);
			
			delete[] _c_str;
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else
		{
			memmove(_c_str + pos + len, _c_str + pos, _size - pos + 1);
			memmove(_c_str + pos, c_str, len);
			_size = new_size;
		}
		
		return *this;
	}
	
	String &String::insert(size_t pos, const String &str)
	{
		if (pos > _size)
		{
			pos = _size;
		}
		
		size_t new_size = _size + str._size;
		
		if (new_size >= _capacity)
		{
			size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
			char *new_c_str = new char[new_capacity];
			
			memmove(new_c_str, _c_str, pos);
			memmove(new_c_str + pos, str._c_str, str._size);
			memmove(new_c_str + pos + str._size, _c_str + pos, _size - pos + 1);
			
			delete[] _c_str;
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else
		{
			memmove(_c_str + pos + str._size, _c_str + pos, _size - pos + 1);
			memmove(_c_str + pos, str._c_str, str._size);
			_size = new_size;
		}
		
		return *this;
	}
	
	String &String::reverse(void)
	{
		for (size_t i = 0; i < (_size >> 1); i++)
		{
			swap(_c_str[i], _c_str[_size - 1 - i]);
		}
		
		return *this;
	}
	
	String &String::remove(size_t pos, size_t len)
	{
		if (pos >= _size || len == 0 || _size == 0)
		{
			return *this;
		}
		
		if (_size - pos < len)
		{
			len = _size - pos;
		}
		
		size_t new_size = _size - len;
		size_t new_capacity = (new_size / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		
		if (new_capacity <= (_capacity >> 1))
		{
			char *new_c_str = new char[new_capacity];
			
			memmove(new_c_str, _c_str, pos);
			memmove(new_c_str + pos, _c_str + pos + len, _size - pos - len + 1);
			
			delete[] _c_str;
			_c_str = new_c_str;
			_size = new_size;
			_capacity = new_capacity;
		}
		else
		{
			memmove(_c_str + pos, _c_str + pos + len, _size - len - pos + 1);
			_size = new_size;
		}
		
		return *this;
	}
	
	String &String::split(size_t pos, String &part1, String &part2)
	{
		if (&part1 == &part2)
		{
			return *this;
		}
		
		if (pos > _size)
		{
			pos = _size;
		}
		
		size_t new_size_1 = pos;
		size_t new_size_2 = _size - pos;
		size_t new_capacity_1 = (new_size_1 / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		size_t new_capacity_2 = (new_size_2 / STRING_CAPACITY_BLOCK + 1) * STRING_CAPACITY_BLOCK;
		
		char *new_c_str_1 = new char[new_capacity_1];
		char *new_c_str_2 = new char[new_capacity_2];
		
		memmove(new_c_str_1, _c_str, new_size_1);
		new_c_str_1[new_size_1] = '\0';
		memmove(new_c_str_2, _c_str + pos, new_size_2 + 1);
		
		delete[] part1._c_str;
		delete[] part2._c_str;
		part1._c_str = new_c_str_1;
		part2._c_str = new_c_str_2;
		part1._size = new_size_1;
		part2._size = new_size_2;
		part1._capacity = new_capacity_1;
		part2._capacity = new_capacity_2;
		
		return *this;
	}
}