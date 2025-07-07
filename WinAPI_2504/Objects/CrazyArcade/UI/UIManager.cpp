#include "Framework.h"

UIManager::UIManager()
{
	CreatePanel<PlayPanel>(PanelType::PlayPanel);
	CreatePanel<ExitPanel>(PanelType::ExitPanel);
	CreatePanel<GoBackPanel>(PanelType::GoBackPanel);
	CreatePanel<WinPanel>(PanelType::WinPanel);
	CreatePanel<LosePanel>(PanelType::LosePanel);
	CreatePanel<LobyPanel>(PanelType::LobyPanel);
	CreatePanel<InventoryPanel>(PanelType::InventoryPanel);
	CreatePanel<StorePanel>(PanelType::StorePanel);
	CreatePanel<BuyCheckPanel>(PanelType::BuyCheckPanel);
	CreatePanel<NoLucciAlretPanel>(PanelType::NoLucciAlretPanel);
	CreatePanel<InventoryCheckAlretPanel>(PanelType::InventoryCheckAlretPanel);
	CreatePanel<NoChoiceAlretPanel>(PanelType::NoChoiceAlretPanel);
	CreatePanel<StartPanel>(PanelType::StartPanel);
	CreatePanel<PlayStartPanel>(PanelType::PlayStartPanel);
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

void UIManager::Edit()
{
	if (!showPanels.empty())
		showPanels.back()->PanelEdit();
}

void UIManager::AddShowPanel(PanelType key)
{
	panels[key]->Reset();
	showPanels.push_back(panels[key]);
}

void UIManager::PopForntPanel()
{
	if (showPanels.empty()) return;

	showPanels.pop_back();
}

PanelType UIManager::GetPrePanelType()
{
	if (showPanels.size() - 2 < 0) return PanelType::ExitPanel;
	return showPanels[showPanels.size() - 2]->GetPanelType();
}
