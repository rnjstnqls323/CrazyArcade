#pragma once

class StoreScene :public Scene
{
public:
	StoreScene();
	~StoreScene();

	void Update() override;
	void Render() override;
	void Start() override;
	void End() override;

private:
	Player* player;
};