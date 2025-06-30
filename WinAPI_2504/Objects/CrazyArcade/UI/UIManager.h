#pragma once

class UIManager :public Singleton<UIManager>
{
	friend class Singleton;
private:
	UIManager();
	~UIManager();

public:
	void Render();
	void Update(Player* player);

	void ShowPanel(PanelType key);
	void PopForntPanel();
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