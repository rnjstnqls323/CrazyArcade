#include "Framework.h"

ShaShakType ShaShak :: shaShak = ShaShakType::Heart;
ShaShak::ShaShak()
{
	UpdateWorld();
	CreateAnimation();
	CreateTransform();
	worldBuffer = new MatrixBuffer;
}

ShaShak::~ShaShak()
{
	delete worldBuffer;
	for (auto& ani : animation)
	{
		delete ani.second;
	}
	animation.clear();

	for (auto& trans : transform)
	{
		delete trans.second;
	}
	transform.clear();
}

wstring ShaShak::GetShaShakTypeToWString(ShaShakType type)
{
	switch (type)
	{
	case ShaShakType::Shine:
		return L"Shine";
	case ShaShakType::Clover:
		return L"Clover";
	case ShaShakType::Heart:
		return L"Heart";
	}
}

void ShaShak::Update()
{
	if (curStatus == ShaShakStatus::Idle || shaShak == ShaShakType::Basic) return;
	UpdateWorld();
	transform[curStatus]->UpdateWorld();
	animation[shaShak]->Update(0);
}

void ShaShak::Render()
{
	if (curStatus == ShaShakStatus::Idle || shaShak == ShaShakType::Basic) return;
	worldBuffer->Set(transform[curStatus]->GetWorld());
	worldBuffer->SetVS(0);
	animation[shaShak]->Render(0);
}

string ShaShak::ShaShakTypeToString(ShaShakType type)
{
	switch (type)
	{
	case ShaShakType::Shine:
		return "Shine";
	case ShaShakType::Clover:
		return "Clover";
	case ShaShakType::Heart:
		return "Heart";
	}
}

void ShaShak::CreateAnimation()
{
	for (int i = 0;i < (int)ShaShakType::Heart;i++)
	{
		ShaShakType type = (ShaShakType)(i + 1);
		animation[type] = new Animation();
		animation[type]->LoadClip("Resources/Textures/CrazyArcade_ShaShak/", ShaShakTypeToString(type) + ".xml",true);
	}
}

void ShaShak::CreateTransform()
{
	float temp = 40;
	for (int i = 0;i < (int)ShaShakStatus::MoveRight;i++)
	{
		ShaShakStatus type= (ShaShakStatus)(i + 1);
		transform[type] = new Transform();
		transform[type]->SetParent(this);
		Vector2 pos = transform[type]->GetLocalPosition();
		switch (type)
		{
		case ShaShakStatus::MoveUp:
			transform[type]->SetLocalPosition(pos.x, pos.y - temp);
			break;
		case ShaShakStatus::MoveDown:
			transform[type]->SetLocalPosition(pos.x, pos.y + temp);
			break;
		case ShaShakStatus::MoveLeft:
			transform[type]->SetLocalPosition(pos.x+ temp, pos.y);
			break;
		case ShaShakStatus::MoveRight:
			transform[type]->SetLocalPosition(pos.x- temp, pos.y);
			break;
		}
	}
}
