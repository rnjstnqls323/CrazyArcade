#include "Framework.h"

TileMap::TileMap(wstring filePath)
{
	
}

TileMap::~TileMap()
{
	delete backGroundImage;
}

void TileMap::Update()
{
	backGroundImage->UpdateWorld();
	backGroundImage->SetLocalPosition({ CENTER.x - 100,CENTER.y });
}

void TileMap::Render()
{
	backGroundImage->Render();
}

void TileMap::Save()
{
}

void TileMap::Load()
{
}

void TileMap::CreateTile()
{
}

void TileMap::ClearTile()
{
}

void TileMap::SetBackGroundImage(wstring filePath)
{
	if (backGroundImage != nullptr) return;
	backGroundImage = new Quad(filePath);
}
