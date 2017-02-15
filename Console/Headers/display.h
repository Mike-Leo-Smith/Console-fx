//
// Created by Mike Smith on 2017/2/12.
//

#ifndef CONSOLE_FX_DISPLAY_H
#define CONSOLE_FX_DISPLAY_H

#include "string.h"
#include "symbol.h"
#include "expr.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH_BYTE 16
#define SCREEN_WIDTH_RSHIFT 4

#define VRAM_SIZE_BYTE 1024

namespace fx
{
	class Display
	{
	private:
		unsigned char *_vram;
	
	public:
		Display(unsigned char *vram) : _vram(vram) {}
		bool on_screen(int x, int y) const { return (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT); }
		const unsigned char *vram(void) { return _vram; }
		bool test_point(int x, int y) { return on_screen(x, y) ? (bool)(_vram[(y << SCREEN_WIDTH_RSHIFT) + (x >> 3)] & (128 >> (x & 7))) : false; }
		void draw_point(int x, int y) { if (on_screen(x, y)) _vram[(y << SCREEN_WIDTH_RSHIFT) + (x >> 3)] |= 128 >> (x & 7); }
		void clear_point(int x, int y) { if (on_screen(x, y)) _vram[(y << SCREEN_WIDTH_RSHIFT) + (x >> 3)] &= ~(128 >> (x & 7)); }
		void reverse_point(int x, int y) { if (on_screen(x, y)) _vram[(y << SCREEN_WIDTH_RSHIFT) + (x >> 3)] ^= 128 >> (x & 7); }
		void draw_bitmap(const unsigned char *bmp, int x, int y, int width, int height);
		void draw_line(int x1, int y1, int x2, int y2);
		void clear_line(int x1, int y1, int x2, int y2);
		void reverse_line(int x1, int y1, int x2, int y2);
		void fill_area(int left, int top, int right, int bottom);
		void clear_area(int left, int top, int right, int bottom);
		void reverse_area(int left, int top, int right, int bottom);
		void fill_all(void);
		void clear_all(void);
		void reverse_all(void);
		void print_char(int code, int left, int top);
		void print_str(const String &str, int left, int top);
		void print_c_str(const char *c_str, int left, int top);
		void print_symbol(const Symbol &symbol, int left, int base);
		void print_expr(const Expr &expr, int left, int base);
	};
}

#endif //CONSOLE_FX_DISPLAY_H
