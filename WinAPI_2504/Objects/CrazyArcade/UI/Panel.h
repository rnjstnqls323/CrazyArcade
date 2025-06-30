#pragma once

enum class PanelType {
	PlayPanel
};
class Panel : public GameObject
{
public:
	Panel();
	~Panel();

	virtual void Update(Player* player) = 0;
	virtual void Render() = 0;

protected:
	virtual void CreateButton() = 0;
	virtual void CreateBackGround() = 0;
	virtual void SetEventFunc() = 0;

protected:

	Vector2 pos = { 700, 480 };
	Quad* backGround;
	vector<Button*> buttons;
};