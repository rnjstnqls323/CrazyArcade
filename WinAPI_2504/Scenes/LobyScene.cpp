#include "Framework.h"
#include "LobyScene.h"

LobyScene::LobyScene()
{
	UIManager::Get()->Reset();
	UIManager::Get()->AddShowPanel(PanelType::LobyPanel);
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
