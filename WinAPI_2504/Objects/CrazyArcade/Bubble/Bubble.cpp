#include "Framework.h"

Bubble::Bubble()
{
	LoadWaterJetAnimation();

	animation = new Animation();
	LoadAnimation();

	worldBuffer = new MatrixBuffer;
	isActive = false;

	CreateJet();
}

Bubble::~Bubble()
{
	delete animation;

	for (auto& ani : waterJetAnimation)
		delete ani.second;
	waterJetAnimation.clear();

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
	animation->Render(curStatus);
 
	RenderJet();

}
void Bubble::Update()
{
	if (isActive == false || curStatus == Dead)
		return;									

	animation->Update(curStatus);
	UpdateStatus();

	UpdateJet();
}

void Bubble::Spawn(Vector2 spawnPos, Index2 index)
{
	SetLocalPosition(spawnPos);
	UpdateWorld();

	curStatus = BubbleIdle;

	isActive = true;
	SetIndexJet(index);
}

void Bubble::Reset()
{

}
void Bubble::LoadAnimation()
{
	animation->LoadClip("Resources/Textures/CrazyArcade_Bubble/", "Bubble_Idle.xml", true,0.4f);
	animation->LoadClip("Resources/Textures/CrazyArcade_Bubble/", "Bubble_Exploding.xml", true,0.5f);
}

void Bubble::LoadWaterJetAnimation()
{
	for (int i = 0;i <= DownWater;i++)
	{
		string fileName;
		switch ((WaterJetStatus)i)
		{
		case LeftWater:
			fileName = "Left";
			break;
		case RightWater:
			fileName = "Right";
			break;
		case UpWater:
			fileName = "Up";
			break;
		case DownWater:
			fileName = "Down";
			break;
		}
		waterJetAnimation[(WaterJetStatus)i] = new Animation;
		waterJetAnimation[(WaterJetStatus)i]->LoadClip("Resources/Textures/CrazyArcade_Bubble/",
			"Create_Jet_"+ fileName +".xml", false, 0.2f);
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
			curStatus = Exploding;
			animation->Play(curStatus);
			for (int i = 0;i <= DownWater;i++)
			{
				for (WaterJet* jet : waterJets[(WaterJetStatus)i])
				{
					jet->PlayAnimation();
				}
			}
		}
	}
		break;
	case Exploding:
	{
		if (timer >= EXPLOING_TIME + BOMB_TIME)
		{
			curStatus = Dead;
			timer = 0.0;
		}
	}
		break;

	case Dead:
	{
		for (int i = 0; i <= DownWater; i++)
		{
			for (WaterJet* jet : waterJets[(WaterJetStatus)i])
			{
				jet->SetActive(false);
			}
		}
		break;
	}
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
			jet = new WaterJet(waterJetAnimation[(WaterJetStatus)i]);

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
			if (!jet->IsActive())
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
		for (WaterJet* jet : waterJets[(WaterJetStatus)i])
		{
			if (count++ < curLength)
			{
				jet->Update();
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
			count++;  
		}
	}
}



