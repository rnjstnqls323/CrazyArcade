#pragma once

class Stage2Scene : public PlayScene
{
public:
	Stage2Scene();
	~Stage2Scene();
private:
	void CreatePlayerMap() override;

};