#include "Framework.h"
#include "MapEditScene.h"

MapEditScene::MapEditScene()
{
	CreateEditTiles();
	quad = new Quad(L"Resources/Textures/CrazyArcade_BG/blocks.png");
	
	quad->SetLocalPosition(CENTER);
	quad->UpdateWorld();
}

MapEditScene::~MapEditScene()
{
	for (Tile* tile : tiles)
	{
		delete tile;
	}
	delete quad;
}

void MapEditScene::Update()
{
	MoveTiles();
	for (Tile* tile : tiles)
	{
		
		tile->UpdateWorld();
	}
	
	quad->UpdateWorld();
}

void MapEditScene::Render()
{
	quad->Render();

	for (Tile* tile : tiles)
	{
		tile->Render();
	}
	
}

void MapEditScene::GUIRender()
{
	//tiles[0]->Edit();
	quad->Edit();
}

void MapEditScene::EditBgTiles()
{
	
	
}

void MapEditScene::RenderSampleButtons()
{
}

void MapEditScene::CreateEditTiles()
{

	Vector2 startPos = Vector2(TILE_SIZE.x * 0.5f, SCREEN_HEIGHT - TILE_SIZE.y * 0.5f);

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			Tile* tile = new Tile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();
			tiles.push_back(tile);
		}
	}
}

void MapEditScene::DeleteEditTiles()
{
}

void MapEditScene::LoadTextures()
{
}

void MapEditScene::Save(string file)
{
}

void MapEditScene::Load(string file)
{
}

void MapEditScene::SaveDialog()
{
}

void MapEditScene::LoadDialog()
{
}

void MapEditScene::MoveTiles()
{
	Vector2 startPos = tiles[0]->GetLocalPosition();

	int x = 0;
	int y = 0;
	for (Tile* tile : tiles)
	{
		Vector2 pos = startPos + Vector2(x++ * tile->Size().x, -y * tile->Size().y);
		if (x > 19)
		{
			x = 0;
			y++;
		}
		tile->SetLocalPosition(pos);
		tile->UpdateWorld();
	}

}
