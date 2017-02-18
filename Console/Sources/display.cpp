//
// Created by Mike Smith on 2017/2/12.
//

#include <cstring>
#include "../Headers/misc.h"
#include "../Headers/display.h"
#include "../Headers/font.h"

namespace fx
{
	void Display::draw_line(int x1, int y1, int x2, int y2)
	{
		if (x1 > x2)
		{
			swap(x1, x2), swap(y1, y2);
		}
		
		int dx = x2 - x1;
		int dy = y2 - y1;
		int f = 0;
		
		if (dy >= 0 && dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				draw_point(x, y);
				
				if ((f + dy) + (f + dy - dx) < 0)
					f += dy;
				else
				{
					f += dy - dx;
					y++;
				}
			}
		}
		else if (dy >= 0 && dy > dx)
		{
			for (int x = x1, y = y1; y <= y2; y++)
			{
				draw_point(x, y);
				
				if ((f - dx) + (f - dx + dy) > 0)
					f += -dx;
				else
				{
					f += -dx + dy;
					x++;
				}
			}
		}
		else if (dy <= 0 && -dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				draw_point(x, y);
				
				if ((f + dy) + (f + dy + dx) > 0)
					f += dy;
				else
				{
					f += dy + dx;
					y--;
				}
			}
		}
		else if (dy <= 0 && -dy > dx)
		{
			for (int x = x1, y = y1; y >= y2; y--)
			{
				draw_point(x, y);
				
				if ((f + dx) + (f + dy + dx) < 0)
					f += dx;
				else
				{
					f += dy + dx;
					x++;
				}
			}
		}
	}
	
	void Display::clear_line(int x1, int y1, int x2, int y2)
	{
		if (x1 > x2)
		{
			swap(x1, x2), swap(y1, y2);
		}
		
		int dx = x2 - x1;
		int dy = y2 - y1;
		int f = 0;
		
		if (dy >= 0 && dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				clear_point(x, y);
				
				if ((f + dy) + (f + dy - dx) < 0)
					f += dy;
				else
				{
					f += dy - dx;
					y++;
				}
			}
		}
		else if (dy >= 0 && dy > dx)
		{
			for (int x = x1, y = y1; y <= y2; y++)
			{
				clear_point(x, y);
				
				if ((f - dx) + (f - dx + dy) > 0)
					f += -dx;
				else
				{
					f += -dx + dy;
					x++;
				}
			}
		}
		else if (dy <= 0 && -dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				clear_point(x, y);
				
				if ((f + dy) + (f + dy + dx) > 0)
					f += dy;
				else
				{
					f += dy + dx;
					y--;
				}
			}
		}
		else if (dy <= 0 && -dy > dx)
		{
			for (int x = x1, y = y1; y >= y2; y--)
			{
				clear_point(x, y);
				
				if ((f + dx) + (f + dy + dx) < 0)
					f += dx;
				else
				{
					f += dy + dx;
					x++;
				}
			}
		}
	}
	
	void Display::reverse_line(int x1, int y1, int x2, int y2)
	{
		if (x1 > x2)
		{
			swap(x1, x2), swap(y1, y2);
		}
		
		int dx = x2 - x1;
		int dy = y2 - y1;
		int f = 0;
		
		if (dy >= 0 && dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				reverse_point(x, y);
				
				if ((f + dy) + (f + dy - dx) < 0)
					f += dy;
				else
				{
					f += dy - dx;
					y++;
				}
			}
		}
		else if (dy >= 0 && dy > dx)
		{
			for (int x = x1, y = y1; y <= y2; y++)
			{
				reverse_point(x, y);
				
				if ((f - dx) + (f - dx + dy) > 0)
					f += -dx;
				else
				{
					f += -dx + dy;
					x++;
				}
			}
		}
		else if (dy <= 0 && -dy <= dx)
		{
			for (int x = x1, y = y1; x <= x2; x++)
			{
				reverse_point(x, y);
				
				if ((f + dy) + (f + dy + dx) > 0)
					f += dy;
				else
				{
					f += dy + dx;
					y--;
				}
			}
		}
		else if (dy <= 0 && -dy > dx)
		{
			for (int x = x1, y = y1; y >= y2; y--)
			{
				reverse_point(x, y);
				
				if ((f + dx) + (f + dy + dx) < 0)
					f += dx;
				else
				{
					f += dy + dx;
					x++;
				}
			}
		}
	}
	
	void Display::fill_area(int left, int top, int right, int bottom)
	{
		if (left > right) swap(left, right);
		if (top > bottom) swap(top, bottom);
		if (left < 0) left = 0;
		if (top < 0) top = 0;
		if (right >= SCREEN_WIDTH) right = SCREEN_WIDTH - 1;
		if (bottom >= SCREEN_HEIGHT) bottom = SCREEN_HEIGHT - 1;
		
		for (int x = left; x <= right; x++)
		{
			for (int y = top; y <= bottom; y++)
			{
				draw_point(x, y);
			}
		}
	}
	
	void Display::clear_area(int left, int top, int right, int bottom)
	{
		if (left > right) swap(left, right);
		if (top > bottom) swap(top, bottom);
		if (left < 0) left = 0;
		if (top < 0) top = 0;
		if (right >= SCREEN_WIDTH) right = SCREEN_WIDTH - 1;
		if (bottom >= SCREEN_HEIGHT) bottom = SCREEN_HEIGHT - 1;
		
		for (int x = left; x <= right; x++)
		{
			for (int y = top; y <= bottom; y++)
			{
				clear_point(x, y);
			}
		}
	}
	
	void Display::reverse_area(int left, int top, int right, int bottom)
	{
		if (left > right) swap(left, right);
		if (top > bottom) swap(top, bottom);
		if (left < 0) left = 0;
		if (top < 0) top = 0;
		if (right >= SCREEN_WIDTH) right = SCREEN_WIDTH - 1;
		if (bottom >= SCREEN_HEIGHT) bottom = SCREEN_HEIGHT - 1;
		
		for (int x = left; x <= right; x++)
		{
			for (int y = top; y <= bottom; y++)
			{
				reverse_point(x, y);
			}
		}
	}
	
	void Display::fill_all(void)
	{
		memset(_vram, 0xff, VRAM_SIZE_BYTE);
	}
	
	void Display::clear_all(void)
	{
		memset(_vram, 0x00, VRAM_SIZE_BYTE);
	}
	
	void Display::reverse_all(void)
	{
		for (int i = 0; i < VRAM_SIZE_BYTE; i++)
		{
			_vram[i] ^= 0xff;
		}
	}
	
	void Display::draw_bitmap(const unsigned char *bmp, int x, int y, int width, int height)
	{
		for (int xi = 0; xi < width; xi++)
		{
			for (int yi = 0; yi < height; yi++)
			{
				if (bmp[yi * (((width - 1) >> 3) + 1) + (xi >> 3)] & (1 << (7 - (xi & 7)))) draw_point(x + xi, y + yi);
			}
		}
	}
	
	void Display::print_char(int code, int left, int top)
	{
		if (!(code & ~0xff))
		{
			if (code != '\n')
			{
				draw_bitmap(GetFontBitmap(code), left, top, FONT_WIDTH, FONT_HEIGHT + FONT_DEPTH);
			}
		}
	}
	
	void Display::print_str(const String &str, int left, int top)
	{
		const char *ptr = str.c_str();
		
		while (*ptr != '\0' && left < SCREEN_WIDTH)
		{
			print_char(*ptr, left, top);
			ptr++;
			left += FONT_WIDTH;
		}
	}
	
	void Display::print_c_str(const char *c_str, int left, int top)
	{
		const char *ptr = c_str;
		
		while (*ptr != '\0' && left < SCREEN_WIDTH)
		{
			print_char(*ptr, left, top);
			left += FONT_WIDTH;
			ptr++;
		}
	}
	
	void Display::print_symbol(const Symbol &symbol, int left, int base)
	{
		switch (symbol.type())
		{
		case SYMBOL_ABS:
		{
			int w = symbol.width();
			int h = symbol.height();
			int d = symbol.depth();
			
			draw_line(left + 1, base - h + 1, left + 1, base + d - 1);
			print_expr(symbol.arg(0), left + 2, base);
			draw_line(left + w - 1, base - h + 1, left + w - 1, base + d - 1);
			break;
		}
		
		case SYMBOL_DEFINITE:
		{
			int w = symbol.width();
			int h = symbol.height();
			int d = symbol.depth();
			int w0 = symbol.arg(0).width();
			int d1 = symbol.arg(1).depth();
			int h2 = symbol.arg(2).height();
			
			draw_point(left + 5, base - h + 2);
			draw_point(left + 4, base - h + 1);
			draw_line(left + 3, base - h + 2, left + 3, base + d - 2);
			draw_point(left + 2, base + d - 1);
			draw_point(left + 1, base + d - 2);
			print_expr(symbol.arg(2), left + 6, base - h + h2);
			print_expr(symbol.arg(1), left + 6, base + d - d1);
			print_expr(symbol.arg(0), left + w - 2 * FONT_WIDTH - w0, base);
			print_c_str("dx", left + w - 2 * FONT_WIDTH, base - FONT_HEIGHT + 1);
			break;
		}
		
		case SYMBOL_FRAC:
		{
			int w = symbol.width();
			int w0 = symbol.arg(0).width();
			int w1 = symbol.arg(1).width();
			int w0_w1_max = max(w0, w1);
			int d0 = symbol.arg(0).depth();
			int h1 = symbol.arg(1).height();
			
			draw_line(left + 1, base, left + w - 1, base);
			print_expr(symbol.arg(0), left + 1 + ((w0_w1_max - w0) >> 1), base - 1 - d0);
			print_expr(symbol.arg(1), left + 1 + ((w0_w1_max - w1) >> 1), base + 1 + h1);
			break;
		}
		
		case SYMBOL_INTEGRAL:
		{
			int w = symbol.width();
			int h = symbol.height();
			int d = symbol.depth();
			
			draw_point(left + 5, base - h + 2);
			draw_point(left + 4, base - h + 1);
			draw_line(left + 3, base - h + 2, left + 3, base + d - 2);
			draw_point(left + 2, base + d - 1);
			draw_point(left + 1, base + d - 2);
			print_expr(symbol.arg(0), left + 6, base);
			print_c_str("dx", left + w - 2 * FONT_WIDTH, base - FONT_HEIGHT + 1);
			break;
		}
		
		case SYMBOL_LOG:
		{
			int w = symbol.width();
			int w0 = symbol.arg(0).width();
			int h0 = symbol.arg(0).height();
			int h1 = symbol.arg(1).height();
			int d1 = symbol.arg(1).depth();
			
			print_c_str("log", left, base - FONT_HEIGHT + 1);
			print_expr(symbol.arg(0), left + 3 * FONT_WIDTH, base + h0 - 1);
			draw_line(left + 3 * FONT_WIDTH + w0 + 1, base - h1 + 3, left + 3 * FONT_WIDTH + w0 + 1, base + d1 - 3);
			draw_point(left + 3 * FONT_WIDTH + w0 + 2, base - h1 + 2);
			draw_point(left + 3 * FONT_WIDTH + w0 + 2, base + d1 - 2);
			draw_point(left + 3 * FONT_WIDTH + w0 + 3, base - h1 + 1);
			draw_point(left + 3 * FONT_WIDTH + w0 + 3, base + d1 - 1);
			print_expr(symbol.arg(1), left + 3 * FONT_WIDTH + w0 + 4, base);
			draw_line(left + w - 1, base - h1 + 3, left + w - 1, base + d1 - 3);
			draw_point(left + w - 2, base - h1 + 2);
			draw_point(left + w - 3, base - h1 + 1);
			draw_point(left + w - 2, base + d1 - 2);
			draw_point(left + w - 3, base + d1 - 1);
			break;
		}
		
		case SYMBOL_POWER:
		{
			int h = symbol.height();
			int w0 = symbol.arg(0).width();
			int h1 = symbol.arg(1).height();
			
			print_expr(symbol.arg(0), left, base);
			print_expr(symbol.arg(1), left + w0, base - h + h1);
			break;
		}
		
		case SYMBOL_PRODUCT:
		{
			int w = symbol.width();
			int w0 = symbol.arg(0).width();
			int h0 = symbol.arg(0).height();
			int d0 = symbol.arg(0).depth();
			int w1 = symbol.arg(1).width();
			int h1 = symbol.arg(1).height();
			int w2 = symbol.arg(2).width();
			int h2 = symbol.arg(2).height();
			int w1_w2_sum = w1 + FONT_WIDTH + w2;
			int h1_h2_max = max(h1, h2);
			int w3 = symbol.arg(3).width();
			int d3 = symbol.arg(3).depth();
			int w1_w2_sum_w3_max = max(w1_w2_sum, w3);
			
			print_expr(symbol.arg(3), left + ((w1_w2_sum_w3_max - w3) >> 1), base - 4 - d3);
			print_expr(symbol.arg(1), left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1), base + 4 + h1_h2_max);
			print_char('=', left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1) + w1, base + 4 + h1_h2_max - FONT_HEIGHT + 1);
			print_expr(symbol.arg(2), left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1) + w1 + FONT_WIDTH, base + 4 + h1_h2_max);
			
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 4, base - 3, left + (w1_w2_sum_w3_max >> 1) + 3, base - 3);
			draw_point(left + (w1_w2_sum_w3_max >> 1) + 4, base - 2);
			draw_line(left + (w1_w2_sum_w3_max >> 1) + 2, base - 3, left + (w1_w2_sum_w3_max >> 1) + 2, base + 3);
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 2, base - 3, left + (w1_w2_sum_w3_max >> 1) - 2, base + 2);
			draw_point(left + (w1_w2_sum_w3_max >> 1) - 3, base + 3);
			
			draw_line(left + w - 1, base - h0 + 3, left + w - 1, base + d0 - 3);
			draw_point(left + w - 2, base - h0 + 2);
			draw_point(left + w - 3, base - h0 + 1);
			draw_point(left + w - 2, base + d0 - 2);
			draw_point(left + w - 3, base + d0 - 1);
			print_expr(symbol.arg(0), left + w - 4 - w0, base);
			draw_line(left + w - 4 - w0 - 3, base - h0 + 3, left + w - 4 - w0 - 3, base + d0 - 3);
			draw_point(left + w - 4 - w0 - 2, base - h0 + 2);
			draw_point(left + w - 4 - w0 - 1, base - h0 + 1);
			draw_point(left + w - 4 - w0 - 2, base + d0 - 2);
			draw_point(left + w - 4 - w0 - 1, base + d0 - 1);
			break;
		}
		
		case SYMBOL_ROOT:
		{
			int w = symbol.width();
			int h = symbol.height();
			int d = symbol.depth();
			int h0 = symbol.arg(0).height();
			int w0 = symbol.arg(0).width();
			int h1 = symbol.arg(1).height();
			
			print_expr(symbol.arg(0), left, base - h + h0);
			draw_point(left + w0 - 1, base + d - 3);
			draw_point(left + w0, base + d - 2);
			draw_line(left + w0 + 1, base + d - 1, left + w0 + 1, base - h1 - 1);
			draw_line(left + w0 + 2, base - h1 - 1, left + w - 1, base - h1 - 1);
			print_expr(symbol.arg(1), left + w0 + 2, base);
			break;
		}
		
		case SYMBOL_SQRT:
		{
			int w = symbol.width();
			int h = symbol.height();
			int d = symbol.depth();
			
			draw_point(left + 1, base + d - 3);
			draw_point(left + 2, base + d - 2);
			draw_line(left + 3, base + d - 1, left + 3, base - h + 1);
			draw_line(left + 4, base - h + 1, left + w - 1, base - h + 1);
			print_expr(symbol.arg(0), left + 4, base);
			break;
		}
		
		case SYMBOL_STR:
		{
			print_str(symbol.str(), left, base - FONT_HEIGHT + 1);
			break;
		}
		
		case SYMBOL_SUM:
		{
			int w = symbol.width();
			int w0 = symbol.arg(0).width();
			int h0 = symbol.arg(0).height();
			int d0 = symbol.arg(0).depth();
			int w1 = symbol.arg(1).width();
			int h1 = symbol.arg(1).height();
			int w2 = symbol.arg(2).width();
			int h2 = symbol.arg(2).height();
			int w1_w2_sum = w1 + FONT_WIDTH + w2;
			int h1_h2_max = max(h1, h2);
			int w3 = symbol.arg(3).width();
			int d3 = symbol.arg(3).depth();
			int w1_w2_sum_w3_max = max(w1_w2_sum, w3);
			
			print_expr(symbol.arg(3), left + ((w1_w2_sum_w3_max - w3) >> 1), base - 5 - d3);
			print_expr(symbol.arg(1), left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1), base + 5 + h1_h2_max);
			print_char('=', left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1) + w1, base + 5 + h1_h2_max - FONT_HEIGHT + 1);
			print_expr(symbol.arg(2), left + ((w1_w2_sum_w3_max - w1_w2_sum) >> 1) + w1 + FONT_WIDTH, base + 5 + h1_h2_max);
			
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 4, base - 4, left + (w1_w2_sum_w3_max >> 1) + 3, base - 4);
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 4, base + 4, left + (w1_w2_sum_w3_max >> 1) + 3, base + 4);
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 3, base - 3, left + (w1_w2_sum_w3_max >> 1), base);
			draw_line(left + (w1_w2_sum_w3_max >> 1) - 1, base + 1, left + (w1_w2_sum_w3_max >> 1) - 3, base + 3);
			draw_point(left + (w1_w2_sum_w3_max >> 1) + 4, base - 3);
			draw_point(left + (w1_w2_sum_w3_max >> 1) + 4, base + 3);
			
			draw_line(left + w - 1, base - h0 + 3, left + w - 1, base + d0 - 3);
			draw_point(left + w - 2, base - h0 + 2);
			draw_point(left + w - 3, base - h0 + 1);
			draw_point(left + w - 2, base + d0 - 2);
			draw_point(left + w - 3, base + d0 - 1);
			print_expr(symbol.arg(0), left + w - 4 - w0, base);
			draw_line(left + w - 4 - w0 - 3, base - h0 + 3, left + w - 4 - w0 - 3, base + d0 - 3);
			draw_point(left + w - 4 - w0 - 2, base - h0 + 2);
			draw_point(left + w - 4 - w0 - 1, base - h0 + 1);
			draw_point(left + w - 4 - w0 - 2, base + d0 - 2);
			draw_point(left + w - 4 - w0 - 1, base + d0 - 1);
			break;
		}
		
		default:
			break;
		}
	}
	
	void Display::print_expr(const Expr &expr, int left, int base)
	{
		int x_offset = 0;
		Node *ptr = expr.head()->next();
		
		if (ptr == NULL)
		{
			if (_cursor->status() == CURSOR_EDITING && _cursor->visible() && _cursor->curr_node() == expr.head())
			{
				draw_cursor(left, base, FONT_HEIGHT, FONT_DEPTH);
			}
			
			draw_line(left + 1, base - FONT_HEIGHT + 1, left + 1, base + FONT_DEPTH - 1);
			draw_line(left + 1, base - FONT_HEIGHT + 1, left + FONT_WIDTH - 1, base - FONT_HEIGHT + 1);
			draw_line(left + FONT_WIDTH - 1, base - FONT_HEIGHT + 1, left + FONT_WIDTH - 1, base + FONT_DEPTH - 1);
			draw_line(left + 1, base + FONT_DEPTH - 1, left + FONT_WIDTH - 1, base + FONT_DEPTH - 1);
		}
		else
		{
			if (_cursor->status() == CURSOR_EDITING && _cursor->visible() && _cursor->curr_node() == expr.head())
			{
				draw_cursor(left, base, ptr->symbol()->height(), ptr->symbol()->depth());
			}
			
			while (ptr != NULL)
			{
				if (_cursor->status() == CURSOR_EDITING && _cursor->visible() && ptr == _cursor->curr_node())
				{
					if (ptr->symbol()->type() == SYMBOL_STR)
					{
						draw_cursor(left + x_offset + _cursor->pos() * FONT_WIDTH, base, FONT_HEIGHT, FONT_DEPTH);
					}
					else
					{
						draw_cursor(left + x_offset + ptr->symbol()->width(), base, ptr->symbol()->height(), ptr->symbol()->depth());
					}
				}
				
				print_symbol(*(ptr->symbol()), left + x_offset, base);
				x_offset += ptr->symbol()->width();
				ptr = ptr->next();
			}
		}
	}
	
	void Display::draw_cursor(int left, int base, int height, int depth)
	{
		_cursor->set_left(left);
		_cursor->set_top(base - height + 1);
		_cursor->set_length(height + depth - 1);
		fill_area(_cursor->left(), _cursor->top(), _cursor->left() + 1, _cursor->top() + _cursor->length() - 1);
	}
	
	void Display::print_line(const Line &line, int top)
	{
		if (_cursor->curr_line() == &line || line.offset() + top + line.expr()->height() + line.expr()->depth() > 0)
		{
			print_expr(*line.expr(), line.scroll(), top + line.expr()->height() - 1);
			
			if (_cursor->status() == CURSOR_SELECTING && _cursor->curr_line() == &line)
			{
				reverse_area(line.scroll(), top, line.scroll() + line.expr()->width() - 1, top + line.expr()->height() + line.expr()->depth() - 1);
			}
		}
	}
}