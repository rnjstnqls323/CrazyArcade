#pragma once

class Stage1Scene : public PlayScene
{
public:
	Stage1Scene();
	~Stage1Scene();

	void Start() override;
	void End() override;
private:
	void StopAudio() override;
	void CreatePlayerMap() override;
};