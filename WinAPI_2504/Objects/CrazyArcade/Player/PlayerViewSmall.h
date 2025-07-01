#pragma once

class PlayerViewSmall : public GameObject
{
public:
	PlayerViewSmall();
	~PlayerViewSmall();

	void Render() override;
private:
	void MakeMesh() override {}
	void CreateQuads();
	wstring ChangeCharacterNameToWstirng(CharacterName name);
private:
	unordered_map<CharacterName,Quad*> quads;
	
};