#include "Framework.h"

Pannel::Pannel()
{
}

Pannel::~Pannel()
{
	for (Button* button : buttons)
	{
		delete button;
	}
	buttons.clear();

	delete backGround;
}