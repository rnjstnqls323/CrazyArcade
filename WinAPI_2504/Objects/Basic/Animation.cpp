#include "Framework.h"

Animation::Animation()
{
}

Animation::~Animation()
{
	for (Clip* clip : clips)
	{
		delete clip;
	}
}

void Animation::Render(size_t index)
{
	clips[index]->Render();
}

void Animation::Update(size_t index)
{
	clips[index]->Update();
}

void Animation::Play(size_t index)
{
	clips[index]->Play();
}

void Animation::LoadClip(const string& path, const string& file, const bool& isLoop, const float& speed)
{
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement();
	string textureFile = path + atlas->Attribute("imagePath");

	vector<Frame*> frames;
	tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;
		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		wstring file = Utility::ToWString(textureFile);
		frames.push_back(new Frame(file, x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clips.push_back(new Clip(frames, isLoop, speed));

	delete document;
}
