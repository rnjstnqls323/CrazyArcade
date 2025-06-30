#include "Framework.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	for (Button* button : buttons)
	{
		delete button;
	}
	buttons.clear();

	delete backGround;
}