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
		for (JetSegment* jet : waterJets[(WaterJet)i])
		{
			delete jet->jetTransform;
			delete jet->jetWorldBuffer;
			delete jet;
		}
		waterJets[(WaterJet)i].clear();
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

void Bubble::Spawn(Vector2 spawnPos)
{
	SetLocalPosition(spawnPos);
	UpdateWorld();

	curStatus = BubbleIdle;

	isActive = true;
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
		switch ((WaterJet)i)
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
		waterJetAnimation[(WaterJet)i] = new Animation;
		waterJetAnimation[(WaterJet)i]->LoadClip("Resources/Textures/CrazyArcade_Bubble/", 
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
				for (JetSegment* jet : waterJets[(WaterJet)i])
				{
					jet->jetAnimation->Play(0);
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
	}
}

void Bubble::CreateJet()
{
	vector<Vector2> offset =
	{
		{-1,0},{1,0},{0,1},{0,-1}
	};

	for (int i = 0;i <= DownWater;i++)
	{
		waterJets[(WaterJet)i].resize(MAX_JET_LENGTH);
	}
	for (int i = 0;i <= DownWater;i++)
	{
		int count = 1;
		for (JetSegment*& jet : waterJets[(WaterJet)i])
		{
			jet = new JetSegment;
			jet->jetAnimation = waterJetAnimation[(WaterJet)i];
			jet->jetTransform = new Transform;
			jet->jetTransform->SetParent(this);
			jet->jetTransform->SetLocalPosition(GetLocalPosition().x + (TILE_SIZE.x * count * offset[i].x),
				GetLocalPosition().y + (TILE_SIZE.y * count * offset[i].y));
			jet->jetTransform->UpdateWorld();
			jet->jetWorldBuffer = new MatrixBuffer;

			count++;
		}
	}

}

void Bubble::RenderJet()
{
	if (curStatus != Exploding) return;

	for (int i = 0;i <= DownWater;i++)
	{
		for (JetSegment* jet : waterJets[(WaterJet)i])
		{
			jet->jetWorldBuffer->Set(jet->jetTransform->GetWorld());
			jet->jetWorldBuffer->SetVS(0);
			jet->jetAnimation->Render(0);
		}
	}
}

void Bubble::UpdateJet()
{
	if (curStatus == Exploding)
	{
		for (int i = 0;i <= DownWater;i++)
		{
			int count = 0;
			for (JetSegment* jet : waterJets[(WaterJet)i])
			{
				if (count++ < curLength)
				{
					jet->isJetActive=true;
					jet->jetTransform->UpdateWorld();
					jet->jetAnimation->Update(0);
				}

			}
		}
	}
}



