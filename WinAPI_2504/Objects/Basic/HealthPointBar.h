#pragma once

class HealthPointBar :public Transform
{
public:
	HealthPointBar(int maxHealthPoint);
	~HealthPointBar();

	void Update();
	void Render();
	void SetLength(int num){ length = (float)num / maxHealthPoint; }
	
private:
	int	maxHealthPoint;
	float length = 1.0f;
	Quad* backBar;
	Quad* frontBar;
	FloatValueBuffer* valueBuffer;
};