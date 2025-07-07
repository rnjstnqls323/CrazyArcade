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
private:

	void OnClick();
	void CreateQuads();

private:
	bool isOnTheButton;
	function<void()> onClick;
	wstring path;
	ButtonStatus curStatus = NoneClick;
	vector<Quad*> quads;
};