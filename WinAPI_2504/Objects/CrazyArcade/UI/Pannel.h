#pragma once

class Pannel : public GameObject
{
public:
	Pannel();
	~Pannel();

	virtual void Update() = 0;
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