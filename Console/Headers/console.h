//
// Created by Mike Smith on 2017/2/7.
//

#ifndef CONSOLE_FX_CONSOLE_H
#define CONSOLE_FX_CONSOLE_H

#include "error.h"
#include "message.h"

namespace fx
{
	class Console
	{
	private:
		Message _msg;
		Error _error;
	
	public:
		Console(void);
	};
}

#endif //CONSOLE_FX_CONSOLE_H
