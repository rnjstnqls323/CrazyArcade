#pragma once

class UIManager :public Singleton<UIManager>
{
	friend class Singleton;
private:
	UIManager();
	~UIManager();

public:
	void Render();
	void Update(Player* player = nullptr);
	void Edit();

	void AddShowPanel(PanelType key);
	void PopForntPanel();

	PanelType GetFrontPanelType() { return showPanels.back()->GetPanelType(); }
	PanelType GetPrePanelType();

	void Reset() { showPanels.clear(); }
private:
	template<typename T>
	void CreatePanel(PanelType key)
	{
		T* panel = new T;
		panels[key] = panel;
	}

private:
	unordered_map< PanelType, Panel*> panels;
	vector<Panel*> showPanels;
};