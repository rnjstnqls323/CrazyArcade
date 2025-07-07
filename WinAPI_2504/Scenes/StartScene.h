#pragma once


class StartScene : public Scene
{
private:
	enum StartStatus {
		StartAni1, StartAni2, StartPanel1
	};
public:
	StartScene();
	~StartScene();

	void Update() override;
	void Render() override;
	void Start() override;
	void End() override;

private:
	void ChangeStatus();
	void CreateAnimation();
	void AddAudio();
private:
	Transform* transform;
	MatrixBuffer* worldBuffer;
	Animation* animation;
	StartStatus curStatus;
};