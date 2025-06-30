#include "Framework.h"

UIManager::UIManager()
{
	CreatePanel<PlayPanel>(PanelType::PlayPanel);
	CreatePanel<ExitPanel>(PanelType::ExitPanel);
	CreatePanel<WinPanel>(PanelType::WinPanel);
	CreatePanel<LosePanel>(PanelType::LosePanel);
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
	if (!showPanels.empty())
		showPanels.back()->Update(player);
}

void UIManager::AddShowPanel(PanelType key)
{
	showPanels.push_back(panels[key]);
}

void UIManager::PopForntPanel()
{
	if (showPanels.empty()) return;

	showPanels.pop_back();
}
