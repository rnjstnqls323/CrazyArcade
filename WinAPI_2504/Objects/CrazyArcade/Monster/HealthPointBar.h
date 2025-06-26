#pragma once

class HealthPointBar :public Transform
{
public:
	HealthPointBar();
	~HealthPointBar();

	void Update();
	void Render();

	void SetLength(int num){}
	
private:
	int	maxLength
	int length = 100;
	Quad* backBar;
	Quad* frontBar;
};