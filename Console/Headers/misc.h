//
// Created by Mike Smith on 2017/2/12.
//

#ifndef CONSOLE_FX_MISC_H
#define CONSOLE_FX_MISC_H

namespace fx
{
	template<typename T> inline T abs(const T &x) { return (x > 0) ? x : -x; }
	
	template<typename T> inline const T &max(const T &a, const T &b) { return (a > b) ? a : b; }
	
	template<typename T> inline const T &min(const T &a, const T &b) { return (a < b) ? a : b; }
	
	template<typename T> int sgn(const T &x) { return (x > 0) ? 1 : ((x < 0) ? -1 : 0); }
	
	template<typename T> inline void swap(T &a, T &b)
	{
		T tmp = a;
		a = b, b = tmp;
	}
}

#endif //CONSOLE_FX_MISC_H
