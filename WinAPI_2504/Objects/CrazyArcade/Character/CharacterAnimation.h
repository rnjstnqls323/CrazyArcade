#pragma once

class CharacterAnimation
{
public:
	CharacterAnimation();
	~CharacterAnimation();

	void Render(size_t index);
	void Update(size_t index);
	void Play(size_t index);

	void LoadClip(const string& path, const string& file, const bool& isLoop, const float& speed = 1.0f);

private:
	vector<Clip*> clips;
};