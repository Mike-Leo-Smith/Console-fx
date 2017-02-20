//
// Created by Mike Smith on 2017/2/14.
//

#include "../Headers/line.h"

namespace fx
{
	
	Line::~Line(void)
	{
		if (_expr != NULL)
		{
			delete _expr;
		}
	}
}