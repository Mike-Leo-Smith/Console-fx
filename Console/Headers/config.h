//
// Created by Mike Smith on 2017/2/16.
//

#ifndef CONSOLE_FX_CONFIG_H
#define CONSOLE_FX_CONFIG_H

#define SCREEN_WIDTH        512
#define SCREEN_HEIGHT       256
#define SCREEN_WIDTH_BYTE   ((SCREEN_WIDTH + 7) >> 3)
#define VRAM_SIZE_BYTE      (SCREEN_WIDTH_BYTE * SCREEN_HEIGHT)

#define FONT_WIDTH      6
#define FONT_HEIGHT     4
#define FONT_DEPTH      4
#define FONT_SIZE_BYTE  8

#define LINE_QUEUE_CAPACITY     256
#define STRING_CAPACITY_BLOCK   8

#endif //CONSOLE_FX_CONFIG_H
