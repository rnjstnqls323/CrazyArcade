#pragma once

class Stage1Scene : public PlayScene
{
public:
	Stage1Scene();
	~Stage1Scene();
private:
	void CreatePlayerMap() override;
};