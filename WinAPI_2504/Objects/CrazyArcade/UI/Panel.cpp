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
void Panel::Update(Player* player)
{
	for (Button* button : buttons)
	{
		button->Update();
	}
}
void Panel::Render()
{
	backGround->Render();
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void Panel::CreateButton(wstring fileName, Vector2 pos, Vector2 size)
{
	Button* button = new Button(fileName, pos, size);
	button->SetParent(this);
	button->UpdateWorld();
	buttons.push_back(button);
}