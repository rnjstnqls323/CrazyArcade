#pragma once

class Stage2Scene : public PlayScene
{
public:
	Stage2Scene();
	~Stage2Scene();

	void Start() override;
	void End() override;
private:
	void StopAudio() override;
	void CreatePlayerMap() override;

};