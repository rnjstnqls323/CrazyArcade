#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	CreateAnimation(); // 局聪皋捞记 包访等芭 傈何 积己
}

StartScene::~StartScene()
{
	delete animation;
}

void StartScene::Update()
{
	if(curStatus == StartPanel1)
		UIManager::Get()->Update();
	else
	{
		animation->Update(curStatus);
		ChangeStatus();
	}
}

void StartScene::Render()
{
	if(curStatus == StartPanel1)
		UIManager::Get()->Render();
	else
	{
		worldBuffer->Set(transform->GetWorld());
		worldBuffer->SetVS(0);
		animation->Render(curStatus);
	}
}

void StartScene::Start()
{
	curStatus = StartAni1;
	animation->Play(curStatus);
}

void StartScene::End()
{
	UIManager::Get()->Reset();
}

void StartScene::ChangeStatus()
{
	if (curStatus == StartPanel1) return;

	if (!animation->IsPlay(curStatus))
	{
		curStatus = (StartStatus)((int)curStatus + 1);
		if (curStatus == StartPanel1)
		{
			UIManager::Get()->AddShowPanel(PanelType::StartPanel);
			return;
		}
		animation->Play(curStatus);
	}
}

void StartScene::CreateAnimation()
{
	animation = new Animation;

	animation->LoadClip("Resources/Textures/CrazyArcade_UI/Start/", "Start1.xml", false,0.4f);
	animation->LoadClip("Resources/Textures/CrazyArcade_UI/Start/", "Start2.xml", false,0.5f);


	transform = new Transform();
	transform->SetLocalPosition(700, 480);
	transform->UpdateWorld();

	worldBuffer = new MatrixBuffer;
}
