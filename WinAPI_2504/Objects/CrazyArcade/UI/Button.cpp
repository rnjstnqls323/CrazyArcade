#include "Framework.h"

Button::Button(wstring name, Vector2 pos, Vector2 size) : RectCollider(size)
{
	SetLocalPosition(pos);
	UpdateWorld();
	path = L"Resources/Textures/CrazyArcade_Button/" + name;
	CreateQuads();
}

Button::~Button()
{
	for (Quad* quad : quads)
	{
		delete quad;
	}
	quads.clear();
}

void Button::Update()
{
	
	if (curStatus == Click && Input::Get()->IsKeyDown(VK_LBUTTON)) 
	{
		Audio::Get()->Play(clickSound);
		OnClick();
	}
	else if (IsPointCollision(mousePos))
	{
		curStatus = Click;
		if (!isOnTheButton)
		{
			Audio::Get()->Play("ef_Hover",0.8);
			isOnTheButton = true;
		}
	}
	else
	{
		curStatus = NoneClick;
		isOnTheButton = false;
	}

	UpdateWorld(); //this purpose is only test
	quads[curStatus]->UpdateWorld();
}

void Button::Render()
{
	quads[curStatus]->Render();
	RectCollider::Render();
}

void Button::OnClick()
{
	if (!onClick) return;
	onClick();
}

void Button::CreateQuads()
{
	quads.resize((int)Click+1);
	int count = 0;
	for (Quad*& quad : quads)
	{
		wstring filePath = path + to_wstring(count++)+L".png";
		quad = new Quad(filePath);
		quad->SetParent(this);
		quad->UpdateWorld();
	}
}
