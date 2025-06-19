#include "Framework.h"

Bubble::Bubble()
{
	animation = new Animation();
	LoadAnimation();

	worldBuffer = new MatrixBuffer;
	isActive = false;
}

Bubble::~Bubble()
{
	delete animation;
}

void Bubble::Render()
{
	if (isActive == false || curStatus != BubbleIdle)// �̺κ� �����ֱ� (�ִϸ��̼� �� ������)
		return;										 // �̺κ� �����ֱ� (�ִϸ��̼� �� ������)
	
	worldBuffer->Set(this->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(curStatus);
 
}

void Bubble::Update()
{
	if (isActive == false || curStatus != BubbleIdle)// �̺κ� �����ֱ� (�ִϸ��̼� �� ������)
		return;										 // �̺κ� �����ֱ� (�ִϸ��̼� �� ������)

	animation->Update(curStatus);
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
	animation->LoadClip("Resources/Textures/CrazyArcade_Bubble/", "Bubble_Idle.xml", true,0.5f);
}



