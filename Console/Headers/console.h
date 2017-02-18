//
// Created by Mike Smith on 2017/2/7.
//

#ifndef CONSOLE_FX_CONSOLE_H
#define CONSOLE_FX_CONSOLE_H

#include "config.h"
#include "string.h"
#include "line.h"
#include "cursor.h"
#include "display.h"
#include "key.h"

namespace fx
{
	class Console
	{
	private:
		int _line_start;
		int _line_end;
		Line *_line_queue[LINE_QUEUE_CAPACITY];
		Cursor _cursor;
		Display _display;
		int _offset;
		
		void pop_line(void);
		Line *add_line(LineType type, bool editable);
		
		void render(void);
	
	public:
		Console(unsigned char *vram);
		~Console(void);
		String &input(String &str_input);
		void output(const String &str_output);
	};
}

#endif //CONSOLE_FX_CONSOLE_H
