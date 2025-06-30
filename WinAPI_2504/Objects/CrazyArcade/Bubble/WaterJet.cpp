#include "Framework.h"

WaterJet::WaterJet(string path)
{
	this->animation = new Animation();
	this->animation -> LoadClip("Resources/Textures/CrazyArcade_Bubble/","Create_Jet_"+path+".xml", false, 0.4f);;
	transform = new Transform;
	worldBuffer = new MatrixBuffer;

	isActive = true;
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

	transform->UpdateWorld();
	animation->Update(0);
}

