//
// Created by Mike Smith on 2017/2/12.
//

#ifndef CONSOLE_FX_FONT_H
#define CONSOLE_FX_FONT_H

#define FONT_WIDTH 6
#define FONT_HEIGHT 4
#define FONT_DEPTH 4
#define FONT_SIZE_BYTE 8

namespace fx
{
	const unsigned char *GetFontBitmap(int code = 0);
}

#endif //CONSOLE_FX_FONT_H
