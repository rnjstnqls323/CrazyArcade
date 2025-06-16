#include "Framework.h"

EditTile::EditTile()
{
	image = new Quad(L"Resources/Textures/CrazyArcade_BG_Texture/NoneBlock.png");
	image->SetParent(this);
}

EditTile::~EditTile()
{
	delete image;
}

void EditTile::Update()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();
}

void EditTile::Render()
{
	image->Render();
	RectCollider::Render();
}

