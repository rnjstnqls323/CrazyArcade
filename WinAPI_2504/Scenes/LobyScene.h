#pragma once

class LobyScene : public Scene
{
public:
	LobyScene();
	~LobyScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Start() override;
	void End() override;
};