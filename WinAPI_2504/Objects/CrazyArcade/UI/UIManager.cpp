#include "Framework.h"

UIManager::UIManager()
{
	CreatePanel<PlayPanel>(PanelType::PlayPanel);
}

UIManager::~UIManager()
{
	for (auto& panel : panels)
	{
		delete panel.second;
	}
	panels.clear();
	showPanels.clear();
}

void UIManager::Render()
{
	for (Panel* panel : showPanels)
	{
		panel->Render();
	}
}

void UIManager::Update(Player* player)
{
	for (Panel* panel : showPanels)
	{
		panel->Update();
	}
}

void UIManager::ShowPanel(PanelType key)
{
	showPanels.push_back(panels[key]);
}

void UIManager::PopForntPanel()
{
	if (showPanels.empty()) return;

	showPanels.pop_back();
}
