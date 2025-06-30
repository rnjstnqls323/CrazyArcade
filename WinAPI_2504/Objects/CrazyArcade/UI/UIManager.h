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

	void AddShowPanel(PanelType key);
	void PopForntPanel();

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