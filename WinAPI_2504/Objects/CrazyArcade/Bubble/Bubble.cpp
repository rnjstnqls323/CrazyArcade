#include "Framework.h"

BubbleType Bubble::bubble = BubbleType::Basic;
Bubble::Bubble()
{
	LoadAnimation();

	worldBuffer = new MatrixBuffer;
	isActive = false;

	CreateJet();
}

Bubble::~Bubble()
{
	for (auto& ani : animation)
	{
		delete ani.second;
	}
	animation.clear();
	for (int i = 0;i <= DownWater;i++)
	{
		for (WaterJet* jet : waterJets[(WaterJetStatus)i])
		{
			delete jet;
		}
		waterJets[(WaterJetStatus)i].clear();
	}

}
void Bubble::Render()
{
	if (isActive == false || curStatus == Dead)
		return;

	worldBuffer->Set(this->GetWorld());
	worldBuffer->SetVS(0);
	animation[bubble]->Render(curStatus);

	RenderJet();

}
void Bubble::Update()
{
	if (isActive == false || curStatus == Dead)
		return;

	animation[bubble]->Update(curStatus);
	UpdateStatus();
	UpdateJet();

}

void Bubble::Spawn(Vector2 spawnPos, Index2 index, TileMap* map, int tag)
{
	this->tag = tag;
	this->map = map;
	this->index = index;
	SetLocalPosition(spawnPos);
	UpdateWorld();

	curStatus = BubbleIdle;

	isActive = true;
	SetIndexJet(index);
}

void Bubble::Reset()
{
	isActive = false;
	timer = 0.0f;
}

string Bubble::GetBubbleTypeToString(BubbleType type)
{
	switch (type)
	{
	case BubbleType::Basic:
		return "Basic";
	case BubbleType::Bling:
		return "Bling";
	case BubbleType::Dark:
		return "Dark";
	case BubbleType::DarkStar:
		return "DarkStar";
	case BubbleType::Korea:
		return "Korea";
	case BubbleType::Rainbow:
		return "Rainbow";
	case BubbleType::RedDevil:
		return "RedDevil";
	case BubbleType::RedPang:
		return "RedPang";
	case BubbleType::Punk:
		return "Punk";

	}
}

wstring Bubble::GetBubbleTypeToWString(BubbleType type)
{
	switch (type)
	{
	case BubbleType::Basic:
		return L"Basic";
	case BubbleType::Bling:
		return L"Bling";
	case BubbleType::Dark:
		return L"Dark";
	case BubbleType::DarkStar:
		return L"DarkStar";
	case BubbleType::Korea:
		return L"Korea";
	case BubbleType::Rainbow:
		return L"Rainbow";
	case BubbleType::RedDevil:
		return L"RedDevil";
	case BubbleType::RedPang:
		return L"RedPang";
	case BubbleType::Punk:
		return L"Punk";
	}
}

void Bubble::LoadAnimation()
{
	for (int i = 0; i < (int)BubbleType::RedPang + 1; i++)
	{
		BubbleType type = (BubbleType)i;
		string name = GetBubbleTypeToString(type);
		animation[type] = new Animation();
		
		animation[type]->LoadClip("Resources/Textures/CrazyArcade_Bubble/", name+".xml", true, 0.4f);
		animation[type]->LoadClip("Resources/Textures/CrazyArcade_Bubble/", "Bubble_Exploding.xml", true, 0.5f);
	}
	
}

void Bubble::UpdateStatus()
{
	timer += DELTA;

	switch (curStatus)
	{
	case BubbleIdle:
	{
		if (timer >= BOMB_TIME)
		{
			Audio::Get()->Play("ef_Bomb");
			curStatus = Exploding;
			animation[bubble]->Play(curStatus);
			CrushOrBomb();
		}
	}
	break;
	case Exploding:
	{
		if (timer >= EXPLOING_TIME + BOMB_TIME)
		{
			curStatus = Dead;
			timer = 0.0;
			for (int i = 0; i <= DownWater; i++)
			{
				for (WaterJet* jet : waterJets[(WaterJetStatus)i])
				{
					if (!jet->IsRender())
						continue;
					jet->SetIsRender(false);
					map->SetTileType(PassTile, jet->GetIndex());
				}
			}
		}
	}

	break;
	}
}

void Bubble::CreateJet()
{
	vector<Vector2> offset =
	{
		{-1,0},{1,0},{0,1},{0,-1} //¿Þ¿ÀÀ§¾Æ·¡
	};

	for (int i = 0;i <= DownWater;i++)
	{
		waterJets[(WaterJetStatus)i].resize(MAX_JET_LENGTH);
	}
	for (int i = 0;i <= DownWater;i++)
	{
		int count = 1;
		for (WaterJet*& jet : waterJets[(WaterJetStatus)i])
		{
			switch ((WaterJetStatus)i)
			{
			case LeftWater:
				jet = new WaterJet("Left");
				break;
			case RightWater:
				jet = new WaterJet("Right");
				break;
			case UpWater:
				jet = new WaterJet("Up");
				break;
			case DownWater:
				jet = new WaterJet("Down");
				break;
			}

			Transform* temp = jet->GetTransform();
			temp->SetParent(this);
			temp->SetLocalPosition(GetLocalPosition().x + (TILE_SIZE.x * count * offset[i].x),
				GetLocalPosition().y + (TILE_SIZE.y * count * offset[i].y));
			temp->UpdateWorld();

			count++;
		}
	}

}

void Bubble::RenderJet()
{
	if (curStatus != Exploding) return;

	for (int i = 0; i <= DownWater; i++)
	{
		for (WaterJet* jet : waterJets[(WaterJetStatus)i])
		{
			if (!jet->IsActive() || !jet->IsRender())
				continue;
			jet->Render();
		}
	}
}

void Bubble::UpdateJet()
{
	if (curStatus != Exploding)
		return;

	for (int i = 0; i <= DownWater; i++)
	{
		int count = 0;
		bool isBlocked = false;

		for (WaterJet* jet : waterJets[(WaterJetStatus)i])
		{
			if (count++ >= curLength)
				break;

			jet->Update();

			Index2 index = jet->GetIndex();
			if (!map->IsIndexInBound(index) || isBlocked)
				continue;

			if (IsBlockingTile(index))
			{
				isBlocked = true;
				jet->SetIsRender(false);
			}
			else if (map->GetPreTileType(index) == CrushTile)
			{
				isBlocked = true;
				jet->SetIsRender(true);
			}
			else
			{
				jet->SetIsRender(true);
				map->SetTileType(WaterTile, index);
				map->SetTileTag(jet->GetJetTag(), index);
			}
		}
	}
}

void Bubble::SetIndexJet(Index2 index)
{
	vector<Index2> offset =
	{
		{0,-1},{0,1},{-1,0},{1,0} //¿Þ¿ÀÀ§¾Æ·¡ ÀÎµ¦½º´Â y,x¼ø
	};

	for (int i = 0; i <= DownWater; i++)
	{
		int count = 1;
		for (WaterJet*& jet : waterJets[(WaterJetStatus)i])
		{
			jet->SetIndex({
				index.y + offset[i].y * count,
				index.x + offset[i].x * count
				});
			Index2 jetindex = jet->GetIndex();
			jet->SetJetTag(tag);
			count++;
		}
	}
}

bool Bubble::IsBlockingTile(Index2 index)
{
	if (map->GetTileType(index) == CrushTile || map->GetTileType(index) == BlockTile)
		return true;
	return false;
}

void Bubble::CrushOrBomb()
{
	for (int i = 0; i <= DownWater; i++)
	{
		int count = 0;
		for (WaterJet* jet : waterJets[(WaterJetStatus)i])
		{
			if (count++ >= curLength)
				break;
			Index2 index = jet->GetIndex();

			if (!map->IsIndexInBound(index))
				continue;

			jet->PlayAnimation();

			TileType tile = map->GetTileType(index);

			if (map->GetPreTileType(index) == CrushTile ) break;
			switch (tile)
			{
			case BubbleTile:
				BubbleManager::Get()->BombBubble(index);
				break;

			case CrushTile:
				map->CrushBlock(index);
				break;

			}
			if (tile == BlockTile || tile == CrushTile)
				break;
		}
	}
}




