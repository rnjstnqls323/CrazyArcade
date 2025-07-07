#include "Framework.h"
#include "LobyScene.h"

LobyScene::LobyScene()
{
}

LobyScene::~LobyScene()
{
}

void LobyScene::Update()
{
	UIManager::Get()->Update();
}

void LobyScene::Render()
{
	UIManager::Get()->Render();
}

void LobyScene::GUIRender()
{
	UIManager::Get()->Edit();
}

void LobyScene::Start()
{
	UIManager::Get()->AddShowPanel(PanelType::LobyPanel);
	Audio::Get()->Play("bg_Loby");
}

void LobyScene::End()
{
	UIManager::Get()->Reset();
	Audio::Get()->Stop("bg_Loby");
}
