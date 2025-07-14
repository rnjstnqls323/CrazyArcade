#include "Framework.h"

HealthPointBar::HealthPointBar(int maxHealthPoint)
{
	this->maxHealthPoint = maxHealthPoint;
	valueBuffer = new FloatValueBuffer;
	backBar = new Quad(L"Resources/Textures/CrazyArcade_Monster/HealthBar/back.png");
	frontBar = new Quad(L"Resources/Textures/CrazyArcade_Monster/HealthBar/front.png");
	frontBar->GetMaterial()->SetShader(L"ProgressBar.hlsl");

	backBar->SetParent(this);
	frontBar->SetParent(this);

	this->SetLocalPosition(500, 500);
	backBar->UpdateWorld();
	frontBar->UpdateWorld();
}

HealthPointBar::~HealthPointBar()
{
	delete valueBuffer;
	delete backBar;
	delete frontBar;
}

void HealthPointBar::Update()
{
	this->UpdateWorld();
	backBar->UpdateWorld();
	frontBar->UpdateWorld();

	valueBuffer->GetValues()[0] = length;
	valueBuffer->SetPS(1);
}

void HealthPointBar::Render()
{
	backBar->Render();
	frontBar->Render();
}