#include "Framework.h"

WaterJet::WaterJet(Animation* animation)
{
	this->animation = animation;
	transform = new Transform;
	worldBuffer = new MatrixBuffer;

	isActive = false;
}

WaterJet::~WaterJet()
{
	delete animation;
	delete transform;
	delete worldBuffer;
}

void WaterJet::Render()
{
	worldBuffer->Set(transform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(0);
}
void WaterJet::Update()
{
	isActive = true;
	transform->UpdateWorld();
	animation->Update(0);
}

