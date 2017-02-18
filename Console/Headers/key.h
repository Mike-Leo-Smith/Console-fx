//
// Created by Mike Smith on 2017/2/16.
//

#ifndef CONSOLE_FX_KEY_H
#define CONSOLE_FX_KEY_H

namespace fx
{
	enum ControlCode
	{
		CONTROL_EXE = 0xff00,
		CONTROL_DEL,
		CONTROL_AC,
		CONTROL_UP,
		CONTROL_DOWN,
		CONTROL_LEFT,
		CONTROL_RIGHT
	};
	
	int GetKeycode(void);
}

#endif //CONSOLE_FX_KEY_H
