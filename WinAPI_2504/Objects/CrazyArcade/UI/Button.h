#pragma once

class Button :public RectCollider
{
public:
	enum ButtonStatus
	{
		NoneClick, Click
	};
public :
	Button(wstring name, Vector2 pos,Vector2 size);
	~Button();

	void Update();
	void Render();
	void SetOnClick(function<void()> func) { onClick = func; }

	void SetClickSound(string clickSound) { this->clickSound = clickSound; }
private:

	void OnClick();
	void CreateQuads();

private:
	string clickSound = "ef_Click";
	bool isOnTheButton;
	function<void()> onClick;
	wstring path;
	ButtonStatus curStatus = NoneClick;
	vector<Quad*> quads;
};